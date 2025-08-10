#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

struct no{
    no23* r;
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

void enqueue(Fila f, no23* r)
{
    struct no* aux = malloc(sizeof(struct no));
    aux->r = r;
    aux->prox = NULL;

    if(f->primeiro == NULL)
        f->primeiro = aux;

    else
        f->ultimo->prox = aux;

    f->ultimo = aux;
}

no23* dequeue(Fila f)
{
    no23* r = f->primeiro->r;
    struct no* aux = f->primeiro;

    f->primeiro = f->primeiro->prox;
    free(aux);

    return r;
}
