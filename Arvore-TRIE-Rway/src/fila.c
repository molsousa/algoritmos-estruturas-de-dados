#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

struct no{
    char c;
    struct no* prox;
};

struct fila{
    struct no* primeiro;
    struct no* ultimo;
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

char consultar_topo(Fila f)
{
    return f->primeiro->c;
}

void enqueue(Fila f, char c)
{
    struct no* novo = malloc(sizeof(struct no));
    novo->c = c;
    novo->prox = NULL;

    if(fila_vazia(f))
        f->primeiro = novo;

    else
        f->ultimo->prox = novo;

    f->ultimo = novo;
}

char dequeue(Fila f)
{
    char c = f->primeiro->c;
    struct no* aux = f->primeiro;

    f->primeiro = f->primeiro->prox;
    free(aux);

    return c;
}
