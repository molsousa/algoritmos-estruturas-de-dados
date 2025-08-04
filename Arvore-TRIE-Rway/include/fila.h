#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct fila* Fila;

Fila criar_fila();

int fila_vazia(Fila);

char consultar_topo(Fila f);

void enqueue(Fila, char);

char dequeue(Fila);

#endif // FILA_H_INCLUDED
