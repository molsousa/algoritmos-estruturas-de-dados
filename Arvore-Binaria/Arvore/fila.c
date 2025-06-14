#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Estrutura para lista encadeada
struct lista{
    Tipo info;
    struct lista* prox;
};

// Estrutura para fila
struct fila{
    struct lista* inicio;
    struct lista* fim;
};

// Funcao para criar fila
// Pre-condicao: nenhuma
// Pos-condicao: cria nova fila vazia
Fila* criar_fila()
{
    Fila* novo = malloc(sizeof(Fila));

    novo->inicio = novo->fim = NULL;

    return novo;
}

// Funcao para liberar fila criada
// Pre-condicao: fila criada
// Pos-condicao: nenhuma
void liberar_fila(Fila* f)
{
    while(!fila_vazia(f))
        dequeue(f);

    free(f);
}

// Funcao para testar se uma fila eh vazia
// Pre-condicao: fila criada
// Pos-condicao: retorna 1 se vazia
int fila_vazia(Fila* f)
{
    return (f->inicio == NULL);
}

// Funcao para enfilerar item
// Pre-condicao: fila criada
// Pos-condicao: enfilera item na lista
void enqueue(Fila* f, Tipo x)
{
    struct lista* novo = malloc(sizeof(struct lista));
    novo->info = x;
    novo->prox = NULL;

    if(fila_vazia(f))
        f->inicio = novo;
    else
        f->fim->prox = novo;

    f->fim = novo;
}

// Funcao para defilerar item
// Pre-condicao: fila criada
// Pos-condicao: retorna o valor defilerado
Tipo dequeue(Fila* f)
{
    Tipo valor;
    valor = f->inicio->info;

    struct lista* aux = f->inicio;

    f->inicio = f->inicio->prox;
    if(f->inicio == NULL)
        f->fim = NULL;

    free(aux);

    return valor;
}
