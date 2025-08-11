#include <stdio.h>
#include <stdlib.h>
#include "arvore23.h"

// Estrutura para arvore23
struct no{
    int chave_esq;
    int chave_dir;
    struct no* esq;
    struct no* meio;
    struct no* dir;
    int num_chaves;
};

// Funcao para criar arvore23
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro Arvore23
Arvore23 criar_arvore()
{
    return NULL;
}

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(Arvore23 raiz)
{
    return (raiz == NULL);
}

// Funcao para buscar na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o no buscado
Arvore23 busca(Arvore23 raiz, int chave)
{
    if(vazia(raiz))
        return raiz;

    if(raiz->chave_esq == chave)
        return raiz;

    if(raiz->num_chaves == 2 && raiz->chave_dir == chave)
        return raiz;

    if(chave < raiz->chave_esq)
        return busca(raiz->esq, chave);

    else if(raiz->num_chaves == 1)
        return busca(raiz->meio, chave);

    else if(chave < raiz->chave_dir)
        return busca(raiz->meio, chave);

    else
        return busca(raiz->dir, chave);
}

// Funcao auxiliar para inserir em 23
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
Arvore23 inserir_aux(Arvore23 raiz, int chave, int* chave_promovida)
{
    if(eh_folha(raiz)){
        if(raiz->num_chaves == 1){
            adiciona_chave(raiz, chave, NULL);
            return NULL;
        }
        else
            return split(raiz, chave, NULL, chave_promovida);
    }
    else{
        Arvore23 p_aux;
        int chave_aux;

        if(chave < raiz->chave_esq)
            p_aux = inserir_aux(raiz->esq, chave, &chave_aux);

        else if((raiz->num_chaves == 1) || (chave < raiz->chave_dir))
            p_aux = inserir_aux(raiz->meio, chave, &chave_aux);

        else
            p_aux = inserir_aux(raiz->dir, chave, &chave_aux);

        if(p_aux == NULL)
            return NULL;

        if(raiz->num_chaves == 1){
            adiciona_chave(raiz, chave_aux, p_aux);
            return NULL;
        }
        else
            return split(raiz, chave_aux, p_aux, chave_promovida);
    }
}

// Funcao para aplicar split em determinado no
// Pre-condicao: elemento na espera de ser inserido
// Pos-condicao: separa um no em dois
Arvore23 split(Arvore23 p, int chave, Arvore23 subarvore, int* chave_promovida)
{
    Arvore23 p_aux;

    if(chave > p->chave_dir){
        *chave_promovida = p->chave_dir;
        p_aux = p->dir;
        p->dir = NULL;
        p->num_chaves = 1;
        return cria_no(chave, 0, p_aux, subarvore, NULL, 1);
    }

    else if(chave >= p->chave_esq){
        *chave_promovida = chave;
        p_aux = p->dir;
        p->dir = NULL;
        p->num_chaves = 1;
        return cria_no(p->chave_dir, 0, subarvore, p_aux, NULL, 1);
    }

    else{
        *chave_promovida = p->chave_esq;
        p_aux = cria_no(p->chave_dir, 0, p->meio, p->dir, NULL, 1);
        p->chave_esq = chave;
        p->num_chaves = 1;
        p->dir = NULL;
        p->meio = subarvore;
        return p_aux;
    }
}

// Funcao para adicionar para adicionar chave
// Pre-condicao: nenhuma
// Pos-condicao: adiciona chave a esquerda ou a direita a depender do tamanho
void adiciona_chave(Arvore23 raiz, int chave, Arvore23 p)
{
    if(raiz->chave_esq < chave){
        raiz->chave_dir = chave;
        raiz->dir = p;
    }
    else{
        raiz->chave_dir = raiz->chave_esq;
        raiz->chave_esq = chave;
        raiz->dir = raiz->meio;
        raiz->meio = p;
    }
    raiz->num_chaves = 2;
}

// Funcao que verifica se um no eh folha
// Pre-condicao: no nao nulo
// Pos-condicao: retorna 1 se folha
int eh_folha(Arvore23 p)
{
    return (!p->esq && !p->meio && !p->dir);
}

// Funcao auxiliar para criar no23
// Pre-condicao: nenhuma
// Pos-condicao: retorna novo no
Arvore23 cria_no(int chave_esq, int chave_dir, Arvore23 esq, Arvore23 meio, Arvore23 dir, int num_chaves)
{
    Arvore23 novo = malloc(sizeof(struct no));
    novo->chave_esq = chave_esq;
    novo->chave_dir = (num_chaves == 2) ? chave_dir : 0;
    novo->esq = esq;
    novo->meio = meio;
    novo->dir = (num_chaves == 2) ? dir : NULL;
    novo->num_chaves = num_chaves;

    return novo;
}

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento
Arvore23 inserir(Arvore23 raiz, int chave)
{
    if(vazia(raiz))
        return cria_no(chave, 0, NULL, NULL, NULL, 1);

    else{
        int chave_promovida;
        Arvore23 aux = inserir_aux(raiz, chave, &chave_promovida);

        if(!vazia(aux))
            return cria_no(chave_promovida, 0, raiz, aux, NULL, 1);

        else
            return raiz;
    }
}

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore ordenada na tela
void inOrdem(Arvore23 raiz)
{
    if(vazia(raiz))
        return;

    inOrdem(raiz->esq);
    printf("%d\n", raiz->chave_esq);
    inOrdem(raiz->meio);
    if(raiz->num_chaves == 2)
        printf("%d\n", raiz->chave_dir);

    if(raiz->num_chaves == 2)
        inOrdem(raiz->dir);
}

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore preOrdenada na tela
void preOrdem(Arvore23 raiz)
{
    if(vazia(raiz))
        return;

    printf("%d - ", raiz->chave_esq);

    if(raiz->num_chaves == 2)
        printf("%d\n", raiz->chave_dir);

    preOrdem(raiz->esq);
    preOrdem(raiz->meio);

    if(raiz->num_chaves == 2)
        preOrdem(raiz->dir);
}

// Funcao de imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime por niveis
void imprimir_niveis(Arvore23 raiz)
{
    if(vazia(raiz))
        return;

    int inicio, fim, i;
    Arvore23* fila = malloc(1000 * sizeof(Arvore23));

    inicio = fim = 0;
    fila[fim++] = raiz;

    while(inicio < fim){
        int nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            Arvore23 atual = fila[inicio++];

            printf("[");
            if(atual->num_chaves >= 1)
                printf("%d", atual->chave_esq);
            if(atual->num_chaves == 2)
                printf(", %d", atual->chave_dir);
            printf("] ");

            if(atual->esq != NULL)
                fila[fim++] = atual->esq;
            if(atual->meio != NULL)
                fila[fim++] = atual->meio;
            if(atual->num_chaves == 2 && atual->dir != NULL)
                fila[fim++] = atual->dir;
        }
        printf("\n");
    }
    free(fila);
}
