#include <stdio.h>
#include <stdlib.h>
#include "../include/trie.h"

// Estrutura para arvore Trie
struct noTST{
    char letra;
    int valor;
    struct noTST* esq;
    struct noTST* meio;
    struct noTST* dir;
};

// Funcao para criar arvore Trie
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
TST_TRIE* criar_arvore()
{
    TST_TRIE* h = malloc(sizeof(TST_TRIE));

    *h = NULL;

    return h;
}

// Funcao para verificar se um no eh nulo
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se nulo
boolean vazia(TST_TRIE h)
{
    return (h == NULL);
}

// Funcao para liberar arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro Trie
static void liberar_aux(TST_TRIE h)
{
    if(vazia(h))
        return;

    liberar_aux(h->esq);
    liberar_aux(h->meio);
    liberar_aux(h->dir);

    free(h);
}

TST_TRIE* liberar(TST_TRIE* h)
{
    liberar_aux(*h);

    free(h);

    return NULL;
}

// Funcao para inserir palavra na arvore
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
static TST_TRIE inserir_aux(TST_TRIE h, char* palavra, int valor)
{
    if(vazia(h)){
        h = malloc(sizeof(struct noTST));
        h->letra = *palavra;
        h->esq = h->dir = h->meio = NULL;
        h->valor = -1;

        if(*(palavra+1) != '\0')
            h->meio = inserir_aux(h->meio, palavra+1, valor);

        else
            h->valor = valor;
    }

    else
        if(h->letra == *palavra)
            h->meio = inserir_aux(h->meio, palavra+1, valor);

        else if(h->letra > *palavra)
            h->esq = inserir_aux(h->esq, palavra, valor);

        else if(h->letra < *palavra)
            h->dir = inserir_aux(h->dir, palavra, valor);

    return h;
}

void inserir(TST_TRIE* h, char* palavra, int valor)
{
    *h = inserir_aux(*h, palavra, valor);
}

// Funcao para remover uma palavra
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
static TST_TRIE remover_aux(TST_TRIE h, char* palavra)
{
    if(vazia(h))
        return h;

    if(*palavra < h->letra)
        h->esq = remover_aux(h->esq, palavra);

    else if(*palavra > h->letra)
        h->dir = remover_aux(h->dir, palavra);

    else{
        if(*(palavra+1) == '\0'){
            if(h->valor != -1){
                h->valor = -1;
                free(h);
                return NULL;
            }
        }
        else
            h->meio = remover_aux(h->meio, palavra+1);

        if(h->meio == NULL && h->valor == -1){
            free(h);
            return NULL;
        }
    }
    return h;
}

void remover(TST_TRIE* h, char* palavra)
{
    *h = remover_aux(*h, palavra);
}

// Funcao auxiliar para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
static void imprimir_aux(TST_TRIE h, char* buffer, int n)
{
    if(vazia(h))
        return;

    imprimir_aux(h->esq, buffer, n);

    buffer[n] = h->letra;

    if(h->valor != -1){
        buffer[n+1] = '\0';
        printf("%s | %d\n", buffer, h->valor);
    }

    imprimir_aux(h->meio, buffer, n+1);
    imprimir_aux(h->dir, buffer, n);
}

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir(TST_TRIE* h)
{
    char* buffer = calloc(TAM, sizeof(char));

    imprimir_aux(*h, buffer, 0);

    free(buffer);
}

// Funcao auxiliar para buscar nome inserindo valor
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
static void busca_dicionario_aux(TST_TRIE h, char* buffer, int valor, int n)
{
    if(vazia(h))
        return;

    busca_dicionario_aux(h->esq, buffer, valor, n);
    buffer[n] = h->letra;

    if(h->valor != -1){
        buffer[n+1] = '\0';

        if(valor == h->valor)
            printf("%s | %d\n", buffer, h->valor);
    }

    busca_dicionario_aux(h->meio, buffer, valor, n+1);
    busca_dicionario_aux(h->dir, buffer, valor, n);
}

// Funcao para buscar nome inserindo valor
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void busca_dicionario(TST_TRIE* h, int valor)
{
    char* buffer = calloc(TAM, sizeof(char));

    busca_dicionario_aux(*h, buffer, valor, 0);

    free(buffer);
}

static void imprimir_dicionario_aux(TST_TRIE h)
{
    if(vazia(h))
        return;

    if(h->valor != -1)
        printf("%d\n", h->valor);

    imprimir_dicionario_aux(h->esq);
    imprimir_dicionario_aux(h->meio);
    imprimir_dicionario_aux(h->dir);
}

void imprimir_dicionario(TST_TRIE* h)
{
    imprimir_dicionario_aux(*h);
}
