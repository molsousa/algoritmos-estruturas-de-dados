#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Estrutura para arvore
struct arvore{
    Tipo info;
    struct arvore* esq;
    struct arvore* dir;
};

// Funcao para liberar arvore binaria
static void liberar_no(No* raiz);
// Funcao para contar a quantidade de elementos de uma arvore
static int contar_elementos(No* raiz, int n);
// Funcao para contar a quantidade de folhas de uma arvore
static int contar_folha(No* raiz);
// Funcao de busca binaria na arvore
static int buscar(No* raiz, Tipo x);
// Funcao para imprimir a arvore ordenada
static void imprimir_ord(No* raiz);
// Funcao para imprimir a arvore pre-ordenada
static void imprimir_pre(No* raiz);
// Funcao para imprimir a arvore pos-ordenada
static void imprimir_pos(No* raiz);

// Funcao para criar arvore binaria
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna arvore vazia
Arvore* criar_arvore()
{
    Arvore* novo;

    novo = (Arvore*) malloc(sizeof(Arvore));
    *novo = NULL;

    return novo;
}

// Funcao para liberar arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro Arvore
Arvore* liberar_arvore(Arvore* raiz)
{
    if(raiz == NULL)
        return raiz;

    liberar_no(*raiz);

    return NULL;
}

// Funcao para liberar arvore binaria
static void liberar_no(No* raiz)
{
    if(raiz == NULL)
        return;

    liberar_no(raiz->esq);
    liberar_no(raiz->dir);

    free(raiz);
}

// Funcao para verificar condicao da arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int arvore_vazia(Arvore* raiz)
{
    return (*raiz == NULL);
}

// Funcao para contar a quantidade de elementos de uma arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna a quantidade de elementos
int quantidade_elementos(Arvore* raiz)
{
    if(raiz == NULL || *raiz == NULL)
        return 0;

    return contar_elementos(*raiz, 0);
}

// Funcao para contar a quantidade de elementos de uma arvore
static int contar_elementos(No* raiz, int n)
{
    if(raiz == NULL)
        return n;

    n = contar_elementos(raiz->esq, n+1);
    n = contar_elementos(raiz->dir, n);

    return n;
}

// Funcao para contar a quantidade de folhas de uma arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna a quantidade de folhas
int quantidade_folha(Arvore* raiz)
{
    if(raiz == NULL || *raiz == NULL)
        return 0;

    return contar_folha(*raiz);
}

// Funcao para contar a quantidade de folhas de uma arvore
static int contar_folha(No* raiz)
{
    if(raiz == NULL)
        return 0;

    if(!raiz->esq && !raiz->dir)
        return 1;

    return contar_folha(raiz->esq) + contar_folha(raiz->dir);
}

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void inserir_no(Arvore* raiz, Tipo x)
{
    if((*raiz) == NULL){
        No* novo = (No*) malloc(sizeof(No));
        novo->info = x;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
    }

    else if(x < (*raiz)->info)
        inserir_no(&(*raiz)->esq, x);
    else
        inserir_no(&(*raiz)->dir, x);
}

// Funcao para remover elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: em caso de dois filhos, remocao in-order (menor subarvore direita)
void remover_no(Arvore* raiz, Tipo x)
{
    if(*raiz == NULL)
        return;

    if(x < (*raiz)->info)
        remover_no(&(*raiz)->esq, x);

    else if(x > (*raiz)->info)
        remover_no(&(*raiz)->dir, x);

    else{
        No* aux = *raiz;

        if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
            free(*raiz);
            *raiz = NULL;
        }
        else if((*raiz)->esq == NULL){
            *raiz = (*raiz)->dir;
            free(aux);
        }
        else if((*raiz)->dir == NULL){
            *raiz = (*raiz)->esq;
            free(aux);
        }
        else{
            No* t = (*raiz)->dir;

            while(t->esq != NULL)
                t = t->esq;

            (*raiz)->info = t->info;
            remover_no(&(*raiz)->dir, t->info);
        }
    }
}

// Funcao de busca binaria na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se achou o elemento
int busca_arvore(Arvore* raiz, Tipo x)
{
    return buscar(*raiz, x);
}

// Funcao de busca binaria na arvore
static int buscar(No* raiz, Tipo x)
{
    if(raiz == NULL)
        return 0;

    if(raiz->info == x)
        return 1;

    else if(raiz->info > x)
        return buscar(raiz->esq, x);

    else
        return buscar(raiz->dir, x);
}

// Funcao para imprimir a arvore pre-ordenada
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore_pre(Arvore* raiz)
{
    imprimir_pre(*raiz);
}

// Funcao para imprimir a arvore pre-ordenada
static void imprimir_pre(No* raiz)
{
    if(raiz == NULL)
        return;

    printf("%d\n", raiz->info);
    imprimir_pre(raiz->esq);
    imprimir_pre(raiz->dir);
}

// Funcao para imprimir a arvore ordenada
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore_ord(Arvore* raiz)
{
    imprimir_ord(*raiz);
}

// Funcao para imprimir a arvore ordenada
static void imprimir_ord(No* raiz)
{
    if(raiz == NULL)
        return;

    imprimir_ord(raiz->esq);
    printf("%d\n", raiz->info);
    imprimir_ord(raiz->dir);
}

// Funcao para imprimir a arvore pos-ordenada
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore_pos(Arvore* raiz)
{
    imprimir_pos(*raiz);
}

// Funcao para imprimir a arvore pos-ordenada
static void imprimir_pos(No* raiz)
{
    if(raiz == NULL)
        return;

    imprimir_pos(raiz->esq);
    imprimir_pos(raiz->dir);
    printf("%d\n", raiz->info);
}
