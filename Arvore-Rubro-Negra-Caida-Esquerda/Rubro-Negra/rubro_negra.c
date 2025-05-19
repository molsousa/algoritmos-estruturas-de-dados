#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

struct no{
    int info;
    int cor;
    struct no* esq;
    struct no* dir;
};

static void liberar_arvore_cauda(No* raiz);
static No* inserir_no_cauda(No* raiz, int info, int* resultado);

ArvoreRN* criar_arvore()
{
    ArvoreRN* novo;

    novo = (ArvoreRN*) malloc(sizeof(ArvoreRN));
    *novo = NULL;

    return novo;
}

ArvoreRN* liberar_arvore(ArvoreRN* raiz)
{
    if(raiz == NULL)
        return raiz;

    liberar_arvore_cauda(*raiz);
    free(raiz);

    return NULL;
}
static void liberar_arvore_cauda(No* raiz)
{
    if(raiz == NULL)
        return;

    liberar_arvore_cauda(raiz->esq);
    liberar_arvore_cauda(raiz->dir);

    free(raiz);
}

int cor(No* no)
{
    if(no == NULL)
        return PRETO;

    else
        return no->cor;
}

void troca_cor(No* no)
{
    no->cor = !no->cor;

    if(no->esq != NULL)
        no->esq->cor = !no->esq->cor;

    if(no->dir != NULL)
        no->dir->cor = !no->dir->cor;
}

No* rotacionar_esquerda(No* no)
{
    No* aux = no->dir;

    no->dir = aux->esq;
    aux->esq = no;
    aux->cor = no->cor;
    no->cor = VERMELHO;

    return aux;
}

No* rotacionar_direita(No* no)
{
    No* aux = no->esq;

    no->esq = aux->dir;
    aux->dir = no;
    aux->cor = no->cor;
    no->cor = VERMELHO;

    return aux;
}

int inserir_no(ArvoreRN* raiz, int info)
{
    int resultado;

    *raiz = inserir_no_cauda(*raiz, info, &resultado);
    if(*raiz != NULL)
        (*raiz)->cor = PRETO;

    return resultado;
}

static No* inserir_no_cauda(No* raiz, int info, int* resultado)
{
    if(raiz == NULL){
        No* novo = (No*) malloc(sizeof(No));
        novo->info = info;
        novo->esq = NULL;
        novo->dir = NULL;

        novo->cor = VERMELHO;
        *resultado = 1;
        return novo;
    }
    else if(info < raiz->info)
        raiz->esq = inserir_no_cauda(raiz->esq, info, resultado);

    else if(info > raiz->info)
        raiz->dir = inserir_no_cauda(raiz->dir, info, resultado);

    if(cor(raiz->dir) == VERMELHO && cor(raiz->esq) == PRETO)
        raiz = rotacionar_esquerda(raiz);

    if(cor(raiz->esq) == VERMELHO && cor(raiz->esq->esq) == VERMELHO)
        raiz = rotacionar_direita(raiz);

    if(cor(raiz->esq) == VERMELHO && cor(raiz->dir) == VERMELHO)
        troca_cor(raiz);

    return raiz;
}

void imprimir_arvore(ArvoreRN* raiz)
{
    if(*raiz == NULL)
        return;

    printf("%d ", (*raiz)->info);

    if((*raiz)->cor == VERMELHO)
        printf("RUBRO\n");

    else
        printf("NEGRO\n");

    imprimir_arvore(&(*raiz)->esq);
    imprimir_arvore(&(*raiz)->dir);
}
