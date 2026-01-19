#ifndef LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED
#define LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED

// Definicao de Lista Duplamente Encadeada
typedef struct lista* Lista;

// Funcao para criar lista
// Pre-condicao: nenhum
// Pos-condicao: retorna uma lista criada
Lista* criar_lista();

// Testa se um no eh vazio
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se vazio
int vazia(struct lista* l);

// Funcao auxiliar para liberar cada elemento
// Pre-condicao: nenhuma
// Pos-condicao: destroi elementos da lista
void liberar_lista_cauda(struct lista* l);

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

// Funcao auxiliar para imprimir a volta
// Pre-condicao: lista criada
// Pos-condicao: imprime a rotina de ida
void rotina_ida(struct lista* l);

// Funcao auxiliar para imprimir a volta
// Pre-condicao: lista criada
// Pos-condicao: imprime a rotina de volta
void rotina_volta(struct lista* l);

// Funcao para imprimir a lista ida e volta
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void imprimir_ida_volta(Lista* l);

#endif // LISTA_DUPLAMENTE_ENCADEADA_H_INCLUDED
