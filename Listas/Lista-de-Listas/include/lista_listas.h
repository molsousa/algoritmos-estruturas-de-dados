#ifndef _LISTA_DE_LISTAS_H_INCLUDED
#define _LISTA_DE_LISTAS_H_INCLUDED

#include "lista.h"

typedef struct no_listas Lista_Listas;

Lista_Listas* criar();

int vazia(Lista_Listas*);

Lista_Listas* inserir(Lista_Listas*, int, Lista);

Lista_Listas* remover(Lista_Listas*, int);

void imprimir(Lista_Listas*);

#endif
