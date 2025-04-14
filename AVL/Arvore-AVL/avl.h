#ifndef ARVORE_AVL_H_
#define ARVORE_AVL_H_

// Definicao de tipo para arvore AVL
typedef struct arvore_avl* Arvore_AVL;
// Definicao de tipo para manipulacao de arvore AVL
typedef struct arvore_avl No_AVL;

// Funcao para criar arvore AVL
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna arvore vazia
Arvore_AVL* criar_arvore();

// Funcao para liberar arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro vazio
void* liberar_arvore(Arvore_AVL* raiz);

// Funcao para inserir elemento na arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int inserir_elemento(Arvore_AVL* raiz, int info);

// Funcao para remover elemento da arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int remover_elemento(Arvore_AVL* raiz, int info);

// Funcao para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore(Arvore_AVL* raiz);

#endif // ARVORE_AVL_H_
