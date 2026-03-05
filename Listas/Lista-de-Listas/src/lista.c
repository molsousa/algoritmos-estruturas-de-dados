#include <stdio.h>
#include <stdlib.h>
#include "../include/lista.h"

struct no{
    int info;
    struct no* prox;
};

Lista criar_lista()
{
    return NULL;
}

int lista_vazia(Lista l)
{
    return (l == NULL);
}

void liberar_lista(Lista l)
{
    if(lista_vazia(l))
        return;

    liberar_lista(l->prox);
    free(l);
}

Lista inserir_no(Lista l, int info)
{
    Lista aux = malloc(sizeof(struct no));

    aux->info = info;
    aux->prox = l;

    return aux;
}

Lista copiar_lista(Lista l)
{
    if(lista_vazia(l))
        return NULL;

    Lista novo = criar_lista();

    novo = inserir_no(novo, l->info);

    novo->prox = copiar_lista(l->prox);

    return novo;

}

Lista remover_no(Lista l, int info)
{
    if(lista_vazia(l))
        return l;

    if(l->info == info){
        Lista aux = l;
        l = aux->prox;
        free(aux);

        return l;
    }

    l->prox = remover_no(l->prox, info);

    return l;
}

void imprimir_lista(Lista l)
{
    if(lista_vazia(l)){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", l->info);

    imprimir_lista(l->prox);
}
