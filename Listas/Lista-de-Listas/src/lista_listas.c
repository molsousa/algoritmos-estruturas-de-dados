#include <stdio.h>
#include <stdlib.h>
#include "../include/lista_listas.h"

struct no_listas{
    Lista lista;
    int identificador;
    struct no_listas* prox;
};

Lista_Listas* criar()
{
    return NULL;
}

int vazia(Lista_Listas* l)
{
    return (l == NULL);
}

Lista_Listas* inserir(Lista_Listas* l, int identificador, Lista lista)
{
    Lista_Listas* aux = malloc(sizeof(Lista_Listas));

    aux->lista = copiar_lista(lista);
    aux->identificador = identificador;
    aux->prox = l;

    return aux;
}

Lista_Listas* remover(Lista_Listas* l, int identificador)
{
    if(vazia(l))
        return l;

    if(l->identificador == identificador){
        Lista_Listas* aux = l;
        l = aux->prox;
        liberar_lista(aux->lista);
        aux->lista = NULL;
        free(aux);

        return l;
    }
    l->prox = remover(l->prox, identificador);

    return l;
}

void imprimir(Lista_Listas* l)
{
    if(vazia(l))
        return;


    printf("id: %2d-> ", l->identificador);
    imprimir_lista(l->lista);

    imprimir(l->prox);
}

