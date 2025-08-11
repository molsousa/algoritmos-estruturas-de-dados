#include <stdio.h>
#include <stdlib.h>
#include "arvore23.h"

// Estrutura para arvore23
struct no23{
    int chave_esq;
    int chave_dir;
    struct no23* esq;
    struct no23* meio;
    struct no23* dir;
    int num_chaves;
};

// Funcao para criar arvore23
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro Arvore23
arvore23 criar_arvore()
{
    return NULL;
}

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(arvore23 raiz)
{
    return (raiz == NULL);
}

// Funcao para buscar na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o no buscado
arvore23 busca(arvore23 raiz, int chave)
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
arvore23 inserir_aux(arvore23 raiz, int chave, int* chave_promovida)
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
        arvore23 p_aux;
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
arvore23 split(arvore23 p, int chave, arvore23 subarvore, int* chave_promovida)
{
    arvore23 p_aux;

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
void adiciona_chave(arvore23 raiz, int chave, arvore23 p)
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
int eh_folha(arvore23 p)
{
    return (!p->esq && !p->meio && !p->dir);
}

// Funcao auxiliar para criar no23
// Pre-condicao: nenhuma
// Pos-condicao: retorna novo no
arvore23 cria_no(int chave_esq, int chave_dir, arvore23 esq, arvore23 meio, arvore23 dir, int num_chaves)
{
    arvore23 novo = malloc(sizeof(struct no23));
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
arvore23 inserir(arvore23 raiz, int chave)
{
    if(vazia(raiz))
        return cria_no(chave, 0, NULL, NULL, NULL, 1);

    else{
        int chave_promovida;
        arvore23 aux = inserir_aux(raiz, chave, &chave_promovida);

        if(!vazia(aux))
            return cria_no(chave_promovida, 0, raiz, aux, NULL, 1);

        else
            return raiz;
    }
}

arvore23 encontrar_sucessor(arvore23 raiz)
{
    arvore23 x = raiz->meio;

    if(!eh_folha(x))
        x = x->esq;

    return x;
}

arvore23 redistribuir(arvore23 pai, int pos_underflow)
{
    if(pos_underflow == 0){
        arvore23 irmao_rico = pai->meio;

        pai->esq = cria_no(pai->chave_esq, 0, NULL, NULL, NULL, 1);
        pai->chave_esq = irmao_rico->chave_esq;

        irmao_rico->chave_esq = irmao_rico->chave_dir;
        irmao_rico->chave_dir = 0;
        irmao_rico->num_chaves--;

        if(!eh_folha(irmao_rico)){
            pai->esq->esq = irmao_rico->esq;
            irmao_rico->esq = irmao_rico->meio;
            irmao_rico->meio = irmao_rico->dir;
            irmao_rico->dir = NULL;
        }
    }
    else{
        arvore23 irmao_rico = pai->esq;

        pai->meio = cria_no(pai->chave_esq, 0, NULL, NULL, NULL, 1);

        pai->chave_esq = irmao_rico->chave_dir;
        irmao_rico->chave_dir = 0;
        irmao_rico->num_chaves = 1;

        if(!eh_folha(irmao_rico)){
            pai->meio->esq = irmao_rico->dir;
            irmao_rico->dir = NULL;
        }
    }

    return pai;
}

arvore23 merge(arvore23 pai, int pos_underflow)
{
    if(pos_underflow == 0){
        arvore23 irmao = pai->meio;

        irmao->chave_dir = irmao->chave_esq;
        irmao->chave_esq = pai->chave_esq;
        irmao->num_chaves = 2;

        pai->chave_esq = pai->chave_dir;
        pai->chave_dir = pai->num_chaves = 0;

        pai->esq = pai->meio;
        pai->meio = pai->dir;
        pai->dir = NULL;

        pai->num_chaves = 1;
    }
    else{
        arvore23 irmao = pai->esq;

        irmao->chave_dir = pai->chave_esq;
        irmao->num_chaves = 2;

        pai->chave_esq = pai->chave_dir;
        pai->chave_dir = 0;
        pai->meio = pai->dir;
        pai->dir = NULL;
        pai->num_chaves--;
    }

    if(pai->num_chaves == 0){
        arvore23 x = pai->esq;
        free(pai);
        return x;
    }

    return pai;
}

arvore23 remover_aux(arvore23 raiz, int chave)
{
    if(eh_folha(raiz)){
        if(raiz->num_chaves == 2 && raiz->chave_dir == chave)
            raiz->num_chaves = 1;

        else if(raiz->chave_esq == chave){
            raiz->chave_esq = raiz->chave_dir;
            raiz->num_chaves = 1;
        }

        if(raiz->num_chaves == 0){
            free(raiz);
            raiz = NULL;
        }
        return raiz;
    }

    if(raiz->chave_esq == chave || (raiz->num_chaves == 2 && raiz->chave_dir == chave)){
        arvore23 sucessor;
        sucessor = encontrar_sucessor(raiz);
        int chave_sucessor = sucessor->chave_esq;

        if(raiz->chave_esq == chave)
            raiz->chave_esq = chave;

        else
            raiz->chave_dir = chave;

        chave = chave_sucessor;
    }

    if(chave < raiz->chave_esq){
        raiz->esq = remover_aux(raiz->esq, chave);

        if(raiz->esq == NULL){
            if(raiz->meio->num_chaves > 1)
                raiz = redistribuir(raiz, 0);

            else
                raiz = merge(raiz, 0);
        }
    }
    else if(raiz->num_chaves == 1 || raiz->chave_dir > chave){
        raiz->meio = remover_aux(raiz->meio, chave);

        if(raiz->meio == NULL){
            if(raiz->esq->num_chaves > 1)
                raiz = redistribuir(raiz, 1);

            else
                raiz = merge(raiz, 1);
        }
    }

    else{
        raiz->dir = remover_aux(raiz->dir, chave);

        if(raiz->dir == NULL){
            if(raiz->meio->num_chaves > 1){
                raiz = redistribuir(raiz, 2);
            }

            else{
                raiz = merge(raiz, 2);
            }
        }
    }

    return raiz;
}

arvore23 remover(arvore23 raiz, int chave)
{
    if(vazia(raiz))
        return NULL;

    raiz = remover_aux(raiz, chave);

    if(raiz != NULL && raiz->num_chaves == 0){
        arvore23 aux = raiz->esq;
        free(raiz);
        raiz = aux;
    }

    return raiz;
}

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore ordenada na tela
void inOrdem(arvore23 raiz)
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
void preOrdem(arvore23 raiz)
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
void imprimir_niveis(arvore23 raiz)
{
    if(vazia(raiz))
        return;

    int inicio, fim, i;
    arvore23* fila = malloc(1000 * sizeof(arvore23));

    inicio = fim = 0;
    fila[fim++] = raiz;

    while(inicio < fim){
        int nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            arvore23 atual = fila[inicio++];

            printf("[");
            if(atual->num_chaves >= 1)
                printf("%d", atual->chave_esq);
            if(atual->num_chaves == 2)
                printf(",%d", atual->chave_dir);

            else
                printf(",-");
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
