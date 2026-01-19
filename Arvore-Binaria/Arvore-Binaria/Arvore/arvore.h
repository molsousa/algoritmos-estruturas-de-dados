#ifndef ARVORE_BINARIA_H_INCLUDED
#define ARVORE_BINARIA_H_INCLUDED

// Definicao de tipo para manipulacao de arvore
typedef struct no* Arvore;

// Funcao para criar arvore vazia
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para variavel Arvore
Arvore criar_arvore();

// Funcao para testar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(Arvore raiz);

// Funcao para inserir no na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento na arvore
Arvore inserir_no(Arvore raiz, int info);

// Funcao para remover no na arvore
// Pre-condicao: arvore criada
// Pos-condicao: remove elemento da arvore
Arvore remover_no(Arvore raiz, int info);

// Funcao que retorna o maior valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o valor do no mais a direita
int maximo(Arvore raiz);

// Funcao que retorna o menor valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o valor do no mais a esquerda
int minimo(Arvore raiz);

// Funcao para calcular altura de uma arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: retorna altura da arvore
int altura(Arvore raiz);

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime a arvore em ordem
void inOrdem(Arvore raiz);

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime a arvore em pre ordem
void preOrdem(Arvore raiz);

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime a arvore em pos ordem
void posOrdem(Arvore raiz);

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime por nivel os elementos da arvorevoid imprimir_por_niveis(Arvore raiz);
void imprimir_por_niveis(Arvore raiz);

#endif // ARVORE_BINARIA_H_INCLUDED
