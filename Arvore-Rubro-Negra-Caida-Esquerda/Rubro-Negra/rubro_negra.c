#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

// Estrutura para arvore rubro negra
struct no{
    int info;
    int cor;
    struct no* esq;
    struct no* dir;
};

// Funcao para liberar nos da arvore
static void liberar_arvore_cauda(No* raiz);
// Funcao auxiliar para inserir elemento
static No* inserir_no_cauda(No* raiz, int info);
// Funcao auxiliar para remover elemento
static No* remover_no_cauda(No* raiz, int info);
// Funcao auxiliar para remover o no menor
static No* remover_no_menor(No* no);
// Funcao auxiliar para encontrar o menor valor
static No* procurar_menor(No* no);

// Funcao para criar arvore Rubro Negra
// Pre-condicao: ponteiro para ArvoreRN criado
// Pos-condicao: retorna arvore criada
ArvoreRN* criar_arvore()
{
    system("color C");

    ArvoreRN* novo;

    novo = (ArvoreRN*) malloc(sizeof(ArvoreRN));
    *novo = NULL;

    return novo;
}

// Funcao para liberar arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro ArvoreRN
ArvoreRN* liberar_arvore(ArvoreRN* raiz)
{
    if(raiz == NULL)
        return raiz;

    liberar_arvore_cauda(*raiz);
    free(raiz);

    return NULL;
}

// Funcao para liberar nos da arvore
// Pre-condicao: nenhuma
// Pos-condicao: destroi os nos da arvore
static void liberar_arvore_cauda(No* raiz)
{
    if(raiz == NULL)
        return;

    liberar_arvore_cauda(raiz->esq);
    liberar_arvore_cauda(raiz->dir);

    free(raiz);
}

// Funcao para retornar cor do no
// Pre-condicao: nenhuma
// Pos-condicao: retorna cor do no ou PRETO se for nulo
int cor(No* no)
{
    if(no == NULL)
        return PRETO;

    else
        return no->cor;
}

// Funcao para trocar cor de nos da arvore
// Pre-condicao: ponteiro para no nao nulo
// Pre-condicao: altera cor da raiz e dos dois filhos (se nao forem nulos)
void troca_cor(No* no)
{
    no->cor = !no->cor;

    if(no->esq != NULL)
        no->esq->cor = !no->esq->cor;

    if(no->dir != NULL)
        no->dir->cor = !no->dir->cor;
}

// Funcao para rotacionar a esquerda
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna novo no rotacionado para a esquerda
No* rotacionar_esquerda(No* no)
{
    No* aux = no->dir;

    no->dir = aux->esq;
    aux->esq = no;
    aux->cor = no->cor;
    no->cor = VERMELHO;

    return aux;
}

// Funcao para rotacionar a direita
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna novo no rotacionado para a direita
No* rotacionar_direita(No* no)
{
    No* aux = no->esq;

    no->esq = aux->dir;
    aux->dir = no;
    aux->cor = no->cor;
    no->cor = VERMELHO;

    return aux;
}

// Funcao para mover no a esquerda
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna subarvore rotacionada para a esquerda e com balanceamento de cor
No* mover_para_esquerda(No* no)
{
    troca_cor(no);

    if(cor(no->dir->esq) == VERMELHO){
        no->dir = rotacionar_direita(no->dir);
        no = rotacionar_esquerda(no);
        troca_cor(no);
    }

    return no;
}

// Funcao para mover no a direita
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna subarvore rotacionada para a direita e com balanceamento de cor
No* mover_para_direita(No* no)
{
    troca_cor(no);

    if(cor(no->esq->esq) == VERMELHO){
        no = rotacionar_direita(no);
        troca_cor(no);
    }

    return no;
}

// Funcao auxiliar para balancear apos remocao
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: aplica balanceamento de cores onde for necessario
No* balancear(No* no)
{
    if(cor(no->dir) == VERMELHO)
        no = rotacionar_esquerda(no);

    if(no->esq != NULL && cor(no->esq) == VERMELHO && cor(no->esq->esq) == VERMELHO)
        no = rotacionar_direita(no);

    if(cor(no->esq) == VERMELHO && cor(no->dir) == VERMELHO)
        troca_cor(no);

    return no;
}

// Funcao principal para inserir elemento
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento na arvore e garante raiz preta
void inserir_no(ArvoreRN* raiz, int info)
{
    *raiz = inserir_no_cauda(*raiz, info);
    if(*raiz != NULL)
        (*raiz)->cor = PRETO;
}

// Funcao auxiliar para inserir elemento
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento e aplica balanceamento de cores
static No* inserir_no_cauda(No* raiz, int info)
{
    if(raiz == NULL){
        No* novo = (No*) malloc(sizeof(No));
        novo->info = info;
        novo->esq = NULL;
        novo->dir = NULL;

        novo->cor = VERMELHO;
        return novo;
    }
    else if(info < raiz->info)
        raiz->esq = inserir_no_cauda(raiz->esq, info);

    else if(info > raiz->info)
        raiz->dir = inserir_no_cauda(raiz->dir, info);

    if(cor(raiz->dir) == VERMELHO && cor(raiz->esq) == PRETO)
        raiz = rotacionar_esquerda(raiz);

    if(cor(raiz->esq) == VERMELHO && cor(raiz->esq->esq) == VERMELHO)
        raiz = rotacionar_direita(raiz);

    if(cor(raiz->esq) == VERMELHO && cor(raiz->dir) == VERMELHO)
        troca_cor(raiz);

    return raiz;
}

// Funcao principal para remover no
// Pre-condicao: arvore criada
// Pos-condicao: remove o elemento se encontrado
void remover_no(ArvoreRN* raiz, int info)
{
    if(buscar_arvore(raiz, info) == 0)
        return;

    No* aux = *raiz;
    *raiz = remover_no_cauda(aux, info);

    if(*raiz != NULL)
        (*raiz)->cor = PRETO;
}

// Funcao auxiliar para remover elemento
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: remove o elemento encontrado e aplica o balanceamento de cores
static No* remover_no_cauda(No* raiz, int info)
{
    if(info < raiz->info){
        if(cor(raiz->esq) == PRETO && cor(raiz->esq->esq) == PRETO)
            raiz = mover_para_esquerda(raiz);

        raiz->esq = remover_no_cauda(raiz->esq, info);
    }

    else{
        if(cor(raiz->esq) == VERMELHO)
            raiz = rotacionar_direita(raiz);

        if(info == raiz->info && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }

        if(cor(raiz->dir) == PRETO && cor(raiz->dir->esq) == PRETO)
            raiz = mover_para_direita(raiz);

        if(info == raiz->info){
            No* aux = procurar_menor(raiz->dir);

            raiz->info = aux->info;
            raiz->dir = remover_no_menor(raiz->dir);
        }
        else
            raiz->dir = remover_no_cauda(raiz->dir, info);
    }
    return balancear(raiz);
}

// Funcao auxiliar para remover o no menor
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: remove o menor no da esquerda
static No* remover_no_menor(No* no)
{
    if(no->esq == NULL){
        free(no);
        return NULL;
    }

    if(cor(no->esq) == PRETO && cor(no->esq->esq) == PRETO)
        no = mover_para_esquerda(no);

    no->esq = remover_no_menor(no->esq);

    return balancear(no);
}

// Funcao auxiliar para encontrar o menor valor
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: encontra o no mais a esquerda da subarvore da direita
static No* procurar_menor(No* no)
{
    No* t = no;
    No* p = no->esq;

    while(p != NULL){
        t = p;
        p = p->esq;
    }
    return t;
}

// Funcao para buscar valor na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se encontrado o elemento, 0 se nao
int buscar_arvore(ArvoreRN* raiz, int info)
{
    if(*raiz == NULL)
        return 0;

    if((*raiz)->info == info)
        return 1;

    if((*raiz)->info > info)
        return buscar_arvore(&(*raiz)->esq, info);

    else
        return buscar_arvore(&(*raiz)->dir, info);
}

// Funcao para imprimir arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: arvore impressa na tela
void imprimir_arvore(ArvoreRN* raiz)
{
    if(*raiz == NULL)
        return;

    printf("%d ", (*raiz)->info);

    if((*raiz)->cor == VERMELHO)
        printf("VERMELHO\n");

    else
        printf("NEGRO\n");

    imprimir_arvore(&(*raiz)->esq);
    imprimir_arvore(&(*raiz)->dir);
}
