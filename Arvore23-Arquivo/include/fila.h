#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include "arvore23.h"

typedef struct fila* Fila;

Fila criar_fila();

boolean fila_vazia(Fila);

void enqueue(Fila, no23*);

no23* dequeue(Fila);

#endif // FILA_H_INCLUDED
