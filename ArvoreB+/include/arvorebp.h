#ifndef ARVORE_B_MAIS_H_INCLUDED
#define ARVORE_B_MAIS_H_INCLUDED

#define ORDEM 7
#define MIN_CHAVES ((ORDEM - 1)/2)

// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;

// Definicao de tipo para intervalo
typedef enum{
    aberto, fechado
}intervalo;

// Definicao de tipo para modo
typedef enum{
    folha, interno, nosTotais
}modo;

// Definicao de tipo arvoreB+
typedef struct nodeBMais* noBMais;

// Entrada: ponteiro para no de B+
boolean vazia(noBMais);

noBMais criar_arvore();

// Entrada: ponteiro para no de B+
boolean overflow(noBMais);

// Entrada: ponteiro para no de B+, ponteiro para valor total
void conta_nos_folhas_aux(noBMais, int*);

// Entrada: ponteiro para no de B+, ponteiro para valor total
void conta_nos_aux(noBMais, int*);

// Entrada: ponteiro para no de B+, valor para modo
int conta_nos(noBMais, modo);

// Entrada: ponteiro para no de B+, valor para chave sucessora
noBMais split(noBMais, int*);

// Entrada: ponteiro para no de B+, chave buscada, valor da posicao
boolean busca_pos(noBMais, int, int*);

// Entrada: ponteiro para no de B+, posicao da chave e no, chave a ser inserida, ponteiro a ser adicionado
void adicionar_direita(noBMais, int, int, noBMais);

// Entrada: ponteiro para no de B+, chave a ser inserida
void inserir_aux(noBMais, int);

// Entrada: chaves a inserir, valor booleano para folha, numero de chaves
noBMais criaPagina(int*, boolean, int);

// Entrada: ponteiro para no de B+
void corrigir_pai(noBMais);

// Entrada: ponteiro para no de B+
void corrigir_intervalo(noBMais);

// Entrada: ponteiro para no de B+, chave a ser inserida
noBMais inserir(noBMais, int);

// Entrada: ponteiro para no de B+
void ler_intervalo(noBMais);

// Entrada: ponteiro para no de B+, chave a ser removida
noBMais remover(noBMais, int);

// Entrada: ponteiro para no de B+, valor a, valor b, modo de intervalo
void imprimir_intervalo(noBMais, int, int, intervalo);

// Entrada: ponteiro para no de B+
void imprimir_niveis(noBMais);

#endif // ARVORE_B_MAIS_H_INCLUDED
