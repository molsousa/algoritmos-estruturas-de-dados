#include <stdio.h>
#include <stdlib.h>
#include "../include/rubronegra.h"

void criar_arvore(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(f, cab);
    free(cab);
}

cabecalho* ler_cabecalho(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, f);

    return cab;
}

void escrever_cabecalho(FILE* f, cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, f);
}

no* ler_no(FILE* f, int pos)
{
    no* x = malloc(sizeof(no));

    fseek(f, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fread(x, sizeof(no), 1, f);

    return x;
}

void escrever_no(FILE* f, no* x, int pos)
{
    fseek(f, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fwrite(x, sizeof(no), 1, f);
}

int cor(FILE* f, int pos)
{
    if(pos == -1)
        return PRETO;

    no* x = ler_no(f, pos);
    int res = x->cor;
    free(x);

    return res;
}

void troca_cor(FILE* f, int pos)
{
    no* x = ler_no(f, pos);
    x->cor = !x->cor;

    if(x->esq != -1){
        no* filho_esq = ler_no(f, x->esq);
        filho_esq->cor = !filho_esq->cor;
        escrever_no(f, filho_esq, x->esq);
        free(filho_esq);
    }

    if(x->dir != -1){
        no* filho_dir = ler_no(f, x->dir);
        filho_dir->cor = !filho_dir->cor;
        escrever_no(f, filho_dir, x->dir);
        free(filho_dir);
    }
    escrever_no(f, x, pos);
    free(x);
}

int rotacionar_esquerda(FILE* f, int pos)
{
    no* x = ler_no(f, pos);
    int pos_dir = x->dir;
    no* no_dir = ler_no(f, pos_dir);

    x->esq = no_dir->dir;
    no_dir->dir = pos;

    no_dir->cor = x->cor;
    x->cor = VERMELHO;

    escrever_no(f, no_dir, pos);
    escrever_no(f, x, pos_dir);

    free(x);
    free(no_dir);

    return pos_dir;
}

int rotacionar_direita(FILE* f, int pos)
{
    no* x = ler_no(f, pos);
    int pos_esq = x->esq;
    no* no_esq = ler_no(f, pos_esq);

    x->dir = no_esq->esq;
    no_esq->esq = pos;

    no_esq->cor = x->cor;
    x->cor = VERMELHO;

    escrever_no(f, no_esq, pos);
    escrever_no(f, x, pos_esq);

    free(x);
    free(no_esq);

    return pos_esq;
}

void inserir(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);
    cab->pos_raiz = inserir_aux(f, cab, chave, cab->pos_raiz);

    no* x = ler_no(f, cab->pos_raiz);
    if(cor(f, cab->pos_raiz) != PRETO){
        x->cor = PRETO;
        escrever_no(f, x, cab->pos_raiz);
    }

    escrever_cabecalho(f, cab);

    free(x);
    free(cab);
}

int inserir_aux(FILE* f, cabecalho* cab, int chave, int pos)
{
    if(pos == -1){
        no novo;
        novo.chave = chave;
        novo.cor = VERMELHO;
        novo.dir = novo.esq = -1;

        int nova_pos = cab->pos_topo++;
        escrever_no(f, &novo, nova_pos);
        return nova_pos;
    }
    no* aux = ler_no(f, pos);

    if(aux->chave > chave){
        aux->esq = inserir_aux(f, cab, chave, aux->esq);
        escrever_no(f, aux, pos);
    }

    else if(aux->chave < chave){
        aux->dir = inserir_aux(f, cab, chave, aux->dir);
        escrever_no(f, aux, pos);
    }

    if(cor(f, aux->dir) == VERMELHO && cor(f, aux->esq) == PRETO)
        rotacionar_esquerda(f, pos);

    if(cor(f, aux->esq) == VERMELHO){
        no* aux_esq = ler_no(f, aux->esq);
        if(cor(f, aux_esq->esq) == VERMELHO)
            rotacionar_direita(f, pos);
        free(aux_esq);
    }

    if(cor(f, aux->esq) == VERMELHO && cor(f, aux->dir) == VERMELHO)
        troca_cor(f, pos);

    free(aux);
    return pos;
}

void imprimir(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_raiz;

    imprimir_aux(f, pos);

    free(cab);
}

void imprimir_aux(FILE* f, int pos)
{
    if(pos == -1)
        return;

    no* aux = ler_no(f, pos);

    printf("%d - ", aux->chave);

    if(aux->cor == VERMELHO)
        printf("VERMELHO\n");

    else
        printf("PRETO\n");

    imprimir_aux(f, aux->esq);
    imprimir_aux(f, aux->dir);

    free(aux);
}
