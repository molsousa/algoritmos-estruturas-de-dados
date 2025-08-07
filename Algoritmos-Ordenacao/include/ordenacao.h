#ifndef _ALGORITMOS_ORDENACAO_H_INCLUDED
#define _ALGORITMOS_ORDENACAO_H_INCLUDED

// Funcao auxiliar para troca de elementos
// Entrada: valores A e B para troca
void troca(int*, int*);

// Algoritmo de ordenacao por selecao
// Seleciona o menor elemento e o poe na menor posicao
// Tempo de complexidade no pior caso
// Comparacoes: O(n*n)
// Troca: O(n)
// Entrada: vetor, numero de elementos
void selectionSort(int*, int);

// Algoritmo de ordenacao por insercao
// Insere cada elemento na posicao correta em relacao aos antecessores
// Tempo de complexidade no pior caso
// Comparacoes: O(n*n)
// Troca: O(n*n)
// Entrada: vetor, numero de elementos
void insertionSort(int*, int);

// Algoritmo de ordenacao em bolha
// Trocas sucessivas em que os elementos menores vao pro inicio e os maiores vao pro final
// Tempo de complexidade no pior caso
// Comparacoes: O(n*n)
// Troca: O(n*n)
// Entrada: vetor, numero de elementos
void bubbleSort(int*, int);

// Algoritmo de intercalacao
// Quebra o vetor recursivamente e ordena cada subvetor e ao final obtem o vetor ordenado
// Tempo de complexidade no pior caso
// Comparacoes: O(n log n)
// Troca: O(n log n)
/* Essa implementacao usa um vetor auxiliar que usa mais memoria,
 *existe implementacao com apenas o vetor a ser ordenado
*/
// Entrada: vetor, numero de elementos
void mergeSort(int*, int);

// Algoritmo quickSort
/* Busca um pivo e separa o restante do vetor em duas partes
 *, os menores ou iguais que o pivo, e os maiores que o pivo.
 * Ordena as duas partes separadamente e apos concatena de forma
 * com que o pivo fique ao meio das duas partes
*/
// Tempo de complexidade no pior caso
// Comparacoes: O(n*n)
// Troca: O(n*n)
// Tempo de complexidade no medio caso
// Comparacoes: O(n log n)
// Troca: O(n log n)
// Entrada: vetor, numero de elementos
void quickSort(int*, int);

// Algoritmo shellSort
/* Divide o vetor em subvetores e ordena de forma independente
 * pode ser encarado como uma evolucao do insertionSort
*/
// Tempo de complexidade no pior caso
// Comparacoes: O(n^2)
// Troca: O(n^2)
// Tempo de complexidade no medio caso
// Comparacoes: O(n log n)
// Troca: O(n log n)
// Entrada: vetor, numero de elementos
void shellSort(int*, int);

// Algoritmo heapSort -> maxHeap
/* O maior elemento esta na posicao 0
 * eh trocado esse elemento com o ultimo elemento
 * eh reduzido o vetor em 1
 * apos isso, o algoritmo desce pelo vetor e troca o maior valor
 * pelo proximo maior (que nao o ja ordenado) e repete o mesmo sistema
*/
// Tempo de complexidade no pior caso
// Comparacoes: O(n log n)
// Troca: O(n log n)
// Entrada: vetor, numero de elementos
void heapSort(int*, int);

#endif // _ALGORITMOS_ORDENACAO_H_INCLUDED
