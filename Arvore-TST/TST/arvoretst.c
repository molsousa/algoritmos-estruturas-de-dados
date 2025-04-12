#include <stdio.h>
#include <stdlib.h>
#define TAM 50
#include "arvoretst.h"

// Estrutura para arvore TST
struct no_tst{
    char info;
    int valor;
    struct no_tst *esq;
    struct no_tst *meio;
    struct no_tst *dir;
};

// Funcao para inserir elemento na arvore
static Arv* inserir(Arv* arvore, char* palavra, int valor);
// Funcao para imprimir arvore Tst
static void imprimir(Arv* arvore, char* palavra, int n);
// Funcao para buscar nome inserindo nome
static void busca(Arv* arvore, char* palavra);
// Funcao para buscar nome inserindo valor
static void buscar(Arv* arvore, int valor, char* palavra, int n);
// Funcao para liberar arvore Tst
static void liberar(Arv* arvore);

// Funcao para criacao de arvore Tst
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna um ponteiro do tipo Tst
Tst *criar_arvore()
{
    Tst *novo = (Tst*) malloc(sizeof(Tst));

    *novo = NULL;

    return novo;
}

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada, vetor de char nao nulo
// Pos-condicao: nenhuma
void inserir_nome(Tst* arvore, char* word, int valor)
{
    *arvore = inserir(*arvore, word, valor);
}

// Funcao para inserir elemento na arvore
static Arv* inserir(Arv* arvore, char* palavra, int valor)
{
    if(arvore == NULL){
        Arv* novo = (Arv*) malloc(sizeof(Arv));
        novo->info = *palavra;
        novo->esq = NULL;
        novo->meio = NULL;
        novo->dir = NULL;
        novo->valor = -1;
        arvore = novo;

        if(*(palavra+1) != 0)
            arvore->meio = inserir(arvore->meio, palavra+1, valor);

        else
            arvore->valor = valor;
    }

    else{
        if(arvore->info == *palavra)
            arvore->meio = inserir(arvore->meio, palavra+1, valor);

        else if(arvore->info > *palavra)
            arvore->esq = inserir(arvore->esq, palavra, valor);

        else if(arvore->info < *palavra)
            arvore->dir = inserir(arvore->dir, palavra, valor);
    }

    return arvore;
}

// Funcao para imprimir arvore Tst
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir_arvore(Tst* arvore)
{
    char* palavra = (char*) malloc(TAM * sizeof(char));

    imprimir(*arvore, palavra, 0);
}

// Funcao para imprimir arvore Tst
static void imprimir(Arv* arvore, char* palavra, int n)
{
    if(!arvore)
        return;

    imprimir(arvore->esq, palavra, n);

    palavra[n] = arvore->info;

    if(arvore->valor != -1){
        palavra[n+1] = '\0';
        printf("%s | %d\n", palavra, arvore->valor);
    }

    imprimir(arvore->meio, palavra, n+1);
    imprimir(arvore->dir, palavra, n);
}

// Funcao para buscar nome inserindo nome
// Pre-condicao: arvore criada e vetor de char nao nulo
// Pos-condicao: nenhuma
void busca_arvore(Tst* arvore, char* palavra)
{
    busca(*arvore, palavra);
}

// Funcao para buscar nome inserindo nome
static void busca(Arv* arvore, char* palavra)
{
    if(!arvore)
        return;

    if(arvore->info == *palavra){
        printf("%c", arvore->info);

        if(arvore->valor != -1)
            printf(" | %d\n", arvore->valor);

        busca(arvore->meio, palavra+1);
    }

    else if(arvore->info > *palavra)
        busca(arvore->esq, palavra);

    else if(arvore->info < *palavra)
        busca(arvore->dir, palavra);
}

// Funcao para buscar nome inserindo valor
// Pre-condicao: arvore criada e valor valido
// Pos-condicao: nenhuma
void busca_dicionario(Tst* arvore, int valor)
{
    char* palavra = (char*) malloc(TAM * sizeof(char));

    buscar(*arvore, valor, palavra, 0);
}

// Funcao para buscar nome inserindo valor
static void buscar(Arv* arvore, int valor, char* palavra, int n)
{
    if(!arvore){
        return;
    }

    buscar(arvore->esq, valor, palavra, n);

    palavra[n] = arvore->info;

    if(arvore->valor != -1){
        palavra[n+1] = '\0';

        if(valor == arvore->valor)
            printf("%s | %d\n", palavra, arvore->valor);
    }

    buscar(arvore->meio, valor, palavra, n+1);
    buscar(arvore->dir, valor, palavra, n);
}

// Funcao para liberar arvore Tst
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
Tst* liberar_arvore(Tst* arvore)
{
    liberar(*arvore);

    free(arvore);

    return NULL;
}

// Funcao para liberar arvore Tst
static void liberar(Arv* arvore)
{
    if(!arvore)
        return;

    liberar(arvore->esq);
    liberar(arvore->meio);
    liberar(arvore->dir);

    free(arvore);
}
