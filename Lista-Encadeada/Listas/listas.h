#ifndef LISTAS_H_
#define LISTAS_H_

// Definicao de tipo para lista
typedef struct lista* Lista;
// Definicao de tipo para manipulacao de lista
typedef struct lista Elem;
// Definicao de tipo para informacao (op)
typedef char Tipo;

// Funcao para criar lista encadeada
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna lista vazia
Lista* criar_lista();

// Funcao para liberar lista
// Pre-condicao: lista criada
// Pos-condicao: libera lista e retorna nulo para ponteiro Lista
Lista* liberar_lista(Lista* l);

// Funcao para verificar condicao da lista
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se vazia
int lista_vazia(Lista *l);

// Funcao para inserir elemento na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void inserir_elemento(Lista* l, Tipo x);

// Funcao para remover elemento da lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void remover_elemento(Lista* l, Tipo x);

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void imprimir_lista(Lista* l);

#endif // LISTAS_H_
