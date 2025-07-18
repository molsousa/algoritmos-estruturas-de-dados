#ifndef _ARVORE_TERNARIA_DE_BUSCA_TRIE_H_INCLUDED
#define _ARVORE_TERNARIA_DE_BUSCA_TRIE_H_INCLUDED
#define TAM 100

// Definicao de tipo para arvore trie
typedef struct no* Trie;

// Funcao para criar arvore Trie
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
Trie criar_arvore();

// Funcao para verificar se um no eh nulo
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se nulo
int vazia(Trie h);

// Funcao para liberar arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro Trie
Trie liberar(Trie h);

// Funcao para inserir palavra na arvore
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
Trie inserir(Trie h, char* palavra, int valor);

// Funcao  para remover uma palavra
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
Trie remover(Trie h, char* palavra);

// Funcao auxiliar para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir_aux(Trie h, char* buffer, int n);

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir(Trie h);

// Funcao para buscar palavra
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void busca(Trie h, char* palavra);

// Funcao auxiliar para buscar nome inserindo valor
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void busca_dicionario_aux(Trie h, char* buffer, int valor, int n);

// Funcao para buscar nome inserindo valor
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void busca_dicionario(Trie h, int valor);

#endif
