#ifndef _ARVORE_TERNARIA_DE_BUSCA_TRIE_H_INCLUDED
#define _ARVORE_TERNARIA_DE_BUSCA_TRIE_H_INCLUDED
#define TAM 100

// Definicao de tipo para arvore trie
typedef struct noTST* TST_TRIE;
// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;

// Funcao para criar arvore Trie
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
TST_TRIE* criar_arvore();

// Funcao para verificar se um no eh nulo
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se nulo
boolean vazia(TST_TRIE h);

// Funcao para liberar arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro Trie
TST_TRIE* liberar(TST_TRIE* h);

// Funcao para inserir palavra na arvore
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void inserir(TST_TRIE* h, char* palavra, int valor);

// Funcao  para remover uma palavra
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void remover(TST_TRIE* h, char* palavra);

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir(TST_TRIE* h);

// Funcao para buscar palavra
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void busca(TST_TRIE* h, char* palavra);

// Funcao para buscar nome inserindo valor
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void busca_dicionario(TST_TRIE* h, int valor);

void imprimir_dicionario(TST_TRIE* h);

#endif
