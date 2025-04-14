#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "Balanceamento/balanceamento.h"

// Funcao para liberar arvore AVL
static void liberar_no(No_AVL* raiz);

// Funcao para criar arvore AVL
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna arvore vazia
Arvore_AVL* criar_arvore()
{
    Arvore_AVL* novo;

    novo = (Arvore_AVL*) malloc(sizeof(Arvore_AVL));
    *novo = NULL;

    return novo;
}

// Funcao para liberar arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro vazio
void* liberar_arvore(Arvore_AVL* raiz)
{
    if(raiz == NULL)
        return raiz;

    liberar_no(*raiz);

    return NULL;
}

// Funcao para liberar arvore AVL
static void liberar_no(No_AVL* raiz)
{
    if(!raiz)
        return;

    liberar_no(raiz->esq);
    liberar_no(raiz->dir);
    free(raiz);
}

// Funcao para inserir elemento na arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int inserir_elemento(Arvore_AVL* raiz, int info)
{
    int res;

    if(*raiz == NULL){
        No_AVL* novo = (No_AVL*) malloc(sizeof(No_AVL));
        novo->info = info;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;

        *raiz = novo;
        return 1;
    }

    No_AVL* aux = *raiz;

    if(info < aux->info){
        if((res = inserir_elemento(&(aux->esq), info)) == 1){
            if(fator_balanceamento(aux) > 1){
                if(info < (*raiz)->esq->info)
                    rotacao_ll(raiz);
                else
                    rotacao_lr(raiz);
            }
        }
    }
    else{
        if(info > aux->info){
            if((res = inserir_elemento(&(aux->dir), info)) == 1){
                if(fator_balanceamento(aux) > 1){
                    if(info > (*raiz)->dir->info)
                        rotacao_rr(raiz);
                    else
                        rotacao_rl(raiz);
                }
            }
        }
    }

    aux->altura = maior(altura_no(aux->esq), altura_no(aux->dir)) + 1;

    return res;
}

// Funcao para remover elemento da arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int remover_elemento(Arvore_AVL* raiz, int info)
{
    if(*raiz == NULL)
        return 0;

    int res;

    if(info < (*raiz)->info){
        if((res = remover_elemento(&(*raiz)->esq, info)) == 1){
            if(fator_balanceamento(*raiz) > 1){
                if(altura_no((*raiz)->dir->esq) <= altura_no((*raiz)->dir->dir))
                    rotacao_rr(raiz);
                else
                    rotacao_rl(raiz);
            }
        }
    }
    if(info > (*raiz)->info){
        if((res = remover_elemento(&(*raiz)->dir, info)) == 1){
            if(fator_balanceamento(*raiz) > 1){
                if(altura_no((*raiz)->esq->dir) <= altura_no((*raiz)->esq->esq))
                    rotacao_ll(raiz);
                else
                    rotacao_lr(raiz);
            }
        }
    }

    if((*raiz)->info == info){
        No_AVL* aux = *raiz;

        if(!aux->esq && !aux->dir){
            free(aux);
            *raiz = NULL;
        }
        else if(!aux->esq && aux->dir){
            (*raiz) = (*raiz)->dir;
            free(aux);
        }
        else if(aux->esq && !aux->dir){
            (*raiz) = (*raiz)->esq;
            free(aux);
        }
        else{
            aux = procura_menor((*raiz)->dir);
            (*raiz)->info = aux->info;
            remover_elemento(&(*raiz)->dir, (*raiz)->info);

            if(fator_balanceamento(*raiz) > 1){
                if(altura_no((*raiz)->esq->dir) <= altura_no((*raiz)->esq->esq))
                   rotacao_ll(raiz);
                else
                    rotacao_lr(raiz);
            }
        }

        if(*raiz != NULL)
            (*raiz)->altura = maior(altura_no((*raiz)->esq), altura_no((*raiz)->dir)) + 1;
        return 1;
    }

    (*raiz)->altura = maior(altura_no((*raiz)->esq), altura_no((*raiz)->dir)) + 1;

    return res;
}

// Funcao para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore(Arvore_AVL* raiz)
{
    if(raiz == NULL)
        return;

    if(*raiz == NULL)
        return;

    printf("%d\n", (*raiz)->info);

    imprimir_arvore(&(*raiz)->esq);
    imprimir_arvore(&(*raiz)->dir);
}
