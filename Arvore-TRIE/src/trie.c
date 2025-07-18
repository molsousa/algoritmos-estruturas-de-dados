#include <stdio.h>
#include <stdlib.h>
#include "../include/trie.h"

// Estrutura para arvore Trie
struct no{
    char letra;
    int valor;
    struct no* esq;
    struct no* meio;
    struct no* dir;
};

// Funcao para criar arvore Trie
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
Trie criar_arvore()
{
    return NULL;
}

// Funcao para verificar se um no eh nulo
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se nulo
int vazia(Trie h)
{
    return (h == NULL);
}

// Funcao para liberar arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro Trie
Trie liberar(Trie h)
{
    if(vazia(h))
        return h;

    liberar(h->esq);
    liberar(h->meio);
    liberar(h->dir);

    free(h);
    return NULL;
}

// Funcao para inserir palavra na arvore
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
Trie inserir(Trie h, char* palavra, int valor)
{
    if(vazia(h)){
        h = malloc(sizeof(struct no));
        h->letra = *palavra;
        h->esq = h->dir = h->meio = NULL;
        h->valor = -1;

        if(*(palavra+1) != '\0')
            h->meio = inserir(h->meio, palavra+1, valor);

        else
            h->valor = valor;
    }

    else{
        if(h->letra == *palavra)
            h->meio = inserir(h->meio, palavra+1, valor);

        else if(h->letra > *palavra)
            h->esq = inserir(h->esq, palavra, valor);

        else if(h->letra < *palavra)
            h->dir = inserir(h->dir, palavra, valor);
    }

    return h;
}

// Funcao para remover uma palavra
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
Trie remover(Trie h, char* palavra)
{
    if(vazia(h))
        return h;

    if(*palavra < h->letra)
        h->esq = remover(h->esq, palavra);

    else if(*palavra > h->letra)
        h->dir = remover(h->dir, palavra);

    else{
        if(*(palavra+1) == '\0'){
            if(h->valor != -1){
                h->valor = -1;
                free(h);
                return NULL;
            }
        }
        else
            h->meio = remover(h->meio, palavra+1);

        if(h->meio == NULL && h->valor == -1){
            free(h);
            return NULL;
        }
    }
    return h;
}

// Funcao auxiliar para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir_aux(Trie h, char* buffer, int n)
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
void imprimir(Trie h)
{
    char* buffer = calloc(TAM, sizeof(char));

    imprimir_aux(h, buffer, 0);

    free(buffer);
}

// Funcao para buscar palavra
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void busca(Trie h, char* palavra)
{
    if(vazia(h))
        return;

    if(h->letra == *palavra){
        printf("%c", h->letra);

        if(h->valor != -1)
            printf(" | %d\n", h->valor);

        busca(h->meio, palavra+1);
    }

    else if(h->letra > *palavra)
        busca(h->esq, palavra);

    else
        busca(h->dir, palavra);
}

// Funcao auxiliar para buscar nome inserindo valor
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void busca_dicionario_aux(Trie h, char* buffer, int valor, int n)
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
void busca_dicionario(Trie h, int valor)
{
    char* buffer = calloc(TAM, sizeof(char));

    busca_dicionario_aux(h, buffer, valor, 0);

    free(buffer);
}
