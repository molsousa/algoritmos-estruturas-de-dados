#include <stdlib.h>
#include "../include/avl.h"
#include "../include/fila.h"

// Funcao para ler cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: nenhuma
cabecalho* ler_cabecalho(FILE* fr)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(fr, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, fr);

    return cab;
}

// Funcao para escrever cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: atualiza cabecalho
void escrever_cabecalho(FILE* fr, cabecalho* cab)
{
    fseek(fr, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, fr);
}

// Funcao para ler no
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
no* ler_no(FILE* fr, int pos)
{
    no* x = malloc(sizeof(no));

    fseek(fr, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fread(x, sizeof(no), 1, fr);

    return x;
}

// Funcao para escrever no
// Pre-condicao: arvore criada
// Pos-condicao: atualiza no
void escrever_no(FILE* fr, no* x, int pos)
{
    fseek(fr, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fwrite(x, sizeof(no), 1, fr);
}

// Funcao para criar arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: cria arvore em arquivo binario
void inicializar(FILE* fr)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(fr, cab);
    free(cab);
}

// Funcao para verificar se um no eh vazio
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
boolean vazia(int pos)
{
    return (pos == -1);
}

// Funcao para verificar altura da arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int altura(FILE* fr, int pos)
{
    if(vazia(pos))
        return -1;

    else{
        no* aux = ler_no(fr, pos);
        int esq = altura(fr, aux->esq);
        int dir = altura(fr, aux->dir);

        free(aux);
        if(esq > dir)
            return (esq+1);

        else
            return (dir+1);
    }

    return 0;
}

// Funcao para verificar fator de balanceamento
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int fator_balanceamento(FILE* fr, no* x)
{
    return labs(altura(fr, x->esq) - altura(fr, x->dir));
}

// Funcao para procurar menor valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int procurar_menor(FILE* fr, int pos)
{
    no* x = ler_no(fr, pos);
    int chave;

    while(!vazia(x->esq)){
        pos = x->esq;
        free(x);
        ler_no(fr, pos);
    }
    chave = x->chave;
    free(x);

    return chave;
}

// Funcao para procurar maior valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int procurar_maior(FILE* fr, int pos)
{
    no* x = ler_no(fr, pos);
    int chave;

    while(x->dir != -1){
        pos = x->dir;
        free(x);
        ler_no(fr, pos);
    }
    chave = x->chave;
    free(x);

    return chave;
}

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona o no a esquerda
int rotacaoLL(FILE* fr, int pos)
{
    no* u = ler_no(fr, pos);
    no* y = ler_no(fr, u->esq);
    int pos_y = u->esq;

    u->esq = y->dir;
    y->dir = pos;

    escrever_no(fr, u, pos);
    escrever_no(fr, y, pos_y);

    u->fb = maior(altura(fr, u->esq), altura(fr, u->dir)) + 1;
    y->fb = maior(altura(fr, y->esq), altura(fr, u->fb)) + 1;

    escrever_no(fr, u, pos);
    escrever_no(fr, y, pos_y);

    free(u);
    free(y);

    return pos_y;
}

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona o no a direita
int rotacaoRR(FILE* fr, int pos)
{
    no* u = ler_no(fr, pos);
    no* y = ler_no(fr, u->dir);
    int pos_y = u->dir;

    u->dir = y->esq;
    y->esq = pos;

    escrever_no(fr, u, pos);
    escrever_no(fr, y, pos_y);

    u->fb = maior(altura(fr, u->esq), altura(fr, u->dir)) + 1;
    y->fb = maior(altura(fr, y->dir), altura(fr, u->fb)) + 1;

    escrever_no(fr, u, pos);
    escrever_no(fr, y, pos_y);

    free(u);
    free(y);

    return pos_y;
}

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona duplamente o no alvo
int rotacaoLR(FILE* fr, int pos)
{
    no* x = ler_no(fr, pos);

    x->esq = rotacaoRR(fr, x->esq);
    escrever_no(fr, x, pos);

    free(x);

    return rotacaoLL(fr, pos);
}

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona duplamente o no alvo
int rotacaoRL(FILE* fr, int pos)
{
    no* x = ler_no(fr, pos);

    x->dir = rotacaoLL(fr, x->dir);
    escrever_no(fr, x, pos);

    free(x);

    return rotacaoRR(fr, pos);
}

// Funcao para inserir chave
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void inserir(FILE* fr, int chave)
{
    if(busca(fr, chave))
        return;

    cabecalho* cab = ler_cabecalho(fr);

    cab->pos_raiz = inserir_aux(fr, chave, cab, cab->pos_raiz);
    escrever_cabecalho(fr, cab);

    free(cab);
}

// Funcao auxiliar para inserir chave
// Pre-condicao: nenhuma
// Pos-condicao: insere chave na arvore
int inserir_aux(FILE* fr, int chave, cabecalho* cab, int pos)
{
    if(pos == -1){
        no novo;

        novo.chave = chave;
        novo.esq = novo.dir = -1;
        novo.fb = 0;

        if(cab->pos_livre == -1){
            escrever_no(fr, &novo, cab->pos_topo);
            return cab->pos_topo++;
        }
        else{
            no* livre = ler_no(fr, cab->pos_livre);
            int pos_livre = cab->pos_livre;
            cab->pos_livre = livre->esq;

            escrever_no(fr, &novo, pos_livre);
            return pos_livre;
        }
    }

    no* aux = ler_no(fr, pos);

    if(chave < aux->chave){
        aux->esq = inserir_aux(fr, chave, cab, aux->esq);

        if(fator_balanceamento(fr, aux) > 1){
            if(chave < ler_no(fr, aux->esq)->chave){
                pos = rotacaoLL(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }

            else{
                pos = rotacaoLR(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }
        }
    }

    else{
        aux->dir = inserir_aux(fr, chave, cab, aux->dir);

        if(fator_balanceamento(fr, aux) > 1){
            if(chave > ler_no(fr, aux->dir)->chave){
                pos = rotacaoRR(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }

            else{
                pos = rotacaoRL(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }
        }
    }

    aux->fb = maior(altura(fr, aux->esq), altura(fr, aux->dir)) + 1;
    escrever_no(fr, aux, pos);
    free(aux);

    return pos;
}

// Funcao para remover chave
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void remover(FILE* fr, int chave)
{
    if(!busca(fr, chave))
        return;

    cabecalho* cab = ler_cabecalho(fr);
    cab->pos_raiz = remover_aux(fr, chave, cab, cab->pos_raiz);

    escrever_cabecalho(fr, cab);
    free(cab);
}

// Funcao auxiliar para remover chave
// Pre-condicao: nenhuma
// Pos-condicao: remove no buscado (se constar)
int remover_aux(FILE* fr, int chave, cabecalho* cab, int pos)
{
    no* aux = ler_no(fr, pos);

    if(chave > aux->chave){
        aux->dir = remover_aux(fr, chave, cab, aux->dir);
        escrever_no(fr, aux, pos);

        if(fator_balanceamento(fr, aux) > 1){
            if(altura(fr, ler_no(fr, aux->esq)->dir) <= altura(fr, ler_no(fr, aux->esq)->esq)){
                pos = rotacaoLL(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }

            else{
                pos = rotacaoLR(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }
        }
    }

    else if(chave < aux->chave){
        aux->esq = remover_aux(fr, chave, cab, aux->esq);
        escrever_no(fr, aux, pos);

        if(fator_balanceamento(fr, aux) > 1){
            if(altura(fr, ler_no(fr, aux->dir)->esq) <= altura(fr, ler_no(fr, aux->dir)->dir)){
                pos = rotacaoRR(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }

            else{
                pos = rotacaoRL(fr, pos);
                free(aux);
                aux = ler_no(fr, pos);
            }
        }
    }
    else{
        if(aux->esq == -1 && aux->dir == -1){
            aux->dir = aux->esq = cab->pos_livre;
            cab->pos_livre = pos;
            escrever_no(fr, aux, pos);
            return -1;
        }
        else if(aux->esq == -1){
            aux->chave = procurar_menor(fr, aux->dir);
            escrever_no(fr, aux, pos);
            aux->dir = remover_aux(fr, aux->chave, cab, aux->dir);
        }
        else{
            aux->chave = procurar_maior(fr, aux->esq);
            escrever_no(fr, aux, pos);
            aux->esq = remover_aux(fr, aux->chave, cab, aux->esq);
        }
    }

    aux->fb = maior(altura(fr, aux->esq), altura(fr, aux->dir)) + 1;
    escrever_no(fr, aux, pos);
    free(aux);

    return pos;
}

// Funcao para busca
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
boolean busca(FILE* fr, int chave)
{
    cabecalho* cab = ler_cabecalho(fr);

    boolean existe = busca_aux(fr, chave, cab->pos_raiz);
    free(cab);

    return existe;
}

// Funcao auxiliar para busca
// Pre-condicao: nenhuma
// Pos-condicao: retorna true se a chave constar
boolean busca_aux(FILE* fr, int chave, int pos)
{
    if(pos == -1)
        return false;

    no* x = ler_no(fr, pos);

    if(chave > x->chave){
        pos = x->dir;
        free(x);
        return busca_aux(fr, chave, pos);
    }
    else if(chave < x->chave){
        pos = x->esq;
        free(x);
        return busca_aux(fr, chave, pos);
    }
    else{
        free(x);
        return true;
    }

    return false;
}

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir(FILE* fr)
{
    cabecalho* cab = ler_cabecalho(fr);

    imprimir_aux(fr, cab->pos_raiz);
    free(cab);
}

// Funcao auxiliar para imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_aux(FILE* fr, int pos)
{
    if(pos == -1)
        return;

    no* aux = ler_no(fr, pos);

    printf("%d\n", aux->chave);

    imprimir_aux(fr, aux->esq);
    imprimir_aux(fr, aux->dir);

    free(aux);
}

// Funcao para imprimir registros lvires
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir_livres(FILE* fr)
{
    cabecalho* cab = ler_cabecalho(fr);

    while(cab->pos_livre != -1){
        no* aux = ler_no(fr, cab->pos_livre);

        printf("Posicao: %d\n", cab->pos_livre);

        cab->pos_livre = aux->esq;
        free(aux);
    }
    free(cab);
}

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir_niveis(FILE* fr)
{
    cabecalho* cab = ler_cabecalho(fr);
    int pos = cab->pos_raiz;
    free(cab);

    no* aux[10000];
    int inicio, fim, cont, i;
    fim = inicio = 0;

    aux[fim++] = ler_no(fr, pos);

    while(fim > inicio){
        cont = fim - inicio;

        printf("<");
        for(i = 0; i < cont; i++){
            no* atual = aux[inicio];

            printf("%d", atual->chave);

            if(atual->esq != -1)
                aux[fim++] = ler_no(fr, atual->esq);

            if(atual->dir != -1)
                aux[fim++] = ler_no(fr, atual->dir);

            if(i+1 < cont)
                printf(" ");

            inicio++;
        }
        printf(">\n");
    }

    while(fim >= 0)
        free(aux[--fim]);
}
