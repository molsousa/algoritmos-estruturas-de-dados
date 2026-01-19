#include <stdio.h>
#include <stdlib.h>
#include "../include/rway.h"

// Estrutura para no RWay
struct noTrie{
    struct noTrie* filho[TAM_ALFABETO];
    int valor;
};

// Estrutura para arvore TRIE
struct trie{
    Trie raiz;
};

// Funcao para criar arvore TRIE
// Pre-condicao: nenhuma
// Pos-condicao: cria arvore com raiz alocada
arvTrie* criar_arvore()
{
    arvTrie* r = malloc(sizeof(arvTrie));
    int i;

    r->raiz = malloc(sizeof(struct noTrie));
    r->raiz->valor = -1;

    for(i = 0; i < TAM_ALFABETO; i++)
        r->raiz->filho[i] = NULL;

    return r;
}

// Funcao para verificar se um no eh vazio
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se vazio
int vazia(Trie r)
{
    return (r == NULL);
}

// Funcao para inserir em arvore TRIE
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void inserir(arvTrie* r, char* str, int valor)
{
    r->raiz = inserir_aux(r->raiz, str, valor);
}

// Funcao auxiliar para insercao
// Pre-condicao: nenhuma
// Pos-condicao: encadeia os nos compativeis com a string desejada
Trie inserir_aux(Trie raiz, char* str, int valor)
{
    if(vazia(raiz)){
        int i;
        raiz = malloc(sizeof(struct noTrie));
        raiz->valor = -1;

        for(i = 0; i < TAM_ALFABETO; i++)
            raiz->filho[i] = NULL;
    }
    if(*str == '\0'){
        raiz->valor = valor;
        return raiz;
    }

    raiz->filho[*str - ASCII_BASE] = inserir_aux(raiz->filho[*str - ASCII_BASE], str+1, valor);

    return raiz;
}

// Funcao para remover string
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void remover(arvTrie* r, char* str)
{
    if(buscar(r, str) == -1)
        return;

    r->raiz = remover_aux(r->raiz, str);
}

// Funcao para remover string
// Pre-condicao: nenhuma
// Pos-condicao: desencadeia e libera os nos que nao tiverem filhos
Trie remover_aux(Trie raiz, char* str)
{
    if(*str == '\0'){
        if(raiz->valor != -1)
            raiz->valor = -1;

        if(!tem_filho(raiz)){
            free(raiz);
            return NULL;
        }
    }
    else
        raiz->filho[*str - ASCII_BASE] = remover_aux(raiz->filho[*str - ASCII_BASE], str+1);

    if(raiz->valor == -1 && !tem_filho(raiz)){
        free(raiz);
        return NULL;
    }

    return raiz;
}

// Verifica se um no tem filho
// Pre-condicao: nenhuma
// Pos-condicao: retorna verdadeiro caso tenha
bool tem_filho(Trie raiz)
{
    if(vazia(raiz))
        return false;

    int i;

    for(i = 0; i < TAM_ALFABETO; i++)
        if(raiz->filho[i] != NULL)
            return true;

    return false;
}

// Funcao para buscar string
// Pre-condicao: arvore criada
// Pos-condicao: retorna o valor da chave
int buscar(arvTrie* r, char* str)
{
    return buscar_aux(r->raiz, str);
}

// Funcao auxiliar para busca
// Pre-condicao: nenhuma
// Pos-condicao: retorna o valor da chave
int buscar_aux(Trie raiz, char* str)
{
    int i;

    for(i = 0; i < TAM_ALFABETO; i++){
        if(raiz->filho[i] != NULL && *str == (ASCII_BASE + i))
            return buscar_aux(raiz->filho[i], str+1);

        if(*str == '\0'){
            if(raiz->valor != -1)
                return raiz->valor;

            else
                return -1;
        }
    }

    return -1;
}

// Funcao para imprimir dicionario
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir(arvTrie* r)
{
    char* buffer = calloc(1000, sizeof(char));

    imprimir_aux(r->raiz, buffer, 0);

    free(buffer);
}

// Funcao auxiliar para impressao
// Pre-condicao: nenhuma
// Pos-condicao: imprime todos os nomes na tela com seu respectivo valor
void imprimir_aux(Trie raiz, char* buffer, int n)
{
    int i;
    for(i = 0; i < TAM_ALFABETO; i++){
        if(raiz->filho[i] != NULL){
            *(buffer+n) = i+ASCII_BASE;
            imprimir_aux(raiz->filho[i], buffer, n+1);
        }
    }
    if(raiz->valor != -1){
        *(buffer+n) = '\0';
        printf("%-20s | %d\n", buffer, raiz->valor);
    }
}
