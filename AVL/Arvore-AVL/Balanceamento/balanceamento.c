#include <stdlib.h>
#include "balanceamento.h"

// Funcao para encontrar maior entre dois valores
// Pre-condicao: nenhuma
// Pos-condicao: retorna maior valor
int maior(int x, int y)
{
    if(x > y)
        return x;

    return y;
}

// Funcao para retornar altura do no
// Pre-condicao: arvore criada
// Pos-condicao: retorna altura da arvore
int altura_no(No_AVL* no)
{
    if(no == NULL)
        return -1;

    return no->altura;
}

// Funcao para retornar a diferenca de altura das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna diferenca de altura das subarvores
int fator_balanceamento(No_AVL* no)
{
    return labs(altura_no(no->esq) - altura_no(no->dir));
}

// Funcao para procurar menor no das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna melhor valor da subarvore da esquerda
No_AVL* procura_menor(No_AVL* aux)
{
    No_AVL* no_1 = aux;
    No_AVL* no_2 = aux->esq;

    while(no_2 != NULL){
        no_1 = no_2;
        no_2 = no_2->esq;
    }

    return no_1;
}

// Funcao para aplicar rotacao simples a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a direita
void rotacao_ll(Arvore_AVL* raiz)
{
    No_AVL* aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);

    (*raiz)->altura = maior(altura_no((*raiz)->esq), altura_no((*raiz)->dir)) + 1;
    aux->altura = maior(altura_no(aux->esq), (*raiz)->altura) + 1;

    *raiz = aux;
}

// Funcao para aplicar rotacao simples a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a esquerda
void rotacao_rr(Arvore_AVL* raiz)
{
    No_AVL* aux;

    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);

    (*raiz)->altura = maior(altura_no((*raiz)->esq), altura_no((*raiz)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), (*raiz)->altura) + 1;

    *raiz = aux;
}

// Funcao para aplicar rotacao dupla a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a esquerda e outra para a direita
void rotacao_lr(Arvore_AVL* raiz)
{
    rotacao_rr(&(*raiz)->esq);
    rotacao_ll(raiz);
}

// Funcao para aplicar rotacao dupla a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a direita e outra para a esquerda
void rotacao_rl(Arvore_AVL* raiz)
{
    rotacao_ll(&(*raiz)->dir);
    rotacao_rr(raiz);
}
