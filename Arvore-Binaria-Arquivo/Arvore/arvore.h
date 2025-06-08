#ifndef ARVORE_BINARIA_H_INCLUDED
#define ARVORE_BINARIA_H_INCLUDED
#include <stdio.h>

// Definicao de tipo para no
typedef struct no No;
// Definicao de tipo para cabecalho
typedef struct cabecalho Cabecalho;

// Funcao para criar uma arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: retorna um arquivo binario inicializado
FILE* criar_arvore();

// Funcao para ler cabecalho
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o cabecalho do arquivo
Cabecalho* ler_cabecalho(FILE* f);

// Funcao para escrever no cabecalho
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: escreve no cabecalho
void escrever_cabecalho(FILE* f, Cabecalho c);

// Funcao para ler no
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna arquivo lido em arquivo binario
No ler_no(FILE* f, int dado);

// Funcao para escrever no
// Pre-condicao: arquivo inicializado
// Pos-condicao: escreve no arquivo o no
void escrever_no(FILE* f, No no, int dado);

// Funcao auxiliar para inserir na arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna sucesso em inserir
int inserir(FILE* f, Cabecalho* c, int atual, int info);

// Funcao para inserir elemento da arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: nenhuma
void inserir_no(FILE* f, Cabecalho* c, int info);

// Funcao auxiliar para remover elemento
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna o registro se removido ou -1 se nao encontrado
int remover(FILE* f, Cabecalho* c, int atual, int info);

// Funcao para remover elemento da arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: nenhuma
void remover_no(FILE* f, Cabecalho* c, int info);

// Funcao para alocar espaco em arquivo binario
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna novo espaco inicializado
int alocar_espaco(FILE* f, Cabecalho* c);

// Funcao para escrever em novo espaco
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: libera novo espaco em arquivo
void espaco_livre_no(FILE* f, Cabecalho* c, int dado);

// Funcao para buscar o maior valor da subarvore esquerda
// Pre-condicao: enviado o valor da esquerda
// Pos-condicao: retorna a posicao do maior valor da subarvore esquerda
int procurar_no_maior(FILE* f, int atual);

// Funcao auxiliar para imprimir em preOrder
// Pre-condicao: arquivo inicializado
// Pos-condicao: imprime na tela a arvore pre ordenada
void imprimir_preOrder(FILE* f, int atual);

// Funcao para imprimir arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: nenhuma
void imprimir_arvore(FILE* f, Cabecalho* c);

// Funcao auxiliar para buscar informacao
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o valor do registro da informacao
int buscar_no(FILE* f, int atual, int info);

// Funcao para buscar informacao
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna o valor do registro da informacao
int buscar_arvore(FILE* f, Cabecalho* c, int info);

#endif // ARVORE_BINARIA_H_INCLUDED
