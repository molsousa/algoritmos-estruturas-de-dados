#ifndef _ARVORE_TRIE_RWAY_H_INCLUDED
#define _ARVORE_TRIE_RWAY_H_INCLUDED

#define TAM_ALFABETO 26
#define ASCII_BASE 97

typedef enum{false = 0, true = 1} bool;
typedef struct noTrie* Trie;
typedef struct trie arvTrie;

// Funcao para criar arvore TRIE
// Pre-condicao: nenhuma
// Pos-condicao: cria arvore com raiz alocada
arvTrie* criar_arvore();

// Funcao para verificar se um no eh vazio
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se vazio
int vazia(Trie);

// Funcao para inserir em arvore TRIE
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void inserir(arvTrie*, char*, int);

// Funcao auxiliar para insercao
// Pre-condicao: nenhuma
// Pos-condicao: encadeia os nos compativeis com a string desejada
Trie inserir_aux(Trie, char*, int);

// Funcao para remover string
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void remover(arvTrie*, char*);

// Funcao auxiliar remocao
// Pre-condicao: nenhuma
// Pos-condicao: desencadeia e libera os nos que nao tiverem filhos
Trie remover_aux(Trie, char*);

// Verifica se um no tem filho
// Pre-condicao: nenhuma
// Pos-condicao: retorna verdadeiro caso tenha
bool tem_filho(Trie raiz);

// Funcao para buscar string
// Pre-condicao: arvore criada
// Pos-condicao: retorna o valor da chave
int buscar(arvTrie*, char*);

// Funcao auxiliar para busca
// Pre-condicao: nenhuma
// Pos-condicao: retorna o valor da chave
int buscar_aux(Trie, char*);

// Funcao para imprimir dicionario
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir(arvTrie*);

// Funcao auxiliar para impressao
// Pre-condicao: nenhuma
// Pos-condicao: imprime todos os nomes na tela com seu respectivo valor
void imprimir_aux(Trie, char*, int);

#endif // _ARVORE_TRIE_RWAY_H_INCLUDED
