#ifndef _LISTA_ENCADEADA_H_INCLUDED
#define _LISTA_ENCADEADA_H_INCLUDED

typedef struct no* Lista;

Lista criar_lista();

int lista_vazia(Lista);

void liberar_lista(Lista);

Lista inserir_no(Lista, int);

Lista copiar_lista(Lista);

Lista remover_no(Lista, int);

void imprimir_lista(Lista);

#endif
