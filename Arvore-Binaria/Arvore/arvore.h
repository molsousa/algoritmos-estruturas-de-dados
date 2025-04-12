#ifndef ARVORE_H_
#define ARVORE_H_

// Definicao de tipo para manipulacao de arvore
typedef struct arvore No;
// Definicao de tipo para arvore
typedef struct arvore* Arvore;
// Definicao de tipo para elemento (op)
typedef int Tipo;

// Funcao para criar arvore binaria
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna arvore vazia
Arvore* criar_arvore();

// Funcao para liberar arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro Arvore
Arvore* liberar_arvore(Arvore* raiz);

// Funcao para verificar condicao da arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int arvore_vazia(Arvore* raiz);

// Funcao para contar a quantidade de elementos de uma arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna a quantidade de elementos
int quantidade_elementos(Arvore* raiz);

// Funcao para contar a quantidade de folhas de uma arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna a quantidade de folhas
int quantidade_folha(Arvore* raiz);

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void inserir_no(Arvore* raiz, Tipo x);

// Funcao para remover elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: em caso de dois filhos, remocao in-order (menor subarvore direita)
void remover_no(Arvore* raiz, Tipo x);

// Funcao de busca binaria na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se achou o elemento
int busca_arvore(Arvore* raiz, Tipo x);

// Funcao para imprimir a arvore pre-ordenada
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore_pre(Arvore* raiz);

// Funcao para imprimir a arvore ordenada
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore_ord(Arvore* raiz);

// Funcao para imprimir a arvore pos-ordenada
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore_pos(Arvore* raiz);

#endif // ARVORE_H_
