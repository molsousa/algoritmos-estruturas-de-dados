#include <stdio.h>
#include <stdlib.h>
#include "../include/arvorebp.h"

struct nodeBMais{
    int* chave;
    void** ponteiro;
    short num_chaves;
    boolean eh_folha;
};

noBMais criar_arvore()
{
    return NULL;
}

boolean vazia(noBMais r)
{
    return (r == NULL);
}

boolean overflow(noBMais r)
{
    return (r->num_chaves == ORDEM);
}

noBMais split(noBMais r, int* m)
{
    int q, i;

    noBMais y = malloc(sizeof(struct nodeBMais));
    y->chave = malloc(ORDEM * sizeof(int));
    y->ponteiro = calloc((ORDEM+1), sizeof(void*));

    q = r->num_chaves/2;
    *m = r->chave[q];

    y->ponteiro[0] = r->ponteiro[q+1];

    if(r->eh_folha){
        y->num_chaves = r->num_chaves - q;

        y->eh_folha = true;
        r->num_chaves = q;

        for(i = 0; i < y->num_chaves; i++)
            y->chave[i] = r->chave[q+i];
    }
    else{
        y->num_chaves = r->num_chaves - q - 1;

        y->eh_folha = false;
        r->num_chaves = q;

        for(i = 0; i < y->num_chaves; i++){
            y->chave[i] = r->chave[q+i+1];
            y->ponteiro[i+1] = r->ponteiro[q+i+2];
        }
    }

    return y;
}

boolean busca_pos(noBMais r, int chave, int* pos)
{
    for((*pos) = 0; (*pos) < r->num_chaves; ++*pos)
        if(r->chave[(*pos)] == chave)
            return true;

        else if(chave < r->chave[(*pos)])
            break;

    return false;
}

void adicionar_direita(noBMais r, int pos, int k, noBMais p)
{
    int i;
    for(i = r->num_chaves; i > pos; i--){
        r->chave[i] = r->chave[i-1];
        r->ponteiro[i+1] = r->ponteiro[i];
    }

    r->chave[pos] = k;
    r->ponteiro[pos+1] = p;
    r->num_chaves++;
}

void inserir_aux(noBMais r, int chave)
{
    int pos;

    if(!busca_pos(r, chave, &pos)){
        if(r->eh_folha)
            adicionar_direita(r, pos, chave, NULL);

        else{
            inserir_aux(r->ponteiro[pos], chave);

            if(overflow(r->ponteiro[pos])){
                int m;
                noBMais p = split(r->ponteiro[pos], &m);
                adicionar_direita(r, pos, m, p);
            }
        }
    }
}

noBMais criaPagina(int* chave, boolean eh_folha, int num_chaves)
{
    int i;

    noBMais r;

    r = malloc(sizeof(struct nodeBMais));
    r->chave = malloc(ORDEM * sizeof(int));
    r->ponteiro = calloc((ORDEM+1), sizeof(void*));

    for(i = 0; i < num_chaves; i++)
        r->chave[i] = chave[i];

    r->eh_folha = eh_folha;
    r->num_chaves = num_chaves;

    return r;
}

noBMais inserir(noBMais r, int chave)
{
    if(vazia(r))
        return criaPagina(&chave, true, 1);

    else{
        inserir_aux(r, chave);

        if(overflow(r)){
            int i;
            int m;

            noBMais x = split(r, &m);
            noBMais nova_raiz = criaPagina(&m, false, 1);

            nova_raiz->ponteiro[0] = r;
            nova_raiz->ponteiro[1] = x;

            for(i = (((int)ORDEM/2)+1); i < ORDEM; i++)
                r->ponteiro[i] = NULL;

            return nova_raiz;
        }
    }

    return r;
}

void imprimir_niveis(noBMais r)
{
    if(vazia(r))
        return;

    void** aux = malloc(10000 * sizeof(void*));
    int i, j, nivel, inicio, fim;
    fim = inicio = 0;

    aux[fim++] = r;

    while(fim > inicio){
        nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            noBMais atual = aux[inicio++];
            printf("[");

            for(j = 0; j < atual->num_chaves; j++){
                printf("%d", atual->chave[j]);

                if(j < atual->num_chaves - 1)
                    printf("|");
            }

            printf("]");

            if(atual->eh_folha)
                printf("->");

            else
                printf(" ");

            for(j = 0; j <= atual->num_chaves; j++)
                if(atual->ponteiro[j] != NULL)
                    aux[fim++] = atual->ponteiro[j];
        }
        if(fim == inicio && !r->eh_folha)
            printf("NULL");

        printf("\n");
    }

    free(aux);
}
