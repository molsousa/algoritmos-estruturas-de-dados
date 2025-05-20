#ifndef LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED
#define LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED

// Definicao de tipo para manipulacao de lista
typedef struct lista Elem;
// Definicao de Lista Duplamente Encadeada
typedef struct lista* Lista;

// Funcao para criar lista
// Pre-condicao: nenhum
// Pos-condicao: retorna uma lista criada
Lista* criar_lista();

// Funcao para liberar lista
// Pre-condicao: lista criada
// Pos-condicao: retorna nulo para ponteiro do tipo Lista
Lista* liberar_lista(Lista* l);

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento em cauda
void inserir_elemento(Lista* l, int info);

// Funcao para inserir elemento ordenado
// Pre-condicao: lista criada
// Pos-condicao: insere elemento de forma ordenada
void inserir_elemento_ordenado(Lista* l, int info);

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove elemeento da lista
void remover_elemento(Lista* l, int info);

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime a lista na tela
void imprimir_lista(Lista* l);

// Funcao para imprimir a lista ida e volta
// Pre-condicao: lista criada
// Pos-condicao: imprime a lista na tela
void imprimir_ida_volta(Lista* l);

#endif // LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED
