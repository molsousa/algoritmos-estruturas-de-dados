#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include "avl.h"

typedef struct fila* Fila;

Fila criar_fila();

int fila_vazia(Fila);

int consultar_nulo(Fila);

void enqueue(Fila, no*);

no* dequeue(Fila);

#endif // FILA_H_INCLUDED
