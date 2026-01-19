#ifndef ARVORE_BINARIA_H_INCLUDED
#define ARVORE_BINARIA_H_INCLUDED
#include <stdio.h>

// Definicao de tipo para cabecalho
typedef struct cabecalho Cabecalho;
// Definicao de tipo para no
typedef struct no_arv No;

// Funcao para escrever no cabecalho
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: escreve no cabecalho
void escrever_cabecalho(FILE* f, Cabecalho* cab);

// Funcao para ler cabecalho
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o cabecalho do arquivo
Cabecalho* ler_cabecalho(FILE* f);

// Funcao para escrever no
// Pre-condicao: arquivo inicializado
// Pos-condicao: escreve no arquivo o no
void escrever_no(FILE* f, No* no, int pos);

// Funcao para ler no
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna ponteiro para no
No* ler_no(FILE* f, int pos);

// Funcao para criar uma arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: retorna o cabecalho inicializado
void criar_arvore(FILE* f);

// Funcao para inserir na arvore
// Pre-condicao: arquivo inicializado
// Pos-condicao: nenhuma
void inserir_no(FILE* f, int info);

// Funcao para remover elemento da arvore
// Pre-condicao: cabecalho inicializado
// Pos-condicao: nenhuma
void remover_no(FILE* f, int info);

// Funcao auxiliar para remover elemento
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna o registro se removido ou -1 se nao encontrado
int remover(FILE* f, int pos, int info, Cabecalho* cab);

// Funcao para encontrar o maximo
// Pre-condicao: nenhuma
// Pos-condicao: retorna a posicao do maior valor da subarvore da esquerda
int maximo(FILE* f, int pos);

// Funcao auxiliar para imprimir em preOrder
// Pre-condicao: arquivo inicializado
// Pos-condicao: imprime na tela a arvore pre ordenada
void imprimir_preOrder(FILE* f, int pos);

// Funcao para imprimir em preOrder
// Pre-condicao: arquivo inicializado
// Pos-condicao: nenhuma
void imprimir_arvore(FILE* f);

#endif // ARVORE_BINARIA_H_INCLUDED
