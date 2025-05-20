#include <stdio.h>
#include <stdlib.h>
#include "listade.h"

// Estrutura para lista duplamente encadeada
struct lista{
    int info;
    struct lista* ant;
    struct lista* prox;
};

// Funcao auxiliar para liberar cada elemento
static void liberar_lista_cauda(Elem* l);
// Funcao auxiliar para imprimir a ida
static void rotina_ida(Elem *l);
// Funcao auxiliar para imprimir a volta
static void rotina_volta(Elem* l);

// Funcao para criar lista
// Pre-condicao: nenhum
// Pos-condicao: retorna uma lista criada
Lista* criar_lista()
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    *novo = NULL;

    return novo;
}

// Funcao para liberar lista
// Pre-condicao: lista criada
// Pos-condicao: retorna nulo para ponteiro do tipo Lista
Lista* liberar_lista(Lista* l)
{
    if(l == NULL)
        return l;

    liberar_lista_cauda(*l);
    free(l);

    return NULL;
}

// Funcao auxiliar para liberar cada elemento
static void liberar_lista_cauda(Elem* l)
{
    if(l == NULL)
        return;

    liberar_lista_cauda(l->prox);

    free(l);
}

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento em cauda
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

// Funcao para inserir elemento ordenado
// Pre-condicao: lista criada
// Pos-condicao: insere elemento de forma ordenada
void inserir_elemento_ordenado(Lista* l, int info)
{
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    novo->info = info;
    novo->prox = NULL;
    novo->ant = NULL;

    if(*l == NULL)
        *l = novo;

    else{
        Elem* aux = *l;

        while(aux->prox != NULL && aux->info <= info)
            aux = aux->prox;

        if(aux == *l && aux->info > info){
            aux->ant = novo;
            novo->prox = aux;
            *l = novo;
        }
        else if(aux == *l && aux->info < info){
            aux->prox = novo;
            novo->ant = aux;
        }
        else{
            Elem* p = aux->ant;

            if(aux->prox == NULL && aux->info <= info){
                aux->prox = novo;
                novo->ant = aux;
            }
            else{
                novo->prox = p->prox;
                novo->ant = p;
                p->prox = novo;
                aux->ant = novo;
            }
        }
    }
}

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove elemeento da lista
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

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime a lista na tela
void imprimir_lista(Lista* l)
{
    if(*l == NULL){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", (*l)->info);

    imprimir_lista(&(*l)->prox);
}

// Funcao para imprimir a lista ida e volta
// Pre-condicao: lista criada
// Pos-condicao: imprime a lista na tela
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

// Funcao auxiliar para imprimir a ida
static void rotina_ida(Elem *l)
{
    if(l == NULL){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", l->info);

    rotina_ida(l->prox);
}

// Funcao auxiliar para imprimir a volta
static void rotina_volta(Elem *l)
{
    if(l == NULL){
        printf("NULL");
        return;
    }

    printf("|%d|->", l->info);

    rotina_volta(l->ant);
}
