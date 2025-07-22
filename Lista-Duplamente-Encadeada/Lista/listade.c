#include <stdio.h>
#include <stdlib.h>
#include "listade.h"

// Estrutura para lista duplamente encadeada
struct lista{
    int info;
    struct lista* ant;
    struct lista* prox;
};

// Funcao para criar lista
// Pre-condicao: nenhum
// Pos-condicao: retorna uma lista criada
Lista* criar_lista()
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    *novo = NULL;

    return novo;
}

// Testa se um no eh vazio
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se vazio
int vazia(struct lista* l)
{
    return (l == NULL);
}

// Funcao auxiliar para liberar cada elemento
// Pre-condicao: nenhuma
// Pos-condicao: destroi elementos da lista
void liberar_lista_cauda(struct lista* l)
{
    if(vazia(l))
        return;

    liberar_lista_cauda(l->prox);

    free(l);
}

// Funcao para liberar lista
// Pre-condicao: lista criada
// Pos-condicao: retorna nulo para ponteiro do tipo Lista
Lista* liberar_lista(Lista* l)
{
    if(vazia(*l))
        return l;

    liberar_lista_cauda(*l);
    free(l);

    return NULL;
}

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento em cauda
void inserir_elemento(Lista* l, int info)
{
    struct lista* novo = malloc(sizeof(struct lista));
    novo->info = info;
    novo->ant = NULL;
    novo->prox = NULL;

    if(vazia(*l))
        *l = novo;

    else{
        struct lista* aux = *l;
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
    struct lista* novo = malloc(sizeof(struct lista));
    novo->info = info;
    novo->prox = NULL;
    novo->ant = NULL;

    if(vazia(*l))
        *l = novo;

    else{
        struct lista* aux = *l;

        while(!vazia(aux->prox) && aux->info <= info)
            aux = aux->prox;

        if(aux == *l && aux->info > info){
            aux->ant = novo;
            novo->prox = aux;
            *l = novo;
        }
        else{
            struct lista* p = aux->ant;

            if(aux->info <= info){
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
    if(vazia(*l))
        return;

    struct lista* aux = *l;

    while(!vazia(aux) && aux->info != info)
        aux = aux->prox;

    if(vazia(aux))
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
    if(vazia(*l)){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", (*l)->info);

    imprimir_lista(&(*l)->prox);
}

// Funcao para imprimir a lista ida e volta
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void imprimir_ida_volta(Lista* l)
{
    printf("IDA:   ");
    rotina_ida(*l);
    struct lista* aux = *l;

    while(!vazia(aux->prox))
        aux = aux->prox;

    printf("VOLTA: ");
    rotina_volta(aux);
    printf("\n");
}

// Funcao auxiliar para imprimir a ida
// Pre-condicao: lista criada
// Pos-condicao: imprime a rotina de ida
void rotina_ida(struct lista* l)
{
    if(vazia(l)){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", l->info);

    rotina_ida(l->prox);
}

// Funcao auxiliar para imprimir a volta
// Pre-condicao: lista criada
// Pos-condicao: imprime a rotina de volta
void rotina_volta(struct lista* l)
{
    if(vazia(l)){
        printf("NULL");
        return;
    }

    printf("|%d|->", l->info);

    rotina_volta(l->ant);
}
