#ifndef ARVORE_B_MAIS_H_INCLUDED
#define ARVORE_B_MAIS_H_INCLUDED

#define ORDEM 7

// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;
// Definicao de tipo arvoreB+
typedef struct nodeBMais* noBMais;

boolean vazia(noBMais);

noBMais criar_arvore();

boolean overflow(noBMais);

noBMais split(noBMais, int*);

boolean busca_pos(noBMais, int, int*);

void adicionar_direita(noBMais, int, int, noBMais);

void inserir_aux(noBMais, int);

noBMais inserir(noBMais, int);

noBMais remover(noBMais, int);

void imprimir_niveis(noBMais);

#endif // ARVORE_B_MAIS_H_INCLUDED
