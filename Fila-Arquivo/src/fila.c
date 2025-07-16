#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

// Funcao para criar fila
// Pre-condicao: arquivo aberto
// Pos-condicao: cria cabecalho no arquivo binario
void criar_fila(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_cabeca = -1;
    cab->pos_ultimo = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para ler cabecalho
// Pre-condicao: nenhuma
// Pos-condicao: retorna atual condicao do cabecalho
cabecalho* ler_cabecalho(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, f);

    return cab;
}

// Funcao para escrever cabecalho
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void escrever_cabecalho(FILE* f, cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, f);
}

// Funcao para ler no
// Pre-condicao: nenhuma
// Pos-condicao: retorna no na posicao escolhida
no* ler_no(FILE* f, int pos)
{
    no* x = malloc(sizeof(no));

    fseek(f, sizeof(cabecalho)+sizeof(no)*pos, SEEK_SET);
    fread(x, sizeof(no), 1, f);

    return x;
}

// Funcao para escrever no
// Pre-condicao: nenhuma
// Pos-condicao: escreve no em determinada posicao
void escrever_no(FILE* f, no* x, int pos)
{
    fseek(f, sizeof(cabecalho)+sizeof(no)*pos, SEEK_SET);
    fwrite(x, sizeof(no), 1, f);
}

// Funcao para enfilerar valor
// Pre-condicao: cabecalho inicializado
// Pos-condicao: insere elemento ao final da fila
void enfilerar(FILE* f, int info)
{
    cabecalho* cab = ler_cabecalho(f);
    no novo;
    novo.info = info;
    novo.prox = -1;

    if(cab->pos_cabeca == -1){
        cab->pos_cabeca = cab->pos_ultimo = cab->pos_topo;
        escrever_no(f, &novo, cab->pos_topo);
        cab->pos_topo++;
    }
    else{
        if(cab->pos_livre == -1){
            no* aux = ler_no(f, cab->pos_ultimo);
            aux->prox = cab->pos_topo;

            escrever_no(f, aux, cab->pos_ultimo);
            cab->pos_ultimo = cab->pos_topo;

            escrever_no(f, &novo, cab->pos_topo);
            cab->pos_topo++;
            free(aux);
        }
        else{
            no* aux = ler_no(f, cab->pos_livre);
            no* ultimo = ler_no(f, cab->pos_ultimo);
            int pos_livre = cab->pos_livre;

            cab->pos_livre = aux->prox;
            ultimo->prox = pos_livre;

            escrever_no(f, ultimo, cab->pos_ultimo);
            cab->pos_ultimo = pos_livre;

            escrever_no(f, &novo, pos_livre);
            free(aux);
            free(ultimo);
        }
    }
    escrever_cabecalho(f, cab);
}

// Funcao para defilerar valor
// Pre-condicao: cabecalho inicializado
// Pos-condicao: remove elemento da cabeca
void defilerar(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);

    if(cab->pos_cabeca == -1){
        free(cab);
        return;
    }

    else{
        no* aux = ler_no(f, cab->pos_cabeca);
        int livre = cab->pos_livre;
        int cabeca = cab->pos_cabeca;

        cab->pos_livre = cabeca;
        cab->pos_cabeca = aux->prox;
        aux->prox = livre;

        if(cab->pos_cabeca == -1){
            cab->pos_topo = 0;
            cab->pos_livre = -1;
            cab->pos_ultimo = -1;
        }

        escrever_no(f, aux, cabeca);

        free(aux);
    }
    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para imprimir elementos em fila
// Pre-condicao: nenhuma
// Pos-condicao: imprime elementos na tela
void imprimir_fila(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_cabeca;
    no* aux;

    while(pos != cab->pos_ultimo){
        aux = ler_no(f, pos);

        printf("%d ", aux->info);

        pos = aux->prox;
        free(aux);
    }
    if(pos != -1){
        aux = ler_no(f, pos);

        printf("%d\n", aux->info);
    }

    free(cab);
}

// Funcao para imprimir posicoes livres
// Pre-condicao: nenhuma
// Pos-condicao: imprime posicoes livres
void imprimir_pos_livre(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos_livre = cab->pos_livre;

    while(pos_livre != -1){
        no* aux = ler_no(f, pos_livre);

        printf("Posicao: %d\n", pos_livre);

        pos_livre = aux->prox;
        free(aux);
    }
    free(cab);
}
