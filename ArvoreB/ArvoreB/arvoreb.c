#include <stdio.h>
#include <stdlib.h>
#include "arvoreb.h"

// Estrutura para arvore-B
struct no{
    int num_chaves;
    int chave[ORDEM-1];
    struct no* filho[ORDEM];
};

// Funcao para criar arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro ArvoreB
ArvoreB criar_arvore()
{
    return NULL;
}

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(ArvoreB raiz)
{
    return (raiz == NULL);
}

// Funcao que separa nos
// Pre-condicao: arvore criada
// Pos-condicao: retorna o no separado
ArvoreB split(ArvoreB no, int* m)
{
    ArvoreB y = malloc(sizeof(struct no));
    int q = no->num_chaves/2;
    y->num_chaves = no->num_chaves - q - 1;
    no->num_chaves = q;
    *m = no->chave[q];

    int i = 0;
    y->filho[0] = no->filho[q+1];

    while(i < y->num_chaves){
        y->chave[i] = no->chave[q+i+1];
        y->filho[i+1] = no->filho[q+i+2];
        i++;
    }
    return y;
}

// Funcao para buscar posicao de um elemento
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se encontrado no
int busca_pos(ArvoreB raiz, int info, int* pos)
{
    for(*pos = 0; *pos < raiz->num_chaves; ++*pos)
        if(info == raiz->chave[(*pos)])
            return 1;
        else if(info < raiz->chave[(*pos)])
            break;

    return 0;
}

// Funcao para verificar se um no eh folha
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se folha
int eh_folha(ArvoreB raiz)
{
    return (raiz->filho[0] == NULL);
}

// Funcao para verificar se houve overflow
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se um no estiver cheio
int overflow(ArvoreB raiz)
{
    return (raiz->num_chaves == ORDEM);
}

// Funcao para adicionar uma chave com um filho a um no
// Pre-condicao: nenhuma
// Pos-condicao: adiciona uma chave com um filho a um no e desloca os demais a direita se necessario
void adicionar_direita(ArvoreB raiz, int pos, int k, ArvoreB p)
{
    register int i;

    for(i = raiz->num_chaves; i > pos; i--){
        raiz->chave[i] = raiz->chave[i-1];
        raiz->filho[i+1] = raiz->filho[i];
    }

    raiz->chave[pos] = k;
    raiz->filho[pos+1] = p;
    raiz->num_chaves++;
}

// Funcao para inserir em arvore-B
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento na arvore
ArvoreB inserir(ArvoreB raiz, int info)
{
    if(vazia(raiz)){
        int i;
        raiz = malloc(sizeof(struct no));
        raiz->chave[0] = info;
        for(i = 0; i < ORDEM; i++)
            raiz->filho[i] = NULL;
        raiz->num_chaves = 1;
    }

    else{
        inserir_aux(raiz, info);
        if(overflow(raiz)){
            int m;
            int i;
            ArvoreB x = split(raiz, &m);
            ArvoreB nova_raiz = malloc(sizeof(struct no));

            nova_raiz->chave[0] = m;
            nova_raiz->filho[0] = raiz;
            nova_raiz->filho[1] = x;

            for(i = (((int) ORDEM/2)+1); i < ORDEM; i++)
                raiz->filho[i] = NULL;

            nova_raiz->num_chaves = 1;
            return nova_raiz;
        }
    }
    return raiz;
}

// Funcao auxiliar para inserir
// Pre-condicao: nenhuma
// Pos-condicao: utiliza as funcoes auxiliares para inserir determinado elemento
void inserir_aux(ArvoreB raiz, int info)
{
    int pos;

    if(!busca_pos(raiz, info, &pos)){
        if(eh_folha(raiz))
            adicionar_direita(raiz, pos, info, NULL);
        else{
            inserir_aux(raiz->filho[pos], info);
            if(overflow(raiz->filho[pos])){
                int m;
                ArvoreB aux = split(raiz->filho[pos], &m);
                adicionar_direita(raiz, pos, m, aux);
            }
        }
    }
}

ArvoreB remover(ArvoreB raiz, int info)
{
    if(vazia(raiz))
        return raiz;

    if(eh_folha(raiz)){
        int i = 0;
        while(i < raiz->num_chaves && raiz->chave[i] != info)
            i++;

        if(raiz->chave[i] != info)
            return raiz;

        else{
            int j;

            for(j = i; j < raiz->num_chaves-1; j++)
                raiz->chave[j] = raiz->chave[j+1];

            raiz->num_chaves--;

            if(raiz->num_chaves == 0)
                return NULL;
        }
    }
    return raiz;
}

// Funcao para imprimir em preOrdem
// Pre-condicao: arvore criada
// Pos-condicao: imprime os elementos da arvore em pre-ordenado
void preOrdem(ArvoreB raiz)
{
    if(raiz == NULL)
        return;

    int i;
    for(i = 0; i < raiz->num_chaves; i++){
        printf("%d ", raiz->chave[i]);
        preOrdem(raiz->filho[i]);
    }
    preOrdem(raiz->filho[i]);
}

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: imprime todos os nos por niveis
void imprimir_por_niveis(ArvoreB raiz)
{
    if(raiz == NULL)
        return;

    int inicio, fim, i, j;
    ArvoreB* fila = malloc(1000 * sizeof(ArvoreB));

    inicio = fim = 0;
    fila[fim++] = raiz;

    while(inicio < fim){
        int nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            ArvoreB atual = fila[inicio++];
            printf("[");

            for(j = 0; j < atual->num_chaves; j++){
                printf("%d", atual->chave[j]);
                if(j < atual->num_chaves - 1)
                    printf(", ");
            }
            printf("] ");
            for(j = 0; j <= atual->num_chaves; j++)
                if(atual->filho[j] != NULL)
                    fila[fim++] = atual->filho[j];
        }
        printf("\n");
    }

    free(fila);
}
