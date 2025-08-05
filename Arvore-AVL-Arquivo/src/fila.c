#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

struct lista{
    no* x;
    struct lista* prox;
};

struct fila{
    struct lista* primeiro;
    struct lista* ultimo;
};

Fila criar_fila()
{
    Fila f = malloc(sizeof(struct fila));

    f->primeiro = f->ultimo = NULL;

    return f;
}

int fila_vazia(Fila f)
{
    return (f->primeiro == NULL);
}

int consultar_nulo(Fila f)
{
    if(f->primeiro == NULL)
        return true;

    return false;
}

void enqueue(Fila f, no* x)
{
    struct lista* novo = malloc(sizeof(struct lista));
    novo->x = x;
    novo->prox = NULL;

    if(fila_vazia(f))
        f->primeiro = novo;

    else
        f->ultimo->prox = novo;

    f->ultimo = novo;
}

no* dequeue(Fila f)
{
    no* x = f->primeiro->x;
    struct lista* aux = f->primeiro;

    f->primeiro = f->primeiro->prox;
    free(aux);

    return x;
}
