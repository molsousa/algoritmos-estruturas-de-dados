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

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: ponteiro para pagina de B+
boolean vazia(noBMais);

// Funcao para criar arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para tipo noBMais
// Entrada: nenhuma
noBMais criar_arvore();

// Funcao para verificar overflow
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: ponteiro para pagina de B+
boolean overflow(noBMais);

// Funcao para contar folhas totais
// Pre-condicao: nenhuma
// Pos-condicao: insere no ponteiro total o valor total de folhas
// Entrada: ponteiro para pagina de B+, ponteiro para valor total
void conta_nos_folhas_aux(noBMais, int*);

// Funcao para contar nos totais
// Pre-condicao: nenhuma
// Pos-condicao: insere no ponteiro total o valor total de nos
// Entrada: ponteiro para pagina de B+, ponteiro para valor total
void conta_nos_aux(noBMais, int*);

// Funcao chamadora para contar nos
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: ponteiro para pagina de B+, valor para modo
int conta_nos(noBMais, modo);

// Funcao para separar nos
// Pre-condicao: overflow
// Pos-condicao: retorna o no a direita e a chave sucessora no ponteiro
// Entrada: ponteiro para pagina de B+, valor para chave sucessora
noBMais split(noBMais, int*);

// Funcao para buscar posicao de pagina B+
// Pre-condicao: arvore criada
// Pos-condicao: retorna verdadeiro se encontrada a chave
// Entrada: ponteiro para pagina de B+, chave buscada, valor da posicao
boolean busca_pos(noBMais, int, int*);

// Funcao para adicionar chave a direita
// Pre-condicao: nenhuma
// Pos-condicao: insere chave e ponteiro a direita
// Entrada: ponteiro para pagina de B+, posicao da chave e no, chave a ser inserida, ponteiro a ser adicionado
void adicionar_direita(noBMais, int, int, noBMais);

// Funcao auxiliar para inserir em pagina B
// Pre-condicao: nenhuma
// Pos-condicao: insere nova chave
// Entrada: ponteiro para pagina de B+, chave a ser inserida
void inserir_aux(noBMais, int);

// Funcao para criar pagina B
// Pre-condicao: nenhuma
// Pos-condicao: cria um ponteiro para pagina B
// Entrada: chaves a inserir, valor booleano para folha, numero de chaves
noBMais criaPagina(int*, boolean, int);

// Funcao para correcao de ponteiro para pai
// Pre-condicao: nenhuma
// Pos-condicao: insere ponteiro para pai ao no
// Entrada: ponteiro para pagina de B+
void corrigir_pai(noBMais);

// Funcao para correcao de intervalos
// Pre-condicao: nenhuma
// Pos-condicao: corrige e insere ponteiros de proximo aos intervalos
// Entrada: ponteiro para pagina de B+
void corrigir_intervalo(noBMais);

// Funcao para inserir chave na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere chave na arvore
// Entrada: ponteiro para pagina de B+, chave a ser inserida
noBMais inserir(noBMais, int);

// Funcao para imprimir intervalo completo de chaves
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: ponteiro para pagina de B+
void ler_intervalo(noBMais);

// Entrada: ponteiro para pagina de B+, chave a ser removida
noBMais remover(noBMais, int);

// Funcao chamadora para imprimir intervalo
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: ponteiro para pagina de B+, valor a, valor b, modo de intervalo
void imprimir_intervalo(noBMais, int, int, intervalo);

// Funcao para imprimir por niveis
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: ponteiro para pagina de B+
void imprimir_niveis(noBMais);

#endif // ARVORE_B_MAIS_H_INCLUDED
