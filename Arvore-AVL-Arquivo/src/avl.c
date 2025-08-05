#include <stdlib.h>
#include "../include/avl.h"
#include "../include/fila.h"

cabecalho* ler_cabecalho(FILE* fr)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(fr, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, fr);

    return cab;
}

void escrever_cabecalho(FILE* fr, cabecalho* cab)
{
    fseek(fr, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, fr);
}

no* ler_no(FILE* fr, int pos)
{
    no* x = malloc(sizeof(no));

    fseek(fr, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fread(x, sizeof(no), 1, fr);

    return x;
}

void escrever_no(FILE* fr, no* x, int pos)
{
    fseek(fr, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fwrite(x, sizeof(no), 1, fr);
}

void inicializar(FILE* fr)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(fr, cab);
    free(cab);
}

int altura(FILE* fr, int pos)
{
    if(pos == -1)
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

int fator_balanceamento(FILE* fr, no* x)
{
    return labs(altura(fr, x->esq) - altura(fr, x->dir));
}

int procurar_menor(FILE* fr, int pos)
{
    no* x = ler_no(fr, pos);
    int chave;

    while(x->esq != -1){
        pos = x->esq;
        free(x);
        ler_no(fr, pos);
    }
    chave = x->chave;
    free(x);

    return chave;
}

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

int rotacaoLR(FILE* fr, int pos)
{
    no* x = ler_no(fr, pos);

    x->esq = rotacaoRR(fr, x->esq);
    escrever_no(fr, x, pos);

    free(x);

    return rotacaoLL(fr, pos);
}

int rotacaoRL(FILE* fr, int pos)
{
    no* x = ler_no(fr, pos);

    x->dir = rotacaoLL(fr, x->dir);
    escrever_no(fr, x, pos);

    free(x);

    return rotacaoRR(fr, pos);
}

void inserir(FILE* fr, int chave)
{
    if(busca(fr, chave))
        return;

    cabecalho* cab = ler_cabecalho(fr);

    cab->pos_raiz = inserir_aux(fr, chave, cab, cab->pos_raiz);
    escrever_cabecalho(fr, cab);

    free(cab);
}

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

void remover(FILE* fr, int chave)
{
    if(!busca(fr, chave))
        return;

    cabecalho* cab = ler_cabecalho(fr);
    cab->pos_raiz = remover_aux(fr, chave, cab, cab->pos_raiz);

    escrever_cabecalho(fr, cab);
    free(cab);
}

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

bool busca(FILE* fr, int chave)
{
    cabecalho* cab = ler_cabecalho(fr);

    bool existe = busca_aux(fr, chave, cab->pos_raiz);
    free(cab);

    return existe;
}

bool busca_aux(FILE* fr, int chave, int pos)
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

void imprimir(FILE* fr)
{
    cabecalho* cab = ler_cabecalho(fr);

    imprimir_aux(fr, cab->pos_raiz);
    free(cab);
}

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

void imprimir_niveis(FILE* fr)
{
    cabecalho* cab = ler_cabecalho(fr);
    int pos = cab->pos_raiz;
    Fila f = criar_fila();
    no* aux[1000];
    int i = 0;

    no* x = ler_no(fr, pos);
    aux[i++] = x;

    enqueue(f, x);
    enqueue(f, NULL);
    printf("<");

    while(!fila_vazia(f)){
        no* atual = dequeue(f);

        if(atual == NULL){
            printf(">\n");

            if(!fila_vazia(f)){
                enqueue(f, NULL);
                printf("<");
            }
        }

        else{
            printf("%d", atual->chave);

            if(atual->esq != -1){
                no* x = ler_no(fr, atual->esq);
                aux[i++] = x;
                enqueue(f, x);
            }
            if(atual->dir != -1){
                no* x = ler_no(fr, atual->dir);
                aux[i++] = x;
                enqueue(f, x);
            }
            if(!consultar_nulo(f))
                printf(", ");
        }
    }
    free(f);
    i--;

    while(i >= 0)
        free(aux[i--]);
}
