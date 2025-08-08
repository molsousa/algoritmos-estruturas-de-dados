#include <stdlib.h>
#include "../include/fila.h"
#include "../include/arvoreb.h"

// Funcao para escrever no cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: nenhuma
void escrever_cabecalho(FILE* f, cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, f);
}

// Funcao para ler cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: retorna cabecalho na condicao atual
cabecalho* ler_cabecalho(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, f);

    return cab;
}

// Funcao para escrever em pagina B
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void escrever_no(FILE* f, noB* r, int pos)
{
    fseek(f, sizeof(cabecalho) + sizeof(noB) * pos, SEEK_SET);
    fwrite(r, sizeof(noB), 1, f);
}

// Funcao para ler pagina B
// Pre-condicao: nenhuma
// Pos-condicao: retorna pagina B na condicao atual
noB* ler_no(FILE* f, int pos)
{
    noB* r = malloc(sizeof(noB));

    fseek(f, sizeof(cabecalho) + sizeof(noB) * pos, SEEK_SET);
    fread(r, sizeof(noB), 1, f);

    return r;
}

// Funcao para inicializar arquivo binario
// Pre-condicao: nenhuma
// Pos-condicao: cria cabecalho
void inicializar(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(f, cab);
    free(cab);
}

boolean eh_folha(FILE* f, int pos)
{
    noB* r = ler_no(f, pos);

    if(r->filhos[0] == -1){
        free(r);
        return true;
    }

    free(r);
    return false;
}

// Funcao para verificar se houve overflow
// Pre-condicao: nenhuma
// Pos-condicao: retorna verdadeiro se um no estiver cheio
boolean overflow(FILE* f, int pos)
{
    noB* r = ler_no(f, pos);
    int num_chaves = r->num_chaves;

    free(r);

    if(num_chaves == ORDEM)
        return true;

    return false;
}

// Funcao para separar paginas
// Pre-condicao: arvore criada
// Pos-condicao: retorna posicao da pagina separada
int split(FILE* f, int pos, int* m, cabecalho* cab)
{
    noB* r = ler_no(f, pos);
    noB y;
    int nova_pos = cab->pos_topo++;

    int q = r->num_chaves/2;
    y.num_chaves = r->num_chaves - q - 1;
    r->num_chaves = q;
    *m = r->chaves[q];

    int i = 0;
    y.filhos[0] = r->filhos[q+1];

    while(i < y.num_chaves){
        y.chaves[i] = r->chaves[q+i+1];
        y.filhos[i+1] = r->filhos[q+i+2];
        i++;
    }
    escrever_no(f, &y, nova_pos);
    escrever_no(f, r, pos);

    return nova_pos;
}

// Funcao para buscar posicao para inserir um elemento
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se encontrado no
int busca_pos(FILE* f, int pos, int chave, int* pos_chave)
{
    noB* r = ler_no(f, pos);

    for(*pos_chave = 0; *pos_chave < r->num_chaves; ++*pos_chave){
        if(chave == r->chaves[(*pos_chave)]){
            free(r);
            return 1;
        }
        else if(chave < r->chaves[(*pos_chave)])
            break;
    }
    free(r);

    return 0;
}

// Funcao para adicionar uma chave com um filho a uma pagina
// Pre-condicao: nenhuma
// Pos-condicao: adiciona uma chave com um filho a uma pagina e desloca as demais a direita se necessario
void adicionar_direita(FILE* f, int pos_r, int pos_chave, int k, int pos_p)
{
    int i;
    noB* r = ler_no(f, pos_r);

    for(i = r->num_chaves; i > pos_chave; i--){
        r->chaves[i] = r->chaves[i-1];
        r->filhos[i+1] = r->filhos[i];
    }

    r->chaves[pos_chave] = k;
    r->filhos[pos_chave+1] = pos_p;
    r->num_chaves++;

    escrever_no(f, r, pos_r);
    free(r);
}

// Funcao para inserir em arvore-B
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void inserir(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    cab->pos_raiz = inserir_chave(f, chave, cab, cab->pos_raiz);
    escrever_cabecalho(f, cab);

    free(cab);
}

// Funcao para inserir em arvore-B
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento na arvore
int inserir_chave(FILE* f, int chave, cabecalho* cab, int pos)
{
    if(pos == -1){
        int i;
        pos = cab->pos_topo++;
        noB novo;
        novo.chaves[0] = chave;

        for(i = 0; i < ORDEM; i++)
            novo.filhos[i] = -1;

        novo.num_chaves = 1;
        escrever_no(f, &novo, pos);
    }
    else{
        inserir_aux(f, chave, cab, pos);

        if(overflow(f, pos)){
            int m;
            int i;

            int pos_split = split(f, pos, &m, cab);
            int nova_pos = cab->pos_topo++;

            noB* nova_raiz = malloc(sizeof(noB));
            noB* r = ler_no(f, pos);

            nova_raiz->chaves[0] = m;
            nova_raiz->filhos[0] = pos;
            nova_raiz->filhos[1] = pos_split;

            for(i = ((ORDEM/2)+1); i < ORDEM; i++)
                r->filhos[i] = -1;

            nova_raiz->num_chaves = 1;
            escrever_no(f, nova_raiz, nova_pos);
            escrever_no(f, r, pos);

            free(r);
            free(nova_raiz);

            return nova_pos;
        }
    }

    return pos;
}

// Funcao auxiliar para inserir
// Pre-condicao: nenhuma
// Pos-condicao: utiliza as funcoes auxiliares para inserir determinado elemento
void inserir_aux(FILE* f, int chave, cabecalho* cab, int pos)
{
    noB* r = ler_no(f, pos);
    int nova_pos;

    if(!busca_pos(f, pos, chave, &nova_pos)){
        if(eh_folha(f, pos))
            adicionar_direita(f, pos, nova_pos, chave, -1);

        else{
            int pos_filho = r->filhos[nova_pos];
            inserir_aux(f, chave, cab, pos_filho);

            if(overflow(f, pos_filho)){
                int m;

                int pos_aux = split(f, pos_filho, &m, cab);
                adicionar_direita(f, pos, nova_pos, m, pos_aux);
            }
        }
    }
    free(r);
}

boolean underflow(FILE* f, int pos)
{
    noB* r = ler_no(f, pos);
    int num_chaves = r->num_chaves;
    free(r);

    if(pos != -1 && num_chaves < MIN_CHAVES)
        return true;

    return false;
}

void remover(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    cab->pos_raiz = remover_aux(f, chave, cab, cab->pos_raiz);
    escrever_cabecalho(f, cab);

    free(cab);
}

int remover_aux(FILE* f, int chave, cabecalho* cab, int pos)
{
    if(pos == -1)
        return pos;

    int pos_busca;
    int i;

    if(busca_pos(f, pos, chave, &pos_busca)){
        if(eh_folha(f, pos)){
            noB* r = ler_no(f, pos);
            for(i = pos_busca; i < r->num_chaves - 1; i++)
                r->chaves[i] = r->chaves[i+1];

            r->num_chaves--;
            escrever_no(f, r, pos);
        }
        else{
            noB* r = ler_no(f, pos);
            noB* predecessor = ler_no(f, r->filhos[pos_busca]);
            int pos_predecessor = pos_busca;

            while(!eh_folha(f, r->filhos[pos_predecessor])){
                pos_predecessor = predecessor->filhos[predecessor->num_chaves];
                free(predecessor);
                predecessor = ler_no(f, pos_predecessor);
            }

            int chave_predecessor = predecessor->chaves[predecessor->num_chaves-1];

            r->chaves[pos_busca] = chave_predecessor;
            r->filhos[pos_busca] = remover_aux(f, chave_predecessor, cab, r->filhos[pos_busca]);
        }
    }

    return pos;
}

// Funcao para imprimir arvore em linha
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);

    imprimir_aux(f, cab->pos_raiz);
    free(cab);
}

// Funcao auxiliar para imprimir em preOrdem
// Pre-condicao: nenhuma
// Pos-condicao: imprime os elementos da arvore em pre-ordenado
void imprimir_aux(FILE* f, int pos)
{
    if(pos == -1)
        return;

    int i;
    noB* r = ler_no(f, pos);

    for(i = 0; i < r->num_chaves; i++){
        printf("%d ", r->chaves[i]);
        imprimir_aux(f, r->filhos[i]);
    }

    imprimir_aux(f, r->filhos[i]);
    free(r);
}

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: imprime todos os nos por niveis
void imprimir_niveis(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_raiz;
    free(cab);

    if(pos == -1)
        return;

    Fila fila = criar_fila();
    noB* x = ler_no(f, pos);
    noB* aux[1000];
    int j = 0;

    enqueue(fila, x);
    enqueue(fila, NULL);

    aux[j++] = x;

    printf("[");

    while(!fila_vazia(fila)){
        noB* atual = dequeue(fila);

        if(atual == NULL){
            printf("\n");

            if(!fila_vazia(fila)){
                enqueue(fila, NULL);
                printf("[");
            }
        }

        else{
            int i;

            for(i = 0; i < atual->num_chaves; i++){
                printf("%d", atual->chaves[i]);
                if(i < atual->num_chaves-1)
                    printf(", ");

                else
                    printf("] ");
            }

            for(i = 0; atual->filhos[i] != -1 && i < atual->num_chaves+1; i++){
                x = ler_no(f, atual->filhos[i]);
                enqueue(fila, x);
                aux[j++] = x;
            }

            if(!consultar_nulo(fila))
                printf("[");
        }
    }
    j--;
    while(j >= 0)
        free(aux[j--]);
}
