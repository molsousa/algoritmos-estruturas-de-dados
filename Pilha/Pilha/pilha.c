#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Estrutura para lista encadeada
struct lista{
    Tipo info;
    struct lista* prox;
};

// Estrutura para pilha
struct pilha{
    struct lista* topo;
};

// Funcao para imprimir pilha
static void imprimir(Elem* p);

// Funcao para criar pilha dinamica
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna pilha vazia
Pilha* criar_pilha()
{
    Pilha* novo;

    novo = (Pilha*) malloc(sizeof(Pilha));
    novo->topo = NULL;

    return novo;
}

// Funcao para liberar pilha
// Pre-condicao: pilha criada
// Pos-condicao: retorna nulo para ponteiro Pilha
Pilha* liberar_pilha(Pilha* p)
{
    if(p == NULL)
        return p;

    while(p->topo != NULL){
        Elem* aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }

    return NULL;
}

// Verifica condicao da pilha
// Pre-condicao: pilha criada
// Pos-condicao: retorna 1 se pilha vazia
int pilha_vazia(Pilha* p)
{
    return (p->topo == NULL);
}

// Funcao para empilhar elemento
// Pre-condicao: pilha criada
// Pos-condicao: nenhuma
void empilhar(Pilha* p, Tipo x)
{
    Elem* novo = (Elem*) malloc(sizeof(Elem));

    novo->info = x;
    novo->prox = p->topo;

    p->topo = novo;
}

// Funcao para desempilhar elemento
// Pre-condicao: pilha criada
// Pos-condicao: nenhuma
void desempilhar(Pilha* p)
{
    if(!pilha_vazia(p)){
        Elem* aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
    else
        printf("Pilha vazia\n");
}

// Funcao para imprimir pilha
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_pilha(Pilha* p)
{
    if(p == NULL)
        return;

    imprimir(p->topo);
}

// Funcao para imprimir pilha
static void imprimir(Elem* p)
{
    if(p == NULL){
        printf("NULL\n");
        return;
    }

    printf("%d\n", p->info);

    imprimir(p->prox);
}
