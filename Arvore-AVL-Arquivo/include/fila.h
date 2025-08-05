#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include "avl.h"

typedef struct fila* Fila;

Fila criar_fila();

bool fila_vazia(Fila);

bool consultar_nulo(Fila);

void enqueue(Fila, no*);

no* dequeue(Fila);

#endif // FILA_H_INCLUDED
