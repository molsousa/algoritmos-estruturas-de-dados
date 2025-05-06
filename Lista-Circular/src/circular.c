#include <stdio.h>
#include <stdlib.h>
#include "circular.h"

struct lista{
    int info;
    struct lista* ant;
    struct lista* prox;
};

Lista* criar_lista()
{
    Lista* novo;
    novo = (Lista*) malloc(sizeof(Lista));

    *novo = NULL;

    return novo;
}

void* liberar_lista(Lista* l)
{
    if(l == NULL)
        return l;

    if(*l != NULL){
        Elem* aux = *l;
        Elem* anterior;

        do{
            anterior = aux;
            aux = aux->prox;
            free(anterior);

        }while(aux != *l);
    }

    free(l);

    return NULL;
}

void inserir_elemento(Lista* l, int info)
{
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    novo->info = info;

    if(*l == NULL){
        novo->ant = novo;
        novo->prox = novo;
        *l = novo;
    }
    else{
        if((*l)->prox == *l){
            novo->prox = *l;
            novo->ant = *l;
            (*l)->prox = novo;
            (*l)->ant = novo;
        }
        else{
            Elem* aux = (*l)->prox;

            while(aux->prox != *l)
                aux = aux->prox;

            aux->prox = novo;
            novo->ant = aux;
            novo->prox = *l;
            (*l)->ant = novo;
        }
    }
}

void remover_elemento(Lista* l, int info)
{
    Elem* aux = *l;

    do{
        aux = aux->prox;
    }while(aux != *l && aux->info != info);

    if(aux->info != info)
        return;

    else if(aux->prox == aux){
        free(aux);
        *l = NULL;
    }

    else{
        Elem* t = aux;
        t = t->ant;
        t->prox = aux->prox;
        aux->prox->ant = t;

        if(aux == *l)
            *l = t;

        free(aux);
    }
}

int buscar_elemento(Lista* l, int info)
{
    Elem* aux = *l;

    if(aux == NULL)
        return 0;

    do{
        aux = aux->prox;
    }while(aux != *l && aux->info != info);

    if(aux->info != info)
        return 0;

    return 1;
}

void imprimir_lista(Lista* l)
{
    Elem* aux = *l;

    if(aux == NULL){
        printf("NULL\n");
        return;
    }

    do{
        printf("|%d|->", aux->info);
        aux = aux->prox;
    }while(aux != *l);

    printf("\n");

    do{
        aux = aux->ant;
        printf("<-|%d|", aux->info);
    }while(aux != *l);

    printf("\n");
}
