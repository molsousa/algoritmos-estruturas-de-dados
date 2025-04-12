#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Estrutura para lista
struct lista{
    Tipo info;
    struct lista* prox;
};

// Estrutura para fila
struct fila{
    struct lista* primeiro;
    struct lista* ultimo;
};

// Funcao para imprimir fila
static void imprimir(Elem* f);

// Funcao para criar fila
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna fila vazia
Fila* criar_fila()
{
    Fila* novo = (Fila*) malloc(sizeof(Fila));

    novo->primeiro = NULL;
    novo->ultimo = NULL;

    return novo;
}

// Funcao para liberar fila
// Pre-condicao: fila criada
// Pos-condicao: retorna nulo para ponteiro Fila
Fila* liberar_fila(Fila* f)
{
    if(f == NULL)
        return f;

    while(f->primeiro != NULL){
        Elem* aux = f->primeiro;
        f->primeiro = f->primeiro->prox;
        free(aux);
    }
	
	free(f);

    return NULL;
}

// Funcao para verificar condicao da fila
// Pre-condicao: fila criada
// Pos-condicao: retorna 1 se vazia
int fila_vazia(Fila* f)
{
    return (f->primeiro == NULL);
}

// Funcao para inserir elemento na fila
// Pre-condicao: fila criada
// Pos-condicao: nenhuma
void enfileirar(Fila* f, Tipo x)
{
    Elem* novo = (Elem*) malloc(sizeof(Elem));

    novo->info = x;
    novo->prox = NULL;

    if(fila_vazia(f))
        f->primeiro = novo;
    else
        f->ultimo->prox = novo;

    f->ultimo = novo;
}

// Funcao para passar elemento da fila
// Pre-condicao: fila criada
// Pos-condicao: nenhuma
void desenfileirar(Fila* f)
{
    if(!fila_vazia(f)){
        Elem* aux = f->primeiro;

        if(f->primeiro == f->ultimo)
            f->primeiro = NULL;

        f->primeiro = f->primeiro->prox;
        free(aux);
    }
}

// Funcao para imprimir fila
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_fila(Fila* f)
{
    if(f == NULL)
        return;

    imprimir(f->primeiro);
}

// Funcao para imprimir fila
static void imprimir(Elem* f)
{
    if(f == NULL){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", f->info);

    imprimir(f->prox);
}
