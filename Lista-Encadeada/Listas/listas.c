#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

// Estrutura para lista encadeada
struct lista{
    int info;
    struct lista* prox;
};

// Funcao para criar lista
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro do tipo Lista
Lista* criar_lista()
{
    return NULL;
}

// Funcao para liberar lista
// Pre-condicao: lista valida
// Pos-condicao: libera todos os elementos da lista
void liberar_lista(Lista* l)
{
    if(vazia(l))
        return;

    liberar_lista(l->prox);
    free(l);
}

// Funcao para verificar se uma lista eh vazia
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se vazia
int vazia(Lista* l)
{
    return (l == NULL);
}

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento na cabeca
Lista* inserir_elemento(Lista* l, int info)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));

    novo->info = info;
    novo->prox = l;

    return novo;
}

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento ao final da lista
Lista* inserir_elemento_cauda(Lista* l, int info)
{
    if(vazia(l)){
        Lista* novo = (Lista*) malloc(sizeof(Lista));
        novo->info = info;
        novo->prox = NULL;
        return novo;
    }
    l->prox = inserir_elemento_cauda(l->prox, info);

    return l;
}

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento ordenado
Lista* inserir_elemento_ordenado(Lista* l, int info)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = info;

    if(vazia(l)){
        novo->prox = l;
        return novo;
    }
    else{
        Lista* aux = l;
        Lista* anterior = l;

        while(aux->prox != NULL && aux->info <= info){
            anterior = aux;
            aux = aux->prox;
        }

        if(anterior == aux && aux->info > info){
            novo->prox = aux;
            return novo;
        }
        else{
            anterior->prox = novo;
            novo->prox = aux;
        }
    }
    return l;
}

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove a primeira ocorrencia do elemento buscado
Lista* remover_elemento(Lista* l, int info)
{
    if(vazia(l))
        return l;

    if(l->info == info){
        Lista* aux = l;
        l = l->prox;
        free(aux);
        return l;
    }

    l->prox = remover_elemento(l->prox, info);

    return l;
}

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove a primeira ocorrencia do elemento buscado
Lista* remover_elemento_iterativo(Lista* l, int info)
{
    Lista* aux = l;
    Lista* anterior = l;

    while(aux != NULL && aux->info != info){
        anterior = aux;
        aux = aux->prox;
    }

    if(aux == NULL)
        return l;

    else if(aux == anterior)
        l = aux->prox;

    else
        anterior->prox = aux->prox;

    free(aux);
    return l;
}

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove todas as ocorrencias do elemento buscado
Lista* remover_elemento_recorrencias(Lista* l, int info)
{
    if(vazia(l))
        return l;

    l->prox = remover_elemento_recorrencias(l->prox, info);

    l = remover_elemento(l, info);

    return l;
}

// Funcao para inverter lista
// Pre-condicao: lista criada
// Pos-condicao: retorna uma nova lista invertida
Lista* inverter_lista(Lista* l)
{
    if(vazia(l))
        return l;

    Lista* novo = criar_lista();

    while(l != NULL){
        novo = inserir_elemento(novo, l->info);
        l = l->prox;
    }

    return novo;
}

// Funcao para concatenar listas
// Pre-condicao: listas criadas
// Pos-condicao: retorna uma nova lista concatenada
Lista* concatenar_lista(Lista* l1, Lista* l2)
{
    Lista* novo = criar_lista();

    while(l1 != NULL){
        novo = inserir_elemento_cauda(novo, l1->info);
        l1 = l1->prox;
    }
    while(l2 != NULL){
        novo = inserir_elemento_cauda(novo, l2->info);
        l2 = l2->prox;
    }

    return novo;
}

// Funcao para intercalar listas
// Pre-condicao: listas criadas
// Pos-condicao: retorna uma nova lista intercalada
Lista* intercalar_lista(Lista* l1, Lista* l2)
{
    Lista* novo = criar_lista();

    while(l1 != NULL || l2 != NULL){
        if(l1 != NULL && l2 != NULL){
            novo = inserir_elemento_cauda(novo, l1->info);
            novo = inserir_elemento_cauda(novo, l2->info);
            l1 = l1->prox;
            l2 = l2->prox;
        }
        else if(l2 == NULL){
            novo = inserir_elemento_cauda(novo, l1->info);
            l1 = l1->prox;
        }
        else if(l1 == NULL){
            novo = inserir_elemento_cauda(novo, l2->info);
            l2 = l2->prox;
        }
    }
    return novo;
}

// Funcao para concatenar listas
// Pre-condicao: listas criadas
// Pos-condicao: concatena a lista 2 na lista 1
Lista* append(Lista* l1, Lista* l2)
{
    Lista* aux = l1;

    if(l1 == NULL)
        return l2;

    while(aux->prox != NULL)
        aux = aux->prox;

    aux->prox = l2;

    return l1;
}

// Funcao para contar ocorrencias
// Pre-condicao: lista criada
// Pos-condicao: retorna numero de ocorrencias de determinado elemento
int contar_ocorrencias(Lista* l, int info)
{
    if(l == NULL)
        return 0;

    if(l->info == info)
        return 1+contar_ocorrencias(l->prox, info);

    return contar_ocorrencias(l->prox, info);
}

// Funcao para inverter lista
// Pre-condicao: lista criada
// Pos-condicao: retorna a lista original invertida
Lista* inverter_lista_original(Lista* l)
{
    Lista* novo = criar_lista();
    Lista* aux = l;

    while(l != NULL){
        novo = inserir_elemento(novo, l->info);
        l = l->prox;
    }

    liberar_lista(aux);

    return novo;
}

// Funcao para eliminar elementos repetidos
// Pre-condicao: lista criada
// Pos-condicao: elimina todas as ocorrencias repetidas
Lista* eliminar_repetidos(Lista* l)
{
    if(l == NULL || l->prox == NULL)
        return l;

    Lista* aux = l;

    while(aux->prox != NULL){
        if(aux->prox->info == l->info){
            Lista* temp = aux->prox;
            aux->prox = temp->prox;
            free(temp);
        }
        else
            aux = aux->prox;
    }

    l->prox = eliminar_repetidos(l->prox);

    return l;
}

// Funcao para contar elementos distintos
// Pre-condicao: lista criada
// Pos-condicao: retorna o numero total de elementos distintos
int contar_distintos(Lista* l)
{
    if(l == NULL)
        return 0;

    int contador = !valor_existe(l->prox, l->info);

    return contador + contar_distintos(l->prox);
}

// Funcao para verificar se um valor existe na lista
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se o valor existe na lista
int valor_existe(Lista* l, int info)
{
    if(l == NULL)
        return 0;

    if(l->info == info)
        return 1;

    return valor_existe(l->prox, info);
}

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime na tela os elementos inseridos
void imprimir_lista(Lista* l)
{
    if(vazia(l)){
        printf("NULL\n");
        return;
    }

    printf("|%d|->", l->info);
    imprimir_lista(l->prox);
}

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime na tela os elementos inseridos de forma invertida
void imprimir_lista_invertido(Lista* l)
{
    if(vazia(l)){
        printf("NULL");
        return;
    }

    imprimir_lista_invertido(l->prox);
    printf("<-|%d|", l->info);
}
