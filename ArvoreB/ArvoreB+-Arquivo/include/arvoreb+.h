#ifndef ARVORE_B_MAIS_ARQUIVO_H_INCLUDED
#define ARVORE_B_MAIS_ARQUIVO_H_INCLUDED

#include <stdio.h>

#define ORDEM 5
#define MIN_CHAVES ((ORDEM  -1)/2)

typedef enum{false = 0, true = 1}boolean;

enum{
    aberto, fechado, folha, interno, nosTotais
};

typedef struct{
    int pos_raiz;
    int pos_topo;
    int pos_livre;
}cabecalho;

typedef struct{
    int chave[ORDEM];
    int ponteiro[ORDEM+1];
    short num_chaves;
    boolean eh_folha;
    int pai;
}paginaBMais;

void escrever_cabecalho(FILE*, cabecalho*);

cabecalho* ler_cabecalho(FILE*);

void escrever_pagina(FILE*, paginaBMais*, int);

paginaBMais* ler_pagina(FILE*, int);

void inicializar(FILE*);

boolean vazia(int);

boolean overflow(FILE*, int);

int obter_pos_livre(FILE*, cabecalho*);

int split(FILE*, cabecalho*, int, int*);

boolean busca_pos(FILE*, int, int, int*);

void adicionar_direita(FILE*, int, int, int, int);

void inserir_aux(FILE*, int, cabecalho*, int);

int criaPagina(FILE*, int*, cabecalho*, boolean, int);

void corrigir_pai(FILE*, int);

int inserir(FILE*, int, cabecalho*, int);

void insere(FILE*, int);

void imprimir_niveis(FILE*);

void err();

#endif // ARVORE_B_MAIS_ARQUIVO_H_INCLUDED
