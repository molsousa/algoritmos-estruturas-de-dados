#include <stdlib.h>
#include "../include/arvore23.h"
#include "../include/fila.h"

// Funcao para ler cabecalho
// Pre-condicao: arvore criada
// Pos-condicao: retorna cabecalho
cabecalho* ler_cabecalho(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, f);

    return cab;
}

// Funcao para escrever cabecalho
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void escrever_cabecalho(FILE* f, cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, f);
}

// Funcao para ler no
// Pre-condicao: arvore criada
// Pos-condicao: retorna no buscado
no23* ler_no(FILE* f, int pos)
{
    no23* r = malloc(sizeof(no23));

    fseek(f, sizeof(cabecalho) + sizeof(no23) * pos, SEEK_SET);
    fread(r, sizeof(no23), 1, f);

    return r;
}

// Funcao para escrever no
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void escrever_no(FILE* f, no23* r, int pos)
{
    fseek(f, sizeof(cabecalho) + sizeof(no23) * pos, SEEK_SET);
    fwrite(r, sizeof(no23), 1, f);
}

// Funcao para criar arvore23
// Pre-condicao: nenhuma
// Pos-condicao: inicializa cabecalho
void inicializar(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna verdadeiro se vazia
boolean vazia(int pos)
{
    if(pos == -1)
        return true;

    return false;
}

// Funcao para testar se um no eh folha
// Pre-condicao: arvore criada
// Pos-condicao: retorna verdadeiro se folha
boolean eh_folha(FILE* f, int pos)
{
    no23* r = ler_no(f, pos);

    if(vazia(r->esq) && vazia(r->meio) && vazia(r->dir)){
        free(r);
        return true;
    }
    free(r);

    return false;
}

// Funcao para buscar na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o indice do no buscado
int busca(FILE* f, int chave, int pos)
{
    if(vazia(pos))
        return pos;

    if(ler_no(f, pos)->chave_esq == chave)
        return pos;

    if(ler_no(f, pos)->num_chaves == 2 && ler_no(f, pos)->chave_dir == chave)
        return pos;

    if(chave < ler_no(f, pos)->chave_esq)
        return busca(f, chave, ler_no(f, pos)->esq);

    else if(ler_no(f, pos)->num_chaves == 1)
        return busca(f, chave, ler_no(f, pos)->meio);

    else if(chave < ler_no(f, pos)->chave_dir)
        return busca(f, chave, ler_no(f, pos)->meio);

    else
        return busca(f, chave, ler_no(f, pos)->dir);
}

// Funcao para obter posicao livre
// Pre-condicao: nenhuma
// Pos-condicao: retorna nova posicao ou posicao reaproveitada
int obter_pos_livre(FILE* f, cabecalho* cab)
{
    int pos_livre;

    if(cab->pos_livre != -1){
        pos_livre = cab->pos_livre;
        no23* livre = ler_no(f, pos_livre);

        cab->pos_livre = livre->esq;
        free(livre);
    }
    else
        pos_livre = cab->pos_topo++;

    return pos_livre;
}

// Funcao auxiliar para inserir em 23
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
int inserir_aux(FILE* f, int pos, int chave, int* chave_promovida, cabecalho* cab)
{
    no23* r = ler_no(f, pos);

    if(eh_folha(f, pos)){
        if(r->num_chaves == 1){
            adiciona_chave(f, pos, chave, -1);
            free(r);
            return -1;
        }
        else{
            free(r);
            return split(f, pos, chave, -1, chave_promovida, cab);
        }
    }
    else{
        int p_aux;
        int chave_aux;

        if(chave < r->chave_esq)
            p_aux = inserir_aux(f, r->esq, chave, &chave_aux, cab);

        else if((r->num_chaves == 1) || (chave < r->chave_dir))
            p_aux = inserir_aux(f, r->meio, chave, &chave_aux, cab);

        else
            p_aux = inserir_aux(f, r->dir, chave, &chave_aux, cab);

        if(vazia(p_aux)){
            free(r);
            return -1;
        }

        if(r->num_chaves == 1){
            free(r);
            adiciona_chave(f, pos, chave_aux, p_aux);
            return -1;
        }
        else{
            free(r);
            return split(f, pos, chave_aux, p_aux, chave_promovida, cab);
        }
    }
}

// Funcao para aplicar split em determinado no
// Pre-condicao: elemento na espera de ser inserido
// Pos-condicao: separa um no em dois
int split(FILE* f, int pos, int chave, int pos_subarvore, int* chave_promovida, cabecalho* cab)
{
    int p_aux;
    no23* r = ler_no(f, pos);

    if(chave > r->chave_dir){
        *chave_promovida = r->chave_dir;
        p_aux = r->dir;
        r->dir = -1;
        r->num_chaves = 1;

        escrever_no(f, r, pos);
        free(r);

        return cria_no(f, cab, chave, 0, p_aux, pos_subarvore, -1, 1);
    }
    else if(chave >= r->chave_esq){
        *chave_promovida = chave;
        p_aux = r->dir;
        r->dir = -1;
        r->num_chaves = 1;

        int chave_dir = r->chave_dir;

        escrever_no(f, r, pos);
        free(r);

        return cria_no(f, cab, chave_dir, 0, pos_subarvore, p_aux, -1, 1);
    }
    else{
        *chave_promovida = r->chave_esq;
        p_aux = cria_no(f, cab, r->chave_dir, 0, r->meio, r->dir, -1, 1);
        r->chave_esq = chave;
        r->num_chaves = 1;
        r->dir = -1;
        r->meio = pos_subarvore;

        escrever_no(f, r, pos);
        free(r);

        return p_aux;
    }
}

// Funcao para adicionar para adicionar chave
// Pre-condicao: nenhuma
// Pos-condicao: adiciona chave a esquerda ou a direita a depender do tamanho
void adiciona_chave(FILE* f, int pos, int chave, int pos_aux)
{
    no23* r = ler_no(f, pos);

    if(r->chave_esq < chave){
        r->chave_dir = chave;
        r->dir = pos_aux;
    }
    else{
        r->chave_dir = r->chave_esq;
        r->chave_esq = chave;
        r->dir = r->meio;
        r->meio = pos_aux;
    }
    r->num_chaves = 2;

    escrever_no(f, r, pos);
    free(r);
}

// Funcao auxiliar para criar no23
// Pre-condicao: nenhuma
// Pos-condicao: retorna novo no
int cria_no(FILE* f, cabecalho* cab, int chave_esq, int chave_dir, int esq, int meio, int dir, int num_chaves)
{
    int nova_pos = obter_pos_livre(f, cab);

    no23 novo;

    novo.chave_esq = chave_esq;
    novo.chave_dir = (num_chaves == 2) ? chave_dir : 0;
    novo.esq = esq;
    novo.meio = meio;
    novo.dir = (num_chaves == 2) ? dir : -1;
    novo.num_chaves = num_chaves;

    escrever_no(f, &novo, nova_pos);

    return nova_pos;
}

// Funcao para inserir elemento na arvore
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
int inserir_chave(FILE* f, int chave, cabecalho* cab, int pos)
{
    if(vazia(pos))
        return cria_no(f, cab, chave, 0, -1, -1, -1, 1);

    else{
        int chave_promovida;

        int p_aux = inserir_aux(f, pos, chave, &chave_promovida, cab);

        if(!vazia(p_aux))
            return cria_no(f, cab, chave_promovida, 0, pos, p_aux, -1, 1);

        else
            return pos;
    }
}

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void inserir(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    cab->pos_raiz = inserir_chave(f, chave, cab, cab->pos_raiz);
    escrever_cabecalho(f, cab);

    free(cab);
}

// Funcao para liberar posicao
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void liberar_pos(FILE* f, cabecalho* cab, int pos_livre)
{
    if(pos_livre == -1)
        return;

    no23* no_livre = ler_no(f, pos_livre);

    no_livre->esq = no_livre->meio = no_livre->dir = cab->pos_livre;
    cab->pos_livre = pos_livre;

    escrever_no(f, no_livre, pos_livre);
    free(no_livre);
}

// Funcao para encontrar o menor no
// Pre-condicao: nenhuma
// Pos-condicao: retorna menor no a partir do no buscado
int encontrar_menor(FILE* f, int pos)
{
    if(vazia(pos))
        return -1;

    no23* aux = ler_no(f, pos);
    int pos_esq = pos;

    while(aux->esq != -1){
        pos_esq = aux->esq;
        free(aux);
        aux = ler_no(f, pos_esq);
    }
    free(aux);

    return pos_esq;
}

// Funcao para verificar e tratar underflow
// Pre-condicao: removido o elemento
// Pos-condicao: verifica e corrige o balanceamento da arvore
int tratar_underflow(FILE* f, cabecalho* cab, int pos, int pos_filho)
{
    no23* pai = ler_no(f, pos);

    if(pos_filho == 0){
        no23* meio = ler_no(f, pai->meio);
        if(meio->num_chaves == 2){
            free(meio);
            free(pai);
            return redistribuir(f, pos, 0);
        }
        else{
            free(meio);
            free(pai);
            return merge(f, cab, pos, 0);
        }
    }
    else if(pos_filho == 1){
        no23* esq = ler_no(f, pai->esq);
        if(esq->num_chaves == 2){
            free(esq);
            free(pai);
            return redistribuir(f, pos, 1);
        }
        free(esq);

        if(pai->dir != -1){
            no23* dir = ler_no(f, pai->dir);
            if(dir->num_chaves == 2){
                free(dir);
                free(pai);

                return redistribuir(f, pos, 1);
            }
        }
        free(pai);
        return merge(f, cab, pos, 1);
    }
    else{
        no23* meio = ler_no(f, pai->meio);

        if(meio->num_chaves == 2){
            free(meio);
            free(pai);
            return redistribuir(f, pos, 2);
        }
        else{
            free(meio);
            free(pai);
            return merge(f, cab, pos, 2);
        }
    }
}

// Funcao para redistribuir chaves
// Pre-condicao: remo��o n�o ocasiona em merge e altera o balanceamento da arvore
// Pos-condicao: retorna ponteiro pai apos redistribui��o
int redistribuir(FILE* f, int pos, int pos_filho)
{
    no23* pai = ler_no(f, pos);

    no23* esq = ler_no(f, pai->esq);
    no23* meio = ler_no(f, pai->meio);
    no23* dir = ler_no(f, pai->dir);
    no23* no_underflow = (pos_filho == 0) ? esq : ((pos_filho == 1) ? meio : dir);

    if(pos_filho == 0){
        no_underflow->chave_esq = pai->chave_esq;
        pai->chave_esq = meio->chave_esq;
        meio->chave_esq = meio->chave_dir;
        meio->chave_dir = 0;
        meio->num_chaves = 1;
        no_underflow->num_chaves = 1;

        if(!eh_folha(f, pai->meio)){
            no_underflow->meio = meio->esq;
            meio->esq = meio->meio;
            meio->meio = meio->dir;
            meio->dir = -1;
        }

        escrever_no(f, no_underflow, pai->esq);
        escrever_no(f, meio, pai->meio);
    }
    else if(pos_filho == 1){
        if(esq->num_chaves == 2){
            no_underflow->meio = no_underflow->esq;
            no_underflow->chave_esq = pai->chave_esq;
            pai->chave_esq = esq->chave_dir;
            esq->chave_dir = 0; esq->num_chaves = 1;
            no_underflow->num_chaves = 1;

            if(!eh_folha(f, pai->esq)){
                no_underflow->esq = esq->dir;
                esq->dir = -1;
            }

            escrever_no(f, no_underflow, pai->meio);
            escrever_no(f, esq, pai->esq);
        }
        else{
            no_underflow->chave_esq = pai->chave_dir;
            pai->chave_dir = dir->chave_esq;
            dir->chave_esq = dir->chave_dir;
            dir->chave_dir = 0;
            dir->num_chaves = 1;

            if(!eh_folha(f, pai->dir)){
                no_underflow->meio = dir->esq;
                dir->esq = dir->meio;
                dir->meio = dir->dir;
                dir->dir = -1;
            }

            escrever_no(f, no_underflow, pai->meio);
            escrever_no(f, dir, pai->dir);
        }
    }
    else{
        no_underflow->meio = no_underflow->esq;
        no_underflow->chave_esq = pai->chave_dir;
        pai->chave_dir = meio->chave_dir;
        meio->chave_dir = 0;
        meio->num_chaves = 1;
        no_underflow->num_chaves = 1;

        if(!eh_folha(f, pai->meio)){
            no_underflow->esq = meio->dir;
            meio->dir = -1;
        }

        escrever_no(f, no_underflow, pai->dir);
        escrever_no(f, meio, pai->meio);
    }
    escrever_no(f, pai, pos);

    free(pai);
    free(esq);
    free(meio);
    free(dir);

    return pos;
}

// Funcao para juntar dois nos
// Pre-condicao: elemento removido
// Pos-condicao: retorna no pai concatenado com outra chave descendente
int merge(FILE* f, cabecalho* cab, int pos, int pos_filho)
{
    no23* pai = ler_no(f, pos);

    if(pos_filho <= 1){
        no23* esq = ler_no(f, pai->esq);
        no23* meio = ler_no(f, pai->meio);

        if(pos_filho == 0){
            esq->chave_esq = pai->chave_esq;
            esq->chave_dir = meio->chave_esq;

            if(!eh_folha(f, pai->meio))
                esq->meio = meio->esq;

            esq->dir = meio->meio;

        }
        else{
            esq->chave_dir = pai->chave_esq;

            if(!eh_folha(f, pai->meio))
                esq->dir = meio->esq;
        }

        esq->num_chaves = 2;
        escrever_no(f, esq, pai->esq);

        free(esq);
        free(meio);

        liberar_pos(f, cab, pai->meio);
        pai->meio = -1;

        pai->chave_esq = pai->chave_dir;
        pai->chave_dir = 0;
        pai->meio = pai->dir;
        pai->dir = -1;
        pai->num_chaves--;
        escrever_no(f, pai, pos);
    }
    else{
        no23* meio = ler_no(f, pai->meio);
        no23* dir = ler_no(f, pai->dir);

        meio->chave_dir = pai->chave_dir;
        meio->num_chaves = 2;

        if(!eh_folha(f, pai->dir))
            meio->dir = dir->esq;

        escrever_no(f, meio, pai->meio);

        free(meio);
        free(dir);

        liberar_pos(f, cab, pai->dir);
        pai->dir = -1;

        pai->chave_dir = 0;
        pai->num_chaves--;
        escrever_no(f, pai, pos);
    }

    free(pai);

    return pos;
}

// Funcao auxiliar para remover elemento
// Pre-condicao: nenhuma
// Pos-condicao: remove elemento e rebalanceia a arvore se necessario
int remover_aux(FILE* f, int chave, int pos, cabecalho* cab)
{
    if(vazia(pos))
        return -1;

    int pos_filho = -1;
    no23* r = ler_no(f, pos);

    if(eh_folha(f, pos)){
        if(r->num_chaves == 2){
            if(r->chave_dir == chave)
                r->chave_dir = 0;

            else if(r->chave_esq == chave){
                r->chave_esq = r->chave_dir;
                r->chave_dir = 0;
            }
            r->num_chaves = 1;

        }
        else
            if(r->chave_esq == chave)
                r->num_chaves = 0;

        escrever_no(f, r, pos);
        free(r);

        return pos;
    }

    if(r->chave_esq == chave || (r->num_chaves == 2 && r->chave_dir == chave)){
        int pos_sucessor;

        if(r->chave_esq == chave){
            pos_sucessor = encontrar_menor(f, r->meio);
            no23* sucessor = ler_no(f, pos_sucessor);
            int chave_sucessor = sucessor->chave_esq;
            free(sucessor);
            r->chave_esq = chave_sucessor;
            r->meio = remover_aux(f, chave_sucessor, r->meio, cab);
            escrever_no(f, r, pos);
            pos_filho = 1;
        }
        else{
            pos_sucessor = encontrar_menor(f, r->dir);
            no23* sucessor = ler_no(f, pos_sucessor);
            int chave_sucessor = sucessor->chave_esq;
            free(sucessor);
            r->chave_dir = chave_sucessor;
            r->dir = remover_aux(f, chave_sucessor, r->dir, cab);
            escrever_no(f, r, pos);
            pos_filho = 2;
        }
    }
    else{
        if(chave < r->chave_esq){
            r->esq = remover_aux(f, chave, r->esq, cab);
            escrever_no(f, r, pos);
            pos_filho = 0;
            free(r);
        }
        else if(r->num_chaves == 1 || chave < r->chave_dir){
            r->meio = remover_aux(f, chave, r->meio, cab);
            escrever_no(f, r, pos);
            pos_filho = 1;
            free(r);
        }
        else{
            r->dir = remover_aux(f, chave, r->dir, cab);
            escrever_no(f, r, pos);
            pos_filho = 2;
            free(r);
        }
    }
    r = ler_no(f, pos);

    if(pos_filho != -1){
        no23* filho = NULL;

        if(pos_filho == 0 && r->esq != -1)
            filho = ler_no(f, r->esq);

        else if(pos_filho == 1 && r->meio != -1)
            filho = ler_no(f, r->meio);

        else if(r->dir != -1)
            filho = ler_no(f, r->dir);

        if(filho != NULL && filho->num_chaves == 0)
            pos = tratar_underflow(f, cab, pos, pos_filho);

        if(filho != NULL)
            free(filho);

        free(r);
    }
    return pos;
}

// Funcao para remover elemento
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void remover(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    if(busca(f, chave, cab->pos_raiz) == -1){
        free(cab);
        return;
    }

    cab->pos_raiz = remover_aux(f, chave, cab->pos_raiz, cab);

    if(cab->pos_raiz != -1 && ler_no(f, cab->pos_raiz)->num_chaves == 0){
        no23* r = ler_no(f, cab->pos_raiz);
        int pos_esq = r->esq;

        liberar_pos(f, cab, cab->pos_raiz);
        cab->pos_raiz = pos_esq;
    }
    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para verificar posicoes livres
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir_livres(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos_livre = cab->pos_livre;
    free(cab);

    while(pos_livre != -1){
        printf("Posicao: %d\n", pos_livre);

        no23* aux = ler_no(f, pos_livre);
        pos_livre = aux->esq;
        free(aux);
    }
}

// Funcao de imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime por niveis
void imprimir_niveis(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_raiz;
    free(cab);

    if(vazia(pos))
        return;

    Fila fila = criar_fila();
    no23* r = ler_no(f, pos);
    no23* aux[10000];
    int j = 0;

    enqueue(fila, r);
    enqueue(fila, NULL);
    aux[j++] = r;

    while(!fila_vazia(fila)){
        no23* atual = dequeue(fila);

        if(atual == NULL){
            printf("\n");

            if(!fila_vazia(fila))
                enqueue(fila, NULL);
        }

        else{
            printf("[%d", atual->chave_esq);

            if(atual->num_chaves == 2)
                printf(",%d] ", atual->chave_dir);

            else
                printf(",-] ");

            if(atual->esq != -1){
                r = ler_no(f, atual->esq);
                enqueue(fila, r);
                aux[j++] = r;
            }

            if(atual->meio != -1){
                r = ler_no(f, atual->meio);
                enqueue(fila, r);
                aux[j++] = r;
            }

            if(atual->dir != -1){
                r = ler_no(f, atual->dir);
                enqueue(fila, r);
                aux[j++] = r;
            }
        }
    }

    while(j >= 0)
        free(aux[--j]);
}
