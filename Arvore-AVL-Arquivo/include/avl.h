#ifndef ARVORE_AVL_H_INCLUDED
#define ARVORE_AVL_H_INCLUDED

#include <stdio.h>

#define maior(x, y) x > y ? x : y

typedef enum{false = 0, true = 1}bool;

typedef struct{
    int pos_raiz;
    int pos_livre;
    int pos_topo;
}cabecalho;

typedef struct{
    int chave;
    int fb;
    int esq;
    int dir;
}no;

cabecalho* ler_cabecalho(FILE*);

void escrever_cabecalho(FILE*, cabecalho*);

no* ler_no(FILE*, int);

void escrever_no(FILE*, no*, int);

void inicializar(FILE*);

int altura(FILE*, int);

int fator_balanceamento(FILE*, no*);

int procurar_menor(FILE*, int);

int rotacaoLL(FILE*, int);

int rotacaoRR(FILE*, int);

int rotacaoLR(FILE*, int);

int rotacaoRL(FILE*, int);

void inserir(FILE*, int);

int inserir_aux(FILE*, int, cabecalho*, int);

void imprimir(FILE*);

void imprimir_aux(FILE*, int);

void imprimir_niveis(FILE*);

#endif // ARVORE_AVL_H_INCLUDED
