#ifndef LISTA_ENCADEADA_CIRCULAR_H_
#define LISTA_ENCADEADA_CIRCULAR_H_

typedef struct lista* Lista;
typedef struct lista Elem;

Lista* criar_lista();

void* liberar_lista(Lista* l);

void inserir_elemento(Lista* l, int info);

void remover_elemento(Lista* l, int info);

int buscar_elemento(Lista* l, int info);

void imprimir_lista(Lista* l);

#endif // LISTA_ENCADEADA_CIRCULAR_H_
