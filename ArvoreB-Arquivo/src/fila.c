#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

struct no{
    noB* r;
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

boolean fila_vazia(Fila f)
{
    if(f->primeiro == NULL)
        return true;

    return false;
}

boolean consultar_nulo(Fila f)
{
    if(f->primeiro->r == NULL)
        return true;

    return false;
}

void enqueue(Fila f, noB* r)
{
    struct no* aux = malloc(sizeof(struct no));
    aux->r = r;
    aux->prox = NULL;

    if(fila_vazia(f))
        f->primeiro = aux;
    else
        f->ultimo->prox = aux;

    f->ultimo = aux;
}

noB* dequeue(Fila f)
{
    noB* r = f->primeiro->r;
    struct no* aux = f->primeiro;

    f->primeiro = f->primeiro->prox;
    free(aux);

    return r;
}
