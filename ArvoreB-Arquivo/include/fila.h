#ifndef _FILA_H_INCLUDED
#define _FILA_H_INCLUDED

#include "arvoreb.h"

typedef struct fila* Fila;

Fila criar_fila();

boolean fila_vazia(Fila);

boolean consultar_nulo(Fila);

void enqueue(Fila, noB*);

noB* dequeue(Fila);

#endif // _FILA_H_INCLUDED
