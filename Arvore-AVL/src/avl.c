#include <stdio.h>
#include <stdlib.h>
#include "../include/avl.h"
#include "../include/fila.h"

struct noAVL{
    int chave;
    int altura;
    struct noAVL* esq;
    struct noAVL* dir;
};

// Funcao para criar arvore AVL
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna arvore vazia
arvoreAVL* criar_arvore()
{
    arvoreAVL* novo;

    novo = malloc(sizeof(arvoreAVL));
    *novo = NULL;

    return novo;
}

// Verificar se um no eh vazio
// Pre-condicao: nenhum
// Pos-condicao: retorna true se vazio
boolean vazia(struct noAVL* r)
{
    return (r == NULL);
}

// Funcao para liberar arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro vazio
void* liberar_arvore(arvoreAVL* r)
{
    if(vazia(*r))
        return r;

    liberar_no(*r);

    return NULL;
}

// Funcao auxiliar para liberar arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: destroi nos da arvore
void liberar_no(struct noAVL* r)
{
    if(vazia(r))
        return;

    liberar_no(r->esq);
    liberar_no(r->dir);
    free(r);
}

// Funcao para retornar altura do no
// Pre-condicao: arvore criada
// Pos-condicao: retorna altura da arvore
int altura_no(struct noAVL* r)
{
    if(vazia(r))
        return -1;

    return r->altura;
}

// Funcao para retornar a diferenca de altura das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna diferenca de altura das subarvores
int fator_balanceamento(struct noAVL* r)
{
    return labs(altura_no(r->esq) - altura_no(r->dir));
}

// Funcao para procurar menor no das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna melhor valor da subarvore da esquerda
struct noAVL* procura_menor(struct noAVL* aux)
{
    while(!vazia(aux->esq))
        aux = aux->esq;

    return aux;
}

// Funcao para aplicar rotacao simples a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a direita
void rotacao_ll(arvoreAVL* r)
{
    struct noAVL* aux;

    aux = (*r)->esq;
    (*r)->esq = aux->dir;
    aux->dir = (*r);

    (*r)->altura = maior(altura_no((*r)->esq), altura_no((*r)->dir)) + 1;
    aux->altura = maior(altura_no(aux->esq), (*r)->altura) + 1;

    *r = aux;
}

// Funcao para aplicar rotacao simples a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a esquerda
void rotacao_rr(arvoreAVL* r)
{
    struct noAVL* aux;

    aux = (*r)->dir;
    (*r)->dir = aux->esq;
    aux->esq = (*r);

    (*r)->altura = maior(altura_no((*r)->esq), altura_no((*r)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), (*r)->altura) + 1;

    *r = aux;
}

// Funcao para aplicar rotacao dupla a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a esquerda e outra para a direita
void rotacao_lr(arvoreAVL* r)
{
    rotacao_rr(&(*r)->esq);
    rotacao_ll(r);
}

// Funcao para aplicar rotacao dupla a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a direita e outra para a esquerda
void rotacao_rl(arvoreAVL* r)
{
    rotacao_ll(&(*r)->dir);
    rotacao_rr(r);
}

// Funcao para inserir elemento na arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int inserir(arvoreAVL* r, int chave)
{
    int res;

    if(vazia(*r)){
        struct noAVL* novo = malloc(sizeof(struct noAVL));
        novo->chave = chave;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;

        *r = novo;
        return 1;
    }

    struct noAVL* aux = *r;

    if(chave < aux->chave){
        if((res = inserir(&(aux->esq), chave)) == 1){
            if(fator_balanceamento(aux) > 1){
                if(chave < (*r)->esq->chave)
                    rotacao_ll(r);
                else
                    rotacao_lr(r);
            }
        }
    }
    else{
        if(chave > aux->chave){
            if((res = inserir(&(aux->dir), chave)) == 1){
                if(fator_balanceamento(aux) > 1){
                    if(chave > (*r)->dir->chave)
                        rotacao_rr(r);
                    else
                        rotacao_rl(r);
                }
            }
        }
    }

    aux->altura = maior(altura_no(aux->esq), altura_no(aux->dir)) + 1;

    return res;
}

// Funcao para remover elemento da arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int remover(arvoreAVL* r, int chave)
{
    if(vazia(*r))
        return 0;

    int res;

    if(chave < (*r)->chave){
        if((res = remover(&(*r)->esq, chave)) == 1){
            if(fator_balanceamento(*r) > 1){
                if(altura_no((*r)->dir->esq) <= altura_no((*r)->dir->dir))
                    rotacao_rr(r);
                else
                    rotacao_rl(r);
            }
        }
    }
    if(chave > (*r)->chave){
        if((res = remover(&(*r)->dir, chave)) == 1){
            if(fator_balanceamento(*r) > 1){
                if(altura_no((*r)->esq->dir) <= altura_no((*r)->esq->esq))
                    rotacao_ll(r);
                else
                    rotacao_lr(r);
            }
        }
    }

    if((*r)->chave == chave){
        struct noAVL* aux = *r;

        if(!aux->esq && !aux->dir){
            free(aux);
            *r = NULL;
        }
        else if(!aux->esq && aux->dir){
            (*r) = (*r)->dir;
            free(aux);
        }
        else if(aux->esq && !aux->dir){
            (*r) = (*r)->esq;
            free(aux);
        }
        else{
            aux = procura_menor((*r)->dir);
            (*r)->chave = aux->chave;
            remover(&(*r)->dir, (*r)->chave);

            if(fator_balanceamento(*r) > 1){
                if(altura_no((*r)->esq->dir) <= altura_no((*r)->esq->esq))
                   rotacao_ll(r);
                else
                    rotacao_lr(r);
            }
        }

        if(*r != NULL)
            (*r)->altura = maior(altura_no((*r)->esq), altura_no((*r)->dir)) + 1;
        return 1;
    }

    (*r)->altura = maior(altura_no((*r)->esq), altura_no((*r)->dir)) + 1;

    return res;
}

// Funcao para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore(arvoreAVL* r)
{
    if(*r == NULL)
        return;

    imprimir_aux(*r);
}

// Funcao auxiliar para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: imprime em percurso pre-order
void imprimir_aux(struct noAVL* r)
{
    if(vazia(r))
        return;

    printf("%d\n", r->chave);

    imprimir_aux(r->esq);
    imprimir_aux(r->dir);
}

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: imprime os nos por niveis
void imprimir_niveis(arvoreAVL* r)
{
    if(vazia(*r))
        return;

    struct noAVL* aux[10000];
    int fim, inicio, cont, i;

    inicio = fim = 0;

    aux[fim++] = *r;

    while(fim > inicio){
        cont = fim - inicio;
        printf("<");

        for(i = 0; i < cont; i++){
            struct noAVL* atual = aux[inicio++];
            printf("%d", atual->chave);

            if(atual->esq)
                aux[fim++] = atual->esq;

            if(atual->dir)
                aux[fim++] = atual->dir;

            if(i+1 < cont)
                printf(" ");
        }
        printf(">\n");
    }
}
