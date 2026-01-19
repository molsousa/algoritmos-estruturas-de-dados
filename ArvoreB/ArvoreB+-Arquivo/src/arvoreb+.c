#include <stdio.h>
#include <stdlib.h>
#include "../include/arvoreb+.h"

void escrever_cabecalho(FILE* f, cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, f);
}

cabecalho* ler_cabecalho(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));
    if(!cab)
        err();

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, f);

    return cab;
}

void escrever_pagina(FILE* f, paginaBMais* x, int pos)
{
    fseek(f, sizeof(cabecalho) + sizeof(paginaBMais)*pos, SEEK_SET);
    fwrite(x, sizeof(paginaBMais), 1, f);
}

paginaBMais* ler_pagina(FILE* f, int pos)
{
    paginaBMais* x = malloc(sizeof(paginaBMais));
    if(!x)
        err();

    fseek(f, sizeof(cabecalho) + sizeof(paginaBMais)*pos, SEEK_SET);
    fread(x, sizeof(paginaBMais), 1, f);

    return x;
}

void inicializar(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));
    if(!cab)
        err();

    cab->pos_raiz = cab->pos_livre = -1;
    cab->pos_topo = 0;

    escrever_cabecalho(f, cab);
    free(cab);
}

boolean vazia(int pos)
{
    return (pos == -1);
}

boolean overflow(FILE* f, int pos)
{
    paginaBMais* x = ler_pagina(f, pos);
    int num_chaves = x->num_chaves;

    free(x);

    return (num_chaves == ORDEM);
}

int obter_pos_livre(FILE* f, cabecalho* cab)
{
    int pos;

    if(!vazia(cab->pos_livre)){
        pos = cab->pos_livre;
        paginaBMais* no_livre = ler_pagina(f, pos);
        cab->pos_livre = no_livre->ponteiro[0];

        free(no_livre);
    }
    else
        pos = cab->pos_topo++;

    return pos;
}

int split(FILE* f, cabecalho* cab, int pos, int* m)
{
    int q, i, pos_y;

    paginaBMais* r = ler_pagina(f, pos);
    paginaBMais y;

    q = r->num_chaves/2;
    *m = r->chave[q];

    y.ponteiro[0] = r->ponteiro[q+1];

    if(r->eh_folha){
        y.num_chaves = r->num_chaves - q;

        y.eh_folha = true;
        r->num_chaves = q;

        for(i = 0; i < y.num_chaves; i++)
            y.chave[i] = r->chave[q+i];

        for(i = 0; i <= y.num_chaves; i++)
            y.ponteiro[i] = -1;
    }

    else{
        y.num_chaves = r->num_chaves - q - 1;

        y.eh_folha = false;
        r->num_chaves = q;

        for(i = 0; i < y.num_chaves; i++){
            y.chave[i] = r->chave[q+i+1];
            y.ponteiro[i+1] = r->ponteiro[q+i+2];
        }
    }
    pos_y = obter_pos_livre(f, cab);

    escrever_pagina(f, r, pos);
    escrever_pagina(f, &y, pos_y);

    free(r);

    return pos_y;
}

boolean busca_pos(FILE* f, int pos, int chave, int* pos_chave)
{
    paginaBMais* r = ler_pagina(f, pos);

    for(*pos_chave = 0; *pos_chave < r->num_chaves; ++*pos_chave){
        if(chave == r->chave[(*pos_chave)]){
            free(r);
            return true;
        }
        else if(chave < r->chave[(*pos_chave)])
            break;
    }
    free(r);

    return false;
}

void adicionar_direita(FILE* f, int pos_r, int pos_chave, int k, int pos_p)
{
    int i;
    paginaBMais* r = ler_pagina(f, pos_r);

    for(i = r->num_chaves; i > pos_chave; i--){
        r->chave[i] = r->chave[i-1];
        r->ponteiro[i+1] = r->ponteiro[i];
    }

    if(pos_p != -1){
        paginaBMais* p = ler_pagina(f, pos_p);

        if(!p->eh_folha)
            corrigir_pai(f, pos_p);

        p->pai = pos_r;

        escrever_pagina(f, p, pos_p);
        free(p);
    }

    r->chave[pos_chave] = k;
    r->ponteiro[pos_chave+1] = pos_p;
    r->num_chaves++;

    escrever_pagina(f, r, pos_r);
}

void inserir_aux(FILE* f, int pos, cabecalho* cab, int chave)
{
    int pos_chave;

    if(!busca_pos(f, pos, chave, &pos_chave)){
        paginaBMais* r = ler_pagina(f, pos);

        if(r->eh_folha)
            adicionar_direita(f, pos, pos_chave, chave, -1);

        else{
            int pos_filho = r->ponteiro[pos_chave];

            inserir_aux(f, pos_filho, cab, chave);

            if(overflow(f, pos_filho)){
                int m;
                int pos_p = split(f, cab, pos_filho, &m);
                adicionar_direita(f, pos, pos_chave, m, pos_p);
            }

        }
        free(r);
    }
}

int criaPagina(FILE* f, int* chave, cabecalho* cab, boolean eh_folha, int num_chaves)
{
    int i, pos;

    paginaBMais x;

    x.pai = -1;

    for(i = 0; i < num_chaves; i++)
        x.chave[i] = chave[i];

    for(i = 0; i <= ORDEM; i++)
        x.ponteiro[i] = -1;

    x.eh_folha = eh_folha;
    x.num_chaves = num_chaves;

    pos = obter_pos_livre(f, cab);
    escrever_pagina(f, &x, pos);

    return pos;
}

void corrigir_pai(FILE* f, int pos)
{
    paginaBMais* r;
    paginaBMais* pai = ler_pagina(f, pos);

    int i;

    for(i = 0; i <= pai->num_chaves; i++){
        r = ler_pagina(f, pai->ponteiro[i]);
        r->pai = pos;

        escrever_pagina(f, r, pai->ponteiro[i]);
        free(r);
    }
}

/*
void corrigir_intervalo(FILE* f, cabecalho* cab)
{
    paginaBMais* aux[10000];
    paginaBMais* nos_intervalo[10000];

    int i, j, k, fim, inicio, nivel;
    k = fim = inicio = 0;

    aux[fim++] = ler_pagina(f, cab->pos_raiz);

    while(fim > inicio){
        nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            paginaBMais* atual = aux[inicio++];

            if(atual->eh_folha)
                nos_intervalo[k++] = atual;

            for(j = 0; j <= atual->num_chaves; j++){
                if(atual->ponteiro[j] != -1)
                    aux[fim++] = ler_pagina(f, atual->ponteiro[j]);
            }
        }
    }

    for(i = 0; i < k-1; i++){
        paginaBMais* atual = nos_intervalo[i];
        paginaBMais* prox = nos_intervalo[i+1];

        atual->ponteiro[ORDEM] = prox;
    }
}
*/

int inserir(FILE* f, int pos, cabecalho* cab, int chave)
{
    if(vazia(pos))
        return criaPagina(f, &chave, cab, true, 1);

    else{
        inserir_aux(f, pos, cab, chave);

        if(overflow(f, pos)){
            int i;
            int m;

            int pos_x = split(f, cab, pos, &m);
            int pos_nova_raiz = criaPagina(f, &m, cab, false, 1);

            paginaBMais* nova_raiz = ler_pagina(f, pos_nova_raiz);

            nova_raiz->ponteiro[0] = pos;
            nova_raiz->ponteiro[1] = pos_x;

            paginaBMais* r = ler_pagina(f, pos);
            paginaBMais* x = ler_pagina(f, pos_x);

            x->pai = r->pai = pos_nova_raiz;

            if(!r->eh_folha){
                corrigir_pai(f, pos);
                corrigir_pai(f, pos_x);
            }

            for(i = (((int)ORDEM/2)+1); i < ORDEM; i++)
                r->ponteiro[i] = -1;

            // corrigir_intervalo

            escrever_pagina(f, x, pos_x);
            escrever_pagina(f, r, pos);
            escrever_pagina(f, nova_raiz, pos_nova_raiz);

            free(r);
            free(x);
            free(nova_raiz);

            return pos_nova_raiz;
        }
    }

    return pos;
}

void insere(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    cab->pos_raiz = inserir(f, cab->pos_raiz, cab, chave);
    escrever_cabecalho(f, cab);

    free(cab);
}

void imprimir_niveis(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_raiz;
    free(cab);

    if(vazia(pos))
        return;

    paginaBMais* aux[10000];
    int inicio, fim, i, j, cont;

    inicio = fim = 0;
    aux[fim++] = ler_pagina(f, pos);

    while(fim > inicio){
        cont = fim - inicio;

        for(i = 0; i < cont; i++){
            paginaBMais* atual = aux[inicio];

            printf("[");

            for(j = 0; j <= atual->num_chaves; j++){
                if(j < atual->num_chaves){
                    printf("%d", atual->chave[j]);

                    if(j+1 < atual->num_chaves)
                        printf(",");
                }

                if(atual->ponteiro[j] != -1)
                    aux[fim++] = ler_pagina(f, atual->ponteiro[j]);
            }

            printf("] ");
            inicio++;
        }

        printf("\n");
    }

    while(fim >= 0)
        free(aux[--fim]);
}

void err()
{
    printf("erro na alocacao\n");
    exit(1);
}
