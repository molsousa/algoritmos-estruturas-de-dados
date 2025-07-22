#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

// Estrutura para lista encadeada
struct lista{
    struct noAVL* x;
    struct lista* prox;
};

// Estrutura para fila
struct fila{
    struct lista* primeiro;
    struct lista* ultimo;
};

// Funcao para criar fila
// Pre-condicao: nenhuma
// Pos-condicao: cria nova fila
Fila criar_fila()
{
    Fila f = (Fila) malloc(sizeof(struct fila));
    f->primeiro = f->ultimo = NULL;

    return f;
}

// Funcao para verificar se uma fila eh vazia
// Pre-condicao: fila criada
// Pos-condicao: retorna 1 se vazia
int fila_vazia(Fila f)
{
    return (f->primeiro == NULL);
}

// Funcao para verificar se um elemento eh nulo
// Pre-condicao: fila criada
// Pos-condicao: retorna 1 se elemento atual eh nulo
int consultar_nulo(Fila f)
{
    return (f->primeiro->x == NULL);
}

// Funcao para liberar fila
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo apos liberar elementos
void* liberar_fila(Fila f)
{
    while(!fila_vazia(f))
        dequeue(f);

    return NULL;
}

// Funcao para enfilerar elemento
// Pre-condicao: fila criada
// Pos-condicao: nenhuma
void enqueue(Fila f, struct noAVL* x)
{
    struct lista* novo = (struct lista*) malloc(sizeof(struct lista));
    novo->x = x;
    novo->prox = NULL;

    if(fila_vazia(f))
        f->primeiro = novo;
    else
        f->ultimo->prox = novo;

    f->ultimo = novo;
}

// Funcao para defilerar elemento
// Pre-condicao: fila criada
// Pos-condicao: retorna elemento defilerado
struct noAVL* dequeue(Fila f)
{
    struct noAVL* x = f->primeiro->x;
    struct lista* aux = f->primeiro;

    f->primeiro = f->primeiro->prox;
    free(aux);

    return x;
}
