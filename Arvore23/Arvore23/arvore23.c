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

// Funcao para encontrar sucessor
// Pre-condicao: nenhuma
// Pos-condicao: encontra menor valor da subarvore da direita
Arvore23 encontrar_sucessor(Arvore23 raiz, int* sucessor)
{
    if(eh_folha(raiz)){
        *sucessor = raiz->chave_esq;
        raiz->chave_esq = (raiz->num_chaves == 2) ? raiz->chave_dir : 0;
        raiz->num_chaves--;
        return raiz;
    }

    raiz->esq = encontrar_sucessor(raiz->esq, sucessor);

    if(raiz->esq->num_chaves == 0)
        restaurar_subarvore(raiz, 0);

    return raiz;
}

// Funcao para corrigir underflow
// Pre-condicao: nenhuma
// Pos-condicao: corrige underflow distribuindo a esquerda, direita ou fundindo filhos
void restaurar_subarvore(Arvore23 pai, int pos_filho)
{
    if(pos_filho == 0){
        Arvore23 x = pai->meio;

        if(x->num_chaves == 2)
            redistribuir_esquerda(pai, 1);

        else
            merge(pai, 0);
    }
    else if(pos_filho == 1){
        Arvore23 irmao_esq = pai->esq;

        if(irmao_esq->num_chaves == 2)
            redistribuir_direita(pai, 0);

        else if(pai->num_chaves == 2){
            Arvore23 irmao_dir = pai->dir;

            if(irmao_dir->num_chaves == 2)
                redistribuir_esquerda(pai, 2);
            else
                merge(pai, 1);
        }
        else
            merge(pai, 0);
    }
    else{
        Arvore23 x = pai->meio;
        if(x->num_chaves == 2)
            redistribuir_direita(pai, 1);
        else
            merge(pai, 1);
    }
}

// Funcao para distribuir a esquerda
// Pre-condicao: nenhuma
// Pos-condicao: reajusta chaves sem alterar a altura da arvore
void redistribuir_esquerda(Arvore23 pai, int pos_filho)
{
    Arvore23 x;
    Arvore23 y;

    if(pos_filho == 1){
        x = pai->meio;
        y = pai->esq;

        y->chave_esq = pai->chave_esq;
        y->num_chaves = 1;
        pai->chave_esq = x->chave_esq;
    }
    else{
        x = pai->dir;
        y = pai->meio;

        y->chave_dir = pai->chave_dir;
        y->num_chaves = 2;
        pai->chave_dir = x->chave_esq;
    }

    if(!eh_folha(x)){
        if(pos_filho == 1)
            y->meio = x->esq;
        else
            y->dir = x->esq;
    }

    x->chave_esq = x->chave_dir;
    x->num_chaves = 1;
    x->esq = x->meio;
    x->meio = x->dir;
    x->dir = NULL;
}

// Funcao para distribuir a direita
// Pre-condicao: nenhuma
// Pos-condicao: reajusta chaves sem alterar a altura da arvore
void redistribuir_direita(Arvore23 pai, int pos_filho)
{
    Arvore23 x = pai->esq;
    Arvore23 y = pai->meio;

    y->chave_dir = y->chave_esq;
    y->chave_esq = pai->chave_esq;
    y->num_chaves = 2;

    if(!eh_folha(x)){
        y->dir = y->meio;
        y->meio = y->esq;
        y->esq = x->dir;
    }

    pai->chave_esq = x->chave_dir;
    x->num_chaves = 1;
    x->dir = NULL;
}

// Funcao para fundir irmaos
// Pre-condicao: nenhuma
// Pos-condicao: funde um filho da esquerda com o irmao da direita
void merge(Arvore23 pai, int pos_filho)
{
    Arvore23 x;
    Arvore23 y;

    if(pos_filho == 0){
        x = pai->esq;
        y = pai->meio;

        x->chave_dir = pai->chave_esq;
        x->chave_esq = (x->num_chaves == 1) ? x->chave_esq : y->chave_esq;
        x->num_chaves = 2;

        x->meio = (x->esq != NULL) ? x->meio : y->esq;
        x->dir = y->meio;

        pai->chave_esq = pai->chave_dir;
        pai->meio = pai->dir;
        pai->dir = NULL;
        pai->num_chaves--;

        free(y);
    }
    else{
        x = pai->meio;
        y = pai->dir;

        x->chave_dir = pai->chave_dir;
        x->num_chaves = 2;

        x->dir = y->esq;

        pai->dir = NULL;
        pai->num_chaves--;
        free(y);
    }
}

// Funcao recursiva para remover elemento
// Pre-condicao: nenhuma
// Pos-condicao: remove elemento
Arvore23 remover_recursivo(Arvore23 raiz, int chave, int *fim)
{
    if(vazia(raiz)){
        *fim = 1;
        return NULL;
    }

    int pos_filho;

    if(eh_folha(raiz)){
        if(raiz->num_chaves == 2){
            if(raiz->chave_esq == chave){
                raiz->chave_esq = raiz->chave_dir;
                raiz->num_chaves = 1;
                *fim = 1;
            }
            else if(raiz->chave_dir == chave){
                raiz->num_chaves = 1;
                *fim = 1;
            }
            else
                *fim = 1;
        }
        else{
            if(raiz->chave_esq == chave){
                raiz->num_chaves = 0;
                *fim = 0;
            }
            else
                *fim = 1;
        }
        return raiz;
    }
    if(chave < raiz->chave_esq){
        pos_filho = 0;
        raiz->esq = remover_recursivo(raiz->esq, chave, fim);
    }
    else if(raiz->num_chaves == 1 || chave < raiz->chave_dir){
        if(chave == raiz->chave_esq){
            int sucessor;
            raiz->meio = encontrar_sucessor(raiz->meio, &sucessor);
            raiz->chave_esq = sucessor;
            pos_filho = 1;
        }
        else if(raiz->num_chaves == 2 && chave == raiz->chave_dir){
            int sucessor;
            raiz->dir = encontrar_sucessor(raiz->dir, &sucessor);
            raiz->chave_dir = sucessor;
            pos_filho = 2;
        }
        else{
            pos_filho = 1;
            raiz->meio = remover_recursivo(raiz->meio, chave, fim);
        }
    }
    else{
        pos_filho = 2;
        raiz->dir = remover_recursivo(raiz->dir, chave, fim);
    }
    if(!(*fim)){
        restaurar_subarvore(raiz, pos_filho);
        if(raiz->num_chaves > 0)
            *fim = 1;
    }

    return raiz;
}

// Funcao para remover elemento
// Pre-condicao: arvore criada
// Pos-condicao: remove elemento
Arvore23 remover(Arvore23 raiz, int chave)
{
    if(vazia(raiz))
        return raiz;

    int fim = 0;

    raiz = remover_recursivo(raiz, chave, &fim);

    if(raiz != NULL && raiz->num_chaves == 0){
        Arvore23 temp = raiz;
        raiz = raiz->esq;
        free(temp);
    }

    return raiz;
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
