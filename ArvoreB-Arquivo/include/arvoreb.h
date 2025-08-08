#ifndef _ARVORE_B_H_INCLUDED
#define _ARVORE_B_H_INCLUDED

#include <stdio.h>
#define ORDEM 7

typedef enum{false = 0, true = 1}boolean;

typedef struct{
    int pos_livre;
    int pos_raiz;
    int pos_topo;
}cabecalho;

typedef struct{
    int num_chaves;
    int chaves[ORDEM];
    int filhos[ORDEM+1];
}noB;

void escrever_cabecalho(FILE*, cabecalho*);

cabecalho* ler_cabecalho(FILE*);

void escrever_no(FILE*, noB*, int);

noB* ler_no(FILE*, int);

void inicializar(FILE*);

boolean overflow(FILE*, int);

int split(FILE*, int, int*, cabecalho*);

int busca_pos(FILE*, int, int, int*);

void adicionar_direita(FILE*, int, int, int, int);

void inserir(FILE*, int);

int inserir_chave(FILE*, int, cabecalho*, int);

void inserir_aux(FILE*, int, cabecalho*, int);

void imprimir(FILE*);

void imprimir_aux(FILE*, int);

void imprimir_niveis(FILE*);

#endif // _ARVORE_B_H_INCLUDED
