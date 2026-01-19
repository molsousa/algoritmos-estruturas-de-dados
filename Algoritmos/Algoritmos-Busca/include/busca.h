#ifndef _ALGORITMOS_BUSCA_H_INCLUDED
#define _ALGORITMOS_BUSCA_H_INCLUDED

// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;

// Funcao para busca linear
// Percorre o vetor ate encontrar o valor desejado
// Caso o valor procurado esteja no final, a busca linear procura ate o valor n
// Complexidade de tempo = O(n)
// Entrada: vetor, numero de elemento, valor desejado
// Saida: verdadeiro ou falso
boolean busca_linear(int*, int, int);

// Funcao para busca binaria
// Conforme o valor buscado seja menor ou maior que o valor inicial
// Quebra o iterador no meio
// O vetor precisa estar ordenado para encontrar o valor
// Complexidade tempo = O(log n)
// Entrada: vetor, numero de elemento, valor desejado
// Saida: verdadeiro ou falso
boolean busca_binaria_iterativa(int*, int, int);

// Funcao recursiva para busca binaria
// Conforme o valor buscado seja menor ou maior que o valor inicial
// Quebra o iterador no meio
// O vetor precisa estar ordenado para encontrar o valor
// Complexidade tempo = O(log n)
// Entrada: vetor, numero de elemento, valor desejado
// Saida: verdadeiro ou falso
boolean busca_binaria_recursiva(int*, int, int);

#endif // _ALGORITMOS_BUSCA_H_INCLUDED
