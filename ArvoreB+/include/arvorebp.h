#ifndef ARVORE_B_MAIS_H_INCLUDED
#define ARVORE_B_MAIS_H_INCLUDED

#define ORDEM 5

// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;
// Definicao de tipo arvoreB+
typedef struct nodeBMais* noBMais;

boolean vazia(noBMais);

noBMais criar_arvore();

noBMais inserir(noBMais, int);

noBMais remover(noBMais, int);

#endif // ARVORE_B_MAIS_H_INCLUDED
