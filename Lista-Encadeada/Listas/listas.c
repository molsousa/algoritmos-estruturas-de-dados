#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

// Estrutura para lista encadeada
struct lista{
    Tipo info;
    struct lista* prox;
};

// Funcao estatica para remover elemento
static Elem* remover(Elem* l, Tipo x);
// Funcao estatica para imprimir lista
static void imprimir(Elem* l);

// Funcao para criar lista encadeada
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna lista vazia
Lista* criar_lista()
{
    Lista* aux;

    aux = (Lista*) malloc(sizeof(Lista));
    *aux = NULL;

    return aux;
}

// Funcao para liberar lista
// Pre-condicao: lista criada
// Pos-condicao: libera lista e retorna nulo para ponteiro Lista
Lista* liberar_lista(Lista* l)
{
    Elem* aux = *l;

    while(aux != NULL){
        Elem* t = aux;
        aux = aux->prox;
        free(t);
    }

    return NULL;
}

// Funcao para verificar condicao da lista
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se vazia
int lista_vazia(Lista *l){
    return (*l == NULL);
}

// Funcao para inserir elemento na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void inserir_elemento(Lista* l, Tipo x)
{
    Elem* novo;

    novo = (Elem*) malloc(sizeof(Elem));

    novo->info = x;
    novo->prox = *l;

    *l = novo;
}

// Funcao para remover elemento da lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void remover_elemento(Lista* l, Tipo x)
{
    *l = remover(*l, x);
}

// Funcao estatica para remover elemento
static Elem* remover(Elem* l, Tipo x)
{
    Elem* aux = l;
    Elem* anterior = NULL;

    while(aux != NULL && aux->info != x){
        anterior = aux;
        aux = aux->prox;
    }

    if(aux == NULL)
        return l;

    else if(anterior == NULL)
        l = aux->prox;

    else
        anterior->prox = aux->prox;

    free(aux);

    return l;
}

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void imprimir_lista(Lista* l)
{
    if(l == NULL)
        return;

    imprimir(*l);
}

// Funcao estatica para imprimir lista
static void imprimir(Elem* l)
{
    if(l == NULL){
        printf("NULL\n");
        return;
    }

    printf("|%c|->", l->info);

    imprimir(l->prox);
}
