#ifndef _ARVORE_RUBRO_NEGRA_H_INCLUDED
#define _ARVORE_RUBRO_NEGRA_H_INCLUDED
#include <stdio.h>

typedef struct{
    int pos_raiz;
    int pos_livre;
    int pos_topo;
}cabecalho;

typedef struct{
    int chave;
    enum{VERMELHO, PRETO} cor;
    int esq;
    int dir;
}no;

void criar_arvore(FILE* f);

cabecalho* ler_cabecalho(FILE* f);

void escrever_cabecalho(FILE* f, cabecalho* cab);

no* ler_no(FILE* f, int pos);

void escrever_no(FILE* f, no* x, int pos);

int cor(FILE* f, int pos);

int rotacionar_esquerda(FILE* f, int pos);

int rotacionar_direita(FILE* f, int pos);

void troca_cor(FILE* f, int pos);

int inserir_aux(FILE* f, cabecalho* cab, int chave, int pos);

void inserir(FILE* f, int chave);

void imprimir_aux(FILE* f, int pos);

void imprimir(FILE* f);

void imprimir_niveis(FILE* f);

#endif
