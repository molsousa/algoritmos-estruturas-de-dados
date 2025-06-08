#include <stdlib.h>
#include "arvore.h"

// Estrutura para no
struct no{
    int info;
    int esq;
    int dir;
};

// Estrutura para cabecalho
struct cabecalho{
    int raiz;
    int no_livre;
};

// Funcao para criar uma arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: retorna um arquivo binario inicializado
FILE* criar_arvore()
{
    FILE* f = fopen("arvore.bin", "w+b");

    Cabecalho c;
    c.raiz = -1;
    c.no_livre = -1;
    escrever_cabecalho(f, c);

    return f;
}

// Funcao para ler cabecalho
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o cabecalho do arquivo
Cabecalho* ler_cabecalho(FILE* f)
{
    Cabecalho *c = malloc(sizeof(Cabecalho));
    fseek(f, 0, SEEK_SET);
    fread(c, sizeof(Cabecalho), 1, f);
    return c;
}

// Funcao para escrever no cabecalho
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: escreve no cabecalho
void escrever_cabecalho(FILE* f, Cabecalho c)
{
    fseek(f, 0, SEEK_SET);
    fwrite(&c, sizeof(Cabecalho), 1, f);
}

// Funcao para ler no
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna arquivo lido em arquivo binario
No ler_no(FILE* f, int dado)
{
    No no;
    fseek(f, dado, SEEK_SET);
    fread(&no, sizeof(No), 1, f);
    return no;
}

// Funcao para escrever no
// Pre-condicao: arquivo inicializado
// Pos-condicao: escreve no arquivo o no
void escrever_no(FILE* f, No no, int dado)
{
    fseek(f, dado, SEEK_SET);
    fwrite(&no, sizeof(No), 1, f);
}

// Funcao auxiliar para inserir na arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna sucesso em inserir
int inserir(FILE* f, Cabecalho* c, int atual, int info)
{
    if(atual == -1){
        int novo_dado = alocar_espaco(f, c);
        No no;
        no.info = info;
        no.esq = -1;
        no.dir = -1;
        escrever_no(f, no, novo_dado);
        return novo_dado;
    }

    No no_atual = ler_no(f, atual);

    if(info < no_atual.info)
        no_atual.esq = inserir(f, c, no_atual.esq, info);
    else if(info > no_atual.info)
        no_atual.dir = inserir(f, c, no_atual.dir, info);

    escrever_no(f, no_atual, atual);
    return atual;
}

// Funcao para inserir elemento da arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: nenhuma
void inserir_no(FILE* f, Cabecalho* c, int info)
{
    c->raiz = inserir(f, c, c->raiz, info);
    escrever_cabecalho(f, *c);
}

// Funcao auxiliar para remover elemento
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna o registro se removido ou -1 se nao encontrado
int remover(FILE* f, Cabecalho* c, int atual, int info)
{
    if(atual == -1)
        return -1;

    No no_atual = ler_no(f, atual);

    if(info < no_atual.info){
        no_atual.esq = remover(f, c, no_atual.esq, info);
        escrever_no(f, no_atual, atual);
    }
    else if(info > no_atual.info){
        no_atual.dir = remover(f, c, no_atual.dir, info);
        escrever_no(f, no_atual, atual);
    }
    else{
        if(no_atual.esq == -1){
            int temp = no_atual.dir;
            espaco_livre_no(f, c, atual);
            return temp;
        }
        else if(no_atual. dir == -1){
            int temp = no_atual.esq;
            espaco_livre_no(f, c, atual);
            return temp;
        }
        else{
            int sucessor = procurar_no_maior(f, no_atual.esq);
            No no_sucessor = ler_no(f, sucessor);

            no_atual.info = no_sucessor.info;

            no_atual.esq = remover(f, c, no_atual.esq, no_sucessor.info);
            escrever_no(f, no_atual, atual);
        }
    }
    return atual;
}

// Funcao para remover elemento da arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: nenhuma
void remover_no(FILE* f, Cabecalho* c, int info)
{
    c->raiz = remover(f, c, c->raiz, info);
    escrever_cabecalho(f, *c);
}

// Funcao para alocar espaco em arquivo binario
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna novo espaco inicializado
int alocar_espaco(FILE* f, Cabecalho* c)
{
    int espaco_novo;

    if(c->no_livre != -1){
        espaco_novo = c->no_livre;
        No no_livre = ler_no(f, espaco_novo);
        c->no_livre = no_livre.esq;
        escrever_cabecalho(f, *c);
    }
    else{
        fseek(f, 0, SEEK_END);
        espaco_novo = (int) ftell(f);
    }

    return espaco_novo;
}

// Funcao para escrever em novo espaco
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: libera novo espaco em arquivo
void espaco_livre_no(FILE* f, Cabecalho* c, int dado)
{
    No dado_livre;

    dado_livre.info = -1;
    dado_livre.esq = c->no_livre;
    dado_livre.dir = -1;
    escrever_no(f, dado_livre, dado);

    c->no_livre = dado;
    escrever_cabecalho(f, *c);
}

// Funcao para buscar o maior valor da subarvore esquerda
// Pre-condicao: enviado o valor da esquerda
// Pos-condicao: retorna a posicao do maior valor da subarvore esquerda
int procurar_no_maior(FILE* f, int atual)
{
    if(atual == -1)
        return -1;

    No no_atual = ler_no(f, atual);

    while(no_atual.dir != -1){
        atual = no_atual.dir;
        no_atual = ler_no(f, atual);
    }

    return atual;
}

// Funcao auxiliar para imprimir em preOrder
// Pre-condicao: arquivo inicializado
// Pos-condicao: imprime na tela a arvore pre ordenada
void imprimir_preOrder(FILE* f, int atual)
{
    if(atual != -1){
        No no_atual = ler_no(f, atual);
        printf("%d\n", no_atual.info);

        imprimir_preOrder(f, no_atual.esq);
        imprimir_preOrder(f, no_atual.dir);
    }
}

// Funcao para imprimir arvore
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: nenhuma
void imprimir_arvore(FILE* f, Cabecalho* c)
{
    imprimir_preOrder(f, c->raiz);
}

// Funcao auxiliar para buscar informacao
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o valor do registro da informacao
int buscar_no(FILE* f, int atual, int info)
{
    if(atual == -1)
        return -1;

    No no_atual = ler_no(f, atual);

    if(info == no_atual.info)
        return atual;

    else if(info < no_atual.info)
        return buscar_no(f, no_atual.esq, info);

    else
        return buscar_no(f, no_atual.dir, info);

    return -1;
}

// Funcao para buscar informacao
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: retorna o valor do registro da informacao
int buscar_arvore(FILE* f, Cabecalho* c, int info)
{
    return buscar_no(f, c->raiz, info);
}


