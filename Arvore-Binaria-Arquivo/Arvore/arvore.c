#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Estrutura para cabecalho
struct cabecalho{
    int pos_raiz;
    int pos_topo;
    int pos_livre;
};

// Estrutura para nos da arvore
struct no_arv{
    int info;
    int esq;
    int dir;
};

// Funcao para escrever no cabecalho
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: escreve no cabecalho
void escrever_cabecalho(FILE* f, Cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(Cabecalho), 1, f);
}

// Funcao para ler cabecalho
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o cabecalho do arquivo
Cabecalho* ler_cabecalho(FILE* f)
{
    Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));
    if(!cab)
        exit(1);

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(Cabecalho), 1, f);

    return cab;
}

// Funcao para escrever no
// Pre-condicao: arquivo inicializado
// Pos-condicao: escreve no arquivo o no
void escrever_no(FILE* f, No* no, int pos)
{
    fseek(f, sizeof(Cabecalho)+pos*sizeof(No), SEEK_SET);
    fwrite(no, sizeof(No), 1, f);
}

// Funcao para ler no
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna ponteiro para no
No* ler_no(FILE* f, int pos)
{
    No* no = (No*) malloc(sizeof(No));
    if(!no)
        exit(1);

    fseek(f, sizeof(Cabecalho)+pos*sizeof(No), SEEK_SET);
    fread(no, sizeof(No), 1, f);

    return no;
}

// Funcao para criar uma arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: retorna o cabecalho inicializado
void criar_arvore(FILE* f)
{
    Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para inserir na arvore
// Pre-condicao: arquivo inicializado
// Pos-condicao: nenhuma
void inserir_no(FILE* f, int info)
{
    Cabecalho* cab = ler_cabecalho(f);
    int pos;
    No novo;

    novo.info = info;
    novo.esq = -1;
    novo.dir = -1;

    if(cab->pos_livre != -1){
        pos = cab->pos_livre;
        No* livre = ler_no(f, pos);
        cab->pos_livre = livre->esq;
        free(livre);
    }
    else
        pos = cab->pos_topo++;

    if(cab->pos_raiz == -1)
        cab->pos_raiz = pos;

    else{
        int pai_pos = cab->pos_raiz;
        No* pai = ler_no(f, pai_pos);

        while(1){
            if(info < pai->info){
                if(pai->esq == -1){
                    pai->esq = pos;
                    escrever_no(f, pai, pai_pos);
                    free(pai);
                    break;
                }
                pai_pos = pai->esq;
            }
            else{
                if(pai->dir == -1){
                    pai->dir = pos;
                    escrever_no(f, pai, pai_pos);
                    free(pai);
                    break;
                }
                pai_pos = pai->dir;
            }
            free(pai);
            pai = ler_no(f, pai_pos);
        }
    }
    escrever_no(f, &novo, pos);
    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao para remover elemento da arvore
// Pre-condicao: cabecalho inicializado
// Pos-condicao: nenhuma
void remover_no(FILE* f, int info)
{
    Cabecalho* cab = ler_cabecalho(f);
    cab->pos_raiz = remover(f, cab->pos_raiz, info, cab);
    escrever_cabecalho(f, cab);
    free(cab);
}

// Funcao auxiliar para remover elemento
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna o registro se removido ou -1 se nao encontrado
int remover(FILE* f, int pos, int info, Cabecalho* cab)
{
    if(pos == -1)
        return -1;

    No* no = ler_no(f, pos);

    if(info < no->info)
        no->esq = remover(f, no->esq, info, cab);

    else if(info > no->info)
        no->dir = remover(f, no->dir, info, cab);

    else{
        int temp;

        if(no->esq == -1){
            temp = no->dir;
            no->dir = cab->pos_livre;
            cab->pos_livre = pos;
            escrever_no(f, no, pos);
            free(no);
            return temp;
        }
        else if(no->dir == -1){
            temp = no->esq;
            no->esq = cab->pos_livre;
            cab->pos_livre = pos;
            escrever_no(f, no, pos);
            free(no);
            return temp;
        }
        else{
            int maior_pos = maximo(f, no->esq);
            No* maior = ler_no(f, maior_pos);
            no->info = maior->info;
            no->esq = remover(f, no->esq, maior->info, cab);
            escrever_no(f, no, pos);
            free(maior);
        }
    }
    escrever_no(f, no, pos);
    free(no);
    return pos;
}

// Funcao para encontrar o maximo
// Pre-condicao: nenhuma
// Pos-condicao: retorna a posicao do maior valor da subarvore da esquerda
int maximo(FILE* f, int pos)
{
    No* no = ler_no(f, pos);
    while(no->dir != -1){
        pos = no->dir;
        free(no);
        no = ler_no(f, pos);
    }
    free(no);
    return pos;
}

// Funcao auxiliar para imprimir em preOrder
// Pre-condicao: arquivo inicializado
// Pos-condicao: imprime na tela a arvore pre ordenada
void imprimir_preOrder(FILE* f, int pos)
{
    if(pos == -1)
        return;

    No* no = ler_no(f, pos);

    printf("%d\n", no->info);

    imprimir_preOrder(f, no->esq);
    imprimir_preOrder(f, no->dir);

    free(no);
}

// Funcao para imprimir em preOrder
// Pre-condicao: arquivo inicializado
// Pos-condicao: nenhuma
void imprimir_arvore(FILE* f)
{
    Cabecalho* cab = ler_cabecalho(f);
    imprimir_preOrder(f, cab->pos_raiz);
    free(cab);
}
