#include <stdio.h>
#include <stdlib.h>
#include "../include/matrizesparsa.h"

struct matriz{
    struct matriz* direita;
    struct matriz* baixo;
    int linha;
    int coluna;
    float valor;
};

MatEsparsa criar(int m, int n)
{
    MatEsparsa mat = malloc(sizeof(struct matriz));
    MatEsparsa aux;

    mat->linha = mat->coluna = -1;
    mat->direita = criar_aux(m-1, 0);
    mat->baixo = criar_aux(n-1, 1);

    aux = mat;
    while(aux->direita != NULL)
        aux = aux->direita;

    aux->direita = mat;

    aux = mat;
    while(aux->baixo != NULL)
        aux = aux->baixo;

    aux->baixo = mat;

    return mat;
}

MatEsparsa criar_aux(int m, int flag)
{
    if(m == -1)
        return NULL;

    MatEsparsa mat;

    mat = malloc(sizeof(struct matriz));
    mat->coluna = mat->linha = 0;
    mat->valor = 0.0f;

    if(!flag){
        mat->coluna = -1;
        mat->baixo = NULL;
        mat->direita = criar_aux(m-1, flag);
    }
    else{
        mat->linha = -1;
        mat->direita = NULL;
        mat->baixo = criar_aux(m-1, flag);
    }

    return mat;
}
