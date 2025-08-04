#include <stdio.h>
#include <stdlib.h>
#include "../include/rway.h"
#include "../include/fila.h"

struct noTrie{
    struct noTrie* filho[TAM_ALFABETO];
    int valor;
};

struct trie{
    Trie raiz;
};

int vazia(Trie r)
{
    return (r == NULL);
}

arvTrie* criar_arvore()
{
    arvTrie* r = malloc(sizeof(arvTrie));
    int i;

    r->raiz = malloc(sizeof(struct noTrie));

    for(i = 0; i < TAM_ALFABETO; i++)
        r->raiz->filho[i] = NULL;

    return r;
}

void inserir(arvTrie* r, char* str, int valor)
{
    r->raiz = inserir_aux(r->raiz, str, valor);
}

Trie inserir_aux(Trie raiz, char* str, int valor)
{
    if(vazia(raiz)){
        int i;
        raiz = malloc(sizeof(struct noTrie));
        raiz->valor = -1;

        for(i = 0; i < TAM_ALFABETO; i++)
            raiz->filho[i] = NULL;
    }
    if(*str == '\0'){
        raiz->valor = valor;
        return raiz;
    }

    raiz->filho[*str - ASCII_BASE] = inserir_aux(raiz->filho[*str - ASCII_BASE], str+1, valor);

    return raiz;
}

void imprimir(arvTrie* r)
{
    Fila fila = criar_fila();

    imprimir_aux(r->raiz, fila);

    free(fila);
}

void imprimir_aux(Trie raiz, Fila fila)
{
    int i;
    for(i = 0; i < TAM_ALFABETO; i++){
        if(raiz->filho[i] != NULL){
            enqueue(fila, ASCII_BASE+i);
            imprimir_aux(raiz->filho[i], fila);
        }
    }

    while(!fila_vazia(fila)){
        printf("%c", consultar_topo(fila));

        dequeue(fila);
    }

    printf("\n");
}
