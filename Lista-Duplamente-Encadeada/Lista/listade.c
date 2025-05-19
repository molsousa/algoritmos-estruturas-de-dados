#include <stdio.h>
#include <stdlib.h>
#include "listade.h"

struct lista{
    int info;
    struct lista* ant;
    struct lista* prox;
};

static void liberar_lista_cauda(Elem* l);
static void rotina_ida(Elem *l);
static void rotina_volta(Elem* l);

Lista* criar_lista()
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    *novo = NULL;

    return novo;
}

Lista* liberar_lista(Lista* l)
{
    if(l == NULL)
        return l;

    liberar_lista_cauda(*l);
    free(l);

    return NULL;
}
static void liberar_lista_cauda(Elem* l)
{
    if(l == NULL)
        return;

    liberar_lista_cauda(l->prox);

    free(l);
}

void inserir_elemento(Lista* l, int info)
{
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    novo->info = info;
    novo->ant = NULL;
    novo->prox = NULL;

    if(*l == NULL)
        *l = novo;

    else{
        Elem* aux = *l;
        while(aux->prox != NULL)
            aux = aux->prox;

        novo->ant = aux;
        aux->prox = novo;
    }
}

void remover_elemento(Lista* l, int info)
{
    if(*l == NULL)
        return;

    Elem* aux = *l;

    while(aux != NULL && aux->info != info)
        aux = aux->prox;

    if(aux == NULL)
        return;

    if(aux == *l){
        *l = aux->prox;
        free(aux);

        if(*l != NULL)
            (*l)->ant = NULL;

        return;
    }
    else{
        aux->ant->prox = aux->prox;

        if(aux->prox != NULL)
            aux->prox->ant = aux->ant;
    }

    free(aux);
}

void imprimir_lista(Lista* l)
{
    if(*l == NULL){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", (*l)->info);

    imprimir_lista(&(*l)->prox);
}

void imprimir_ida_volta(Lista* l)
{
    printf("IDA:   ");
    rotina_ida(*l);
    Elem* aux = *l;

    while(aux->prox != NULL)
        aux = aux->prox;

    printf("VOLTA: ");
    rotina_volta(aux);
    printf("\n");
}

static void rotina_ida(Elem *l)
{
    if(l == NULL){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", l->info);

    rotina_ida(l->prox);
}

static void rotina_volta(Elem *l)
{
    if(l == NULL){
        printf("NULL");
        return;
    }

    printf("|%d|->", l->info);

    rotina_volta(l->ant);
}
