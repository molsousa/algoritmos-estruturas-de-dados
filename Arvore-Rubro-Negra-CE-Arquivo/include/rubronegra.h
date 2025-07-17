#ifndef _ARVORE_RUBRO_NEGRA_H_INCLUDED
#define _ARVORE_RUBRO_NEGRA_H_INCLUDED
#include <stdio.h>

typedef struct{
    int pos_raiz;
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

int busca_aux(FILE* f, int chave, int pos);

int busca(FILE* f, int chave);

int mover_para_esquerda(FILE* f, int pos);

int mover_para_direita(FILE* f, int pos);

int balancear(FILE* f, int pos);

int remover_aux(FILE* f, cabecalho* cab, int chave, int pos);

void remover(FILE* f, int chave);

void imprimir_aux(FILE* f, int pos);

void imprimir(FILE* f);

void imprimir_niveis(FILE* f);

int contar_nos(FILE* f);

int contar_nos_aux(FILE* f, int pos);

#endif
