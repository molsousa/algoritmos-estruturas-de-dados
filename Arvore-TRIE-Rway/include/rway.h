#ifndef _ARVORE_TRIE_RWAY_H_INCLUDED
#define _ARVORE_TRIE_RWAY_H_INCLUDED
#define TAM_ALFABETO 26
#define ASCII_BASE 97

typedef struct fila* Fila;
typedef struct noTrie* Trie;
typedef struct trie arvTrie;

arvTrie* criar_arvore();

int vazia(Trie);

void inserir(arvTrie*, char*, int);

Trie inserir_aux(Trie, char*, int);

void remover(arvTrie*, char*);

void imprimir_dicionario(arvTrie*);

int buscar(arvTrie*, char*);

void imprimir(arvTrie*);

void imprimir_aux(Trie, Fila);

#endif // _ARVORE_TRIE_RWAY_H_INCLUDED
