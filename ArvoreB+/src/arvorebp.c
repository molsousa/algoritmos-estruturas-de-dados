#include <stdio.h>
#include <stdlib.h>
#include "../include/arvorebp.h"

// Estrutura para B+
struct nodeBMais{
    void* ponteiro[ORDEM+1];
    int chave[ORDEM];
    struct nodeBMais* pai;
    boolean eh_folha;
    int num_chaves;
};

boolean vazia(noBMais r)
{
    return (r == NULL);
}

noBMais criar_arvore()
{
    return NULL;
}

boolean overflow(noBMais r)
{
    return (r->num_chaves == ORDEM);
}

noBMais split(noBMais r, int* m)
{
    noBMais y = malloc(sizeof(struct nodeBMais));


    int q = r->num_chaves/2;

    y->num_chaves = r->num_chaves - q - 1;
    r->num_chaves = q;

    *m = r->chave[q];
    int i = 0;

    y->ponteiro[0] = r->ponteiro[q+1];

    while(i < y->num_chaves){
        y->chave[q] = r->chave[q+i];
        y->ponteiro[i+1] = r->ponteiro[q+i+2];
        i++;
    }

    return y;
}

boolean busca_pos(noBMais r, int chave, int* pos)
{
    for(*pos = 0; *pos < r->num_chaves; ++*pos)
        if(chave == r->chave[(*pos)])
            return 1;

        else if(chave < r->chave[(*pos)])
            break;

    return 0;
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
                noBMais aux = split(r->ponteiro[pos], &m);
                adicionar_direita(r, pos, m, aux);
            }
        }
    }
}

noBMais inserir(noBMais r, int chave)
{
    if(vazia(r)){
        int i;

        r = malloc(sizeof(struct nodeBMais));

        r->chave[0] = chave;
        r->pai = NULL;
        r->eh_folha = true;

        for(i = 0; i < ORDEM; i++)
            r->ponteiro[i] = NULL;

        r->num_chaves = 1;
    }
    else{
        inserir_aux(r, chave);

        if(overflow(r)){
            int m;
            int i;

            noBMais x = split(r, &m);
            noBMais nova_raiz = malloc(sizeof(struct nodeBMais));

            nova_raiz->chave[0] = m;

            r->pai = nova_raiz;
            nova_raiz->ponteiro[0] = r;

            x->pai = nova_raiz;
            nova_raiz->ponteiro[1] = x;


            for(i = (((int) ORDEM/2)+1); i < ORDEM; i++)
                r->ponteiro[i] = NULL;

            nova_raiz->num_chaves = 1;

            return nova_raiz;
        }
    }

    return r;
}
