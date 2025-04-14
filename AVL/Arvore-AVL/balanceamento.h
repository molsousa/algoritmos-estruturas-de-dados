#ifndef BALANCEAMENTO_H_
#define BALANCEAMENTO_H_

// Definicao de tipo para arvore AVL
typedef struct arvore_avl* Arvore_AVL;
// Definicao de tipo para manipulacao de arvore AVL
typedef struct arvore_avl No_AVL;

// Estrutura para arvore AVL
struct arvore_avl{
    int info;
    int altura;
    struct arvore_avl* esq;
    struct arvore_avl* dir;
};

// Funcao para encontrar maior entre dois valores
// Pre-condicao: nenhuma
// Pos-condicao: retorna maior valor
int maior(int x, int y);

// Funcao para retornar altura do no
// Pre-condicao: arvore criada
// Pos-condicao: retorna altura da arvore
int altura_no(No_AVL* no);

// Funcao para retornar a diferenca de altura das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna diferenca de altura das subarvores
int fator_balanceamento(No_AVL* no);

// Funcao para procurar menor no das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna melhor valor da subarvore da esquerda
No_AVL* procura_menor(No_AVL* aux);

// Funcao para aplicar rotacao simples a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a direita
void rotacao_ll(Arvore_AVL* raiz);

// Funcao para aplicar rotacao simples a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a esquerda
void rotacao_rr(Arvore_AVL* raiz);

// Funcao para aplicar rotacao dupla a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a esquerda e outra para a direita
void rotacao_lr(Arvore_AVL* raiz);

// Funcao para aplicar rotacao dupla a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a direita e outra para a esquerda
void rotacao_rl(Arvore_AVL* raiz);

#endif // BALANCEAMENTO_H_
