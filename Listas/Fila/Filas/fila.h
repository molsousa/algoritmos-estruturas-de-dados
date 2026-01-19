#ifndef FILA_H_
#define FILA_H_

// Definicao de tipo para manipular lista
typedef struct lista Elem;
// Definicao de tipo para Fila
typedef struct fila Fila;
// Definicao de tipo para elemento (op)
typedef int Tipo;

// Funcao para criar fila
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna fila vazia
Fila* criar_fila();

// Funcao para liberar fila
// Pre-condicao: fila criada
// Pos-condicao: retorna nulo para ponteiro Fila
Fila* liberar_fila(Fila* f);

// Funcao para verificar condicao da fila
// Pre-condicao: fila criada
// Pos-condicao: retorna 1 se vazia
int fila_vazia(Fila* f);

// Funcao para inserir elemento na fila
// Pre-condicao: fila criada
// Pos-condicao: nenhuma
void enfileirar(Fila* f, Tipo x);

// Funcao para passar elemento da fila
// Pre-condicao: fila criada
// Pos-condicao: nenhuma
void desenfileirar(Fila* f);

// Funcao para imprimir fila
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_fila(Fila* f);

#endif // FILA_H_
