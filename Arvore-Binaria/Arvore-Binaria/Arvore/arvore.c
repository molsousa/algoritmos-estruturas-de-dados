#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "fila.h"

// Estrutura para arvore
struct no{
    int info;
    struct no* esq;
    struct no* dir;
};

// Funcao para criar arvore vazia
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para variavel Arvore
Arvore criar_arvore()
{
    return NULL;
}

// Funcao para testar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(Arvore raiz)
{
    return (raiz == NULL);
}

// Funcao para inserir no na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento na arvore
Arvore inserir_no(Arvore raiz, int info)
{
    if(vazia(raiz)){
        raiz = malloc(sizeof(struct no));
        raiz->info = info;
        raiz->esq = raiz->dir = NULL;
        return raiz;
    }
    else if(raiz->info > info)
        raiz->esq = inserir_no(raiz->esq, info);
    else if(raiz->info < info)
        raiz->dir = inserir_no(raiz->dir, info);

    return raiz;
}

// Funcao para remover no na arvore
// Pre-condicao: arvore criada
// Pos-condicao: remove elemento da arvore
Arvore remover_no(Arvore raiz, int info)
{
    if(vazia(raiz))
        return raiz;

    else if(raiz->info > info)
        raiz->esq = remover_no(raiz->esq, info);

    else if(raiz->info < info)
        raiz->dir = remover_no(raiz->dir, info);

    else{
        Arvore aux = raiz;
        if(!raiz->esq && !raiz->dir){
            free(aux);
            return NULL;
        }
        else if(!raiz->esq){
            raiz = raiz->dir;
            free(aux);
        }

        else if(!raiz->dir){
            raiz = raiz->esq;
            free(aux);
        }

        else{
            aux = raiz->dir;

            while(aux->esq != NULL)
                aux = aux->esq;

            raiz->info = aux->info;
            raiz->dir = remover_no(raiz->dir, aux->info);
        }
    }
    return raiz;
}

// Funcao que retorna o maior valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o valor do no mais a direita
int maximo(Arvore raiz)
{
    if(vazia(raiz->dir))
        return raiz->info;

    return maximo(raiz->dir);
}

// Funcao que retorna o menor valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o valor do no mais a esquerda
int minimo(Arvore raiz)
{
    if(vazia(raiz->esq))
        return raiz->info;

    return minimo(raiz->esq);
}

// Funcao para calcular altura de uma arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: retorna altura da arvore
int altura(Arvore raiz)
{
    if(vazia(raiz))
        return 0;

    else{
        int esq = altura(raiz->esq);
        int dir = altura(raiz->dir);

        if(esq > dir)
            return (esq+1);

        else
            return (dir+1);
    }
    return 0;
}

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime a arvore em ordem
void inOrdem(Arvore raiz)
{
    if(vazia(raiz))
        return;

    inOrdem(raiz->esq);
    printf("%d\n", raiz->info);
    inOrdem(raiz->dir);
}

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime a arvore em pre ordem
void preOrdem(Arvore raiz)
{
    if(vazia(raiz))
        return;

    printf("%d\n", raiz->info);

    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
}

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime a arvore em pos ordem
void posOrdem(Arvore raiz)
{
    if(vazia(raiz))
        return;

    posOrdem(raiz->esq);
    posOrdem(raiz->dir);

    printf("%d\n", raiz->info);
}

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: imprime por nivel os elementos da arvore
void imprimir_por_niveis(Arvore raiz)
{
    if(vazia(raiz))
        return;

    Fila* f = criar_fila();
    int i = 1;

    enqueue(f, raiz);
    enqueue(f, NULL);

    printf("Nivel: %d -> ", i++);
    while(!fila_vazia(f)){
        struct no* atual = dequeue(f);

        if(atual == NULL){
            printf("\n");

            if(!fila_vazia(f)){
                printf("Nivel: %d -> ", i++);
                enqueue(f, NULL);
            }
        }
        else{
            printf("%d ", atual->info);

            if(atual->esq != NULL)
                enqueue(f, atual->esq);

            if(atual->dir != NULL)
                enqueue(f, atual->dir);
        }
    }
    liberar_fila(f);
}
