#ifndef PILHA_H_
#define PILHA_H_

// Definicao de tipo para pilha
typedef struct pilha Pilha;
// Definicao de tipo para manipulacao de lista
typedef struct lista Elem;
// Definicao de tipo para elemento (op)
typedef int Tipo;

// Funcao para criar pilha dinamica
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna pilha vazia
Pilha* criar_pilha();

// Funcao para liberar pilha
// Pre-condicao: pilha criada
// Pos-condicao: retorna nulo para ponteiro Pilha
Pilha* liberar_pilha(Pilha* p);

// Verifica condicao da pilha
// Pre-condicao: pilha criada
// Pos-condicao: retorna 1 se pilha vazia
int pilha_vazia(Pilha* p);

// Funcao para empilhar elemento
// Pre-condicao: pilha criada
// Pos-condicao: nenhuma
void empilhar(Pilha* p, Tipo x);

// Funcao para desempilhar elemento
// Pre-condicao: pilha criada
// Pos-condicao: nenhuma
void desempilhar(Pilha* p);

// Funcao para imprimir pilha
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_pilha(Pilha* p);

#endif // PILHA_H_
