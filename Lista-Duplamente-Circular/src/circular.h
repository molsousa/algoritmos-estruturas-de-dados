#ifndef LISTA_ENCADEADA_CIRCULAR_H_
#define LISTA_ENCADEADA_CIRCULAR_H_

// Definicao de tipo para lista circular
typedef struct lista* Lista;
// Definicao de tipo para manipular lista circular
typedef struct lista Elem;

// Funcao para criar lista encadeada
// Pre-condicao: ponteiro do tipo lista criado
// Pos-condicao: lista criada
Lista* criar_lista();

// Funcao para liberar lista circular
// Pre-condicao: lista criada
// Pos-condicao: retorna nulo para ponteiro void
void* liberar_lista(Lista* l);

// Funcao para inserir elemento na lista circular
// Pre-condicao: lista criada
// Pos-condicao: adiciona elemento anterior ao primeiro elemento
void inserir_elemento(Lista* l, int info);

// Funcao para remover elemento da lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void remover_elemento(Lista* l, int info);

// Funcao para buscar elemento na lista circular
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se encontrado, 0 se nao
int buscar_elemento(Lista* l, int info);

// Funcao para imprimir lista circular
// Pre-condicao: lista criada
// Pos-condicao: imprime a ida e a volta
void imprimir_lista(Lista* l);

#endif // LISTA_ENCADEADA_CIRCULAR_H_
