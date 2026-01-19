#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

// Definicao para fila
typedef struct fila Fila;
// Definicao para tipo
typedef struct no* Tipo;

// Funcao para criar fila
// Pre-condicao: nenhuma
// Pos-condicao: cria nova fila vazia
Fila* criar_fila();

// Funcao para liberar fila criada
// Pre-condicao: fila criada
// Pos-condicao: nenhuma
void liberar_fila(Fila* f);

// Funcao para testar se uma fila eh vazia
// Pre-condicao: fila criada
// Pos-condicao: retorna 1 se vazia
int fila_vazia(Fila* f);

// Funcao para enfilerar item
// Pre-condicao: fila criada
// Pos-condicao: enfilera item na lista
void enqueue(Fila* f, Tipo x);

// Funcao para defilerar item
// Pre-condicao: fila criada
// Pos-condicao: retorna o valor defilerado
Tipo dequeue(Fila* f);

#endif // FILA_H_INCLUDED
