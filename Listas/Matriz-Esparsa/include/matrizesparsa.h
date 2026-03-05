#ifndef _MATRIZ_ESPARSA_H_INCLUDED
#define _MATRIZ_ESPARSA_H_INCLUDED

typedef struct matriz* MatEsparsa;

MatEsparsa criar(int, int);

MatEsparsa criar_aux(int, int);

MatEsparsa inserir(MatEsparsa, float, int, int);

MatEsparsa remover(MatEsparsa, float);

void imprimir(MatEsparsa);

void imprimir_teste(MatEsparsa);

#endif
