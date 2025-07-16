#ifndef _FILA_H_INCLUDED
#define _FILA_H_INCLUDED
#include <stdio.h>

// Estrutura para lista encadeada
typedef struct{
    int info;
    int prox;
}no;

// Estrutura para cabecalho
typedef struct{
    int pos_cabeca;
    int pos_ultimo;
    int pos_topo;
    int pos_livre;
}cabecalho;

// Funcao para criar fila
// Pre-condicao: arquivo aberto
// Pos-condicao: cria cabecalho no arquivo binario
void criar_fila(FILE* f);

// Funcao para ler cabecalho
// Pre-condicao: nenhuma
// Pos-condicao: retorna atual condicao do cabecalho
cabecalho* ler_cabecalho(FILE* f);

// Funcao para escrever cabecalho
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void escrever_cabecalho(FILE* f, cabecalho* cab);

// Funcao para ler no
// Pre-condicao: nenhuma
// Pos-condicao: retorna no na posicao escolhida
no* ler_no(FILE* f, int pos);

// Funcao para escrever no
// Pre-condicao: nenhuma
// Pos-condicao: escreve no em determinada posicao
void escrever_no(FILE* f, no* x, int pos);

// Funcao para enfilerar valor
// Pre-condicao: cabecalho inicializado
// Pos-condicao: insere elemento ao final da fila
void enfilerar(FILE* f, int info);

// Funcao para defilerar valor
// Pre-condicao: cabecalho inicializado
// Pos-condicao: remove elemento da cabeca
void defilerar(FILE* f);

// Funcao para imprimir elementos em fila
// Pre-condicao: nenhuma
// Pos-condicao: imprime elementos na tela
void imprimir_fila(FILE* f);

// Funcao para imprimir posicoes livres
// Pre-condicao: nenhuma
// Pos-condicao: imprime posicoes livres
void imprimir_pos_livre(FILE* f);

#endif // _FILA_H_INCLUDED
