#ifndef LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED
#define LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED

typedef struct lista Elem;
typedef struct lista* Lista;

Lista* criar_lista();

Lista* liberar_lista(Lista* l);

void inserir_elemento(Lista* l, int info);

void remover_elemento(Lista* l, int info);

void imprimir_lista(Lista* l);

void imprimir_ida_volta(Lista* l);

#endif // LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED
