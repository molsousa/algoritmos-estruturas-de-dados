#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED
#include <stdio.h>

// Definicao de tipo para cabecalho
typedef struct cabec Cabecalho;
// Definicao de tipo para lista
typedef struct lista Lista;

// Funcao para criar nova lista
// Pre-condicao: arquivo inicializado
// Pos-condicao: cria novo cabecalho no arquivo
void criar_lista(FILE* f);

// Funcao para escrever no cabecalho
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void escrever_cabecalho(FILE* f, Cabecalho* cab);

// Funcao para retornar o cabecalho
// Pre-condicao: lista criada
// Pos-condicao: retorna informacoes do cabecalho
Cabecalho* ler_cabecalho(FILE* f);

// Funcao para escrever No
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void escrever_no(FILE* f, Lista* l, int pos);

// Funcao para encontrar No
// Pre-condicao: lista criada
// Pos-condicao: retorna informacoes do no buscado
Lista* ler_no(FILE* f, int pos);

// Funcao para inserir elemento na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void inserir_elemento(FILE* f, int info);

// Funcao para remover elemento na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void remover_elemento(FILE* f, int info);

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime a lista em ordem de insercao
void imprimir_lista(FILE* f);

#endif // LISTA_ENCADEADA_H_INCLUDED
