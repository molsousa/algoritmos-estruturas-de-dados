#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Estrutura para cabecalho
struct cabec{
    int pos_livre;
    int pos_topo;
    int pos_cabeca;
};

// Estrutura para lista encadeada
struct lista{
    int info;
    int prox;
};

// Funcao para criar nova lista
// Pre-condicao: arquivo inicializado
// Pos-condicao: cria novo cabecalho no arquivo
void criar_lista(FILE* f)
{
    Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));

    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para escrever no cabecalho
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void escrever_cabecalho(FILE* f, Cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(Cabecalho), 1, f);
}

// Funcao para retornar o cabecalho
// Pre-condicao: lista criada
// Pos-condicao: retorna informacoes do cabecalho
Cabecalho* ler_cabecalho(FILE* f)
{
    Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(Cabecalho), 1, f);

    return cab;
}

// Funcao para escrever No
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void escrever_no(FILE* f, Lista* l, int pos)
{
    fseek(f, sizeof(Cabecalho)+pos*sizeof(Lista), SEEK_SET);
    fwrite(l, sizeof(Lista), 1, f);
}

// Funcao para encontrar No
// Pre-condicao: lista criada
// Pos-condicao: retorna informacoes do no buscado
Lista* ler_no(FILE* f, int pos)
{
    Lista* atual = (Lista*) malloc(sizeof(Lista));

    fseek(f, sizeof(Cabecalho)+pos*sizeof(Lista), SEEK_SET);
    fread(atual, sizeof(Lista), 1, f);

    return atual;
}

// Funcao para inserir elemento na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void inserir_elemento(FILE* f, int info)
{
    Cabecalho* cab = ler_cabecalho(f);
    Lista novo;

    novo.info = info;
    novo.prox = cab->pos_cabeca;

    if(cab->pos_livre == -1){
        escrever_no(f, &novo, cab->pos_topo);
        cab->pos_cabeca = cab->pos_topo;
        cab->pos_topo++;
    }
    else{
        Lista* aux = ler_no(f, cab->pos_livre);
        escrever_no(f, &novo, cab->pos_livre);

        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->prox;
        free(aux);
    }

    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para remover elemento na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void remover_elemento(FILE* f, int info)
{
    Cabecalho* cab = ler_cabecalho(f);
    int pos_aux = cab->pos_cabeca;
    int pos_ant = cab->pos_cabeca;
    Lista* aux = NULL;

    while(pos_aux != -1 && ((aux = ler_no(f, pos_aux))) != NULL && aux->info != info){
        pos_ant = pos_aux;
        pos_aux = aux->prox;
        free(aux);
        aux = NULL;
    }

    if(pos_aux == -1){
        free(cab);
        return;
    }

    if(pos_ant == pos_aux)
        cab->pos_cabeca = aux->prox;

    else{
        Lista* ant = ler_no(f, pos_ant);
        ant->prox = aux->prox;
        escrever_no(f, ant, pos_ant);
        free(ant);
    }
    aux->prox = cab->pos_livre;
    cab->pos_livre = pos_aux;
    escrever_no(f, aux, pos_aux);
    escrever_cabecalho(f, cab);

    free(aux);
    free(cab);
}

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime a lista em ordem de insercao
void imprimir_lista(FILE* f)
{
    Cabecalho* cab = ler_cabecalho(f);
    Lista* aux;

    while(cab->pos_cabeca != -1){
        aux = ler_no(f, cab->pos_cabeca);

        printf("|%d|->", aux->info);

        cab->pos_cabeca = aux->prox;
        free(aux);
    }
    printf("NULL\n");
}
