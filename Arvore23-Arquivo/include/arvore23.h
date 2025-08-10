#ifndef ARVORE_23_H_INCLUDED
#define ARVORE_23_H_INCLUDED

#include <stdio.h>

typedef enum{false = 0, true = 1}boolean;

typedef struct{
    int pos_raiz;
    int pos_topo;
    int pos_livre;
}cabecalho;

typedef struct{
    int chave_esq;
    int chave_dir;
    int esq;
    int meio;
    int dir;
    int num_chaves;
}no23;

cabecalho* ler_cabecalho(FILE*);

void escrever_cabecalho(FILE*, cabecalho*);

no23* ler_no(FILE*, int);

void escrever_no(FILE*, no23*, int);

void inicializar(FILE*);

boolean vazia(int);

boolean eh_folha(FILE*, int);

int busca(FILE*, int, int);

int inserir_aux(FILE*, int, int, int*, cabecalho*);

int split(FILE*, int, int, int, int*, cabecalho*);

void adiciona_chave(FILE*, int, int, int);

int cria_no(FILE*, cabecalho*, int, int, int, int, int, int);

int inserir_chave(FILE*, int, cabecalho*, int);

void inserir(FILE*, int);

void imprimir_niveis(FILE*);

#endif // ARVORE_23_H_INCLUDED
