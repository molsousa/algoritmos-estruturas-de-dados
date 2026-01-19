#include <stdio.h>
#include <stdlib.h>
#include "../include/ordenacao.h"

// Funcao auxiliar para troca de elementos
void troca(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Algoritmo de ordenacao por selecao
// Seleciona o menor elemento e o poe na menor posicao
// Tempo de complexidade no pior caso
// Comparacoes: O(n*n)
// Troca: O(n)
void selectionSort(int* v, int n)
{
    int i, j, min;

    for(i = 0; i < n-1; i++){
        min = i;
        for(j = i+1; j < n; j++)
            if(v[j] < v[min])
                min = j;

        troca(&v[i], &v[min]);
    }
}

// Algoritmo de ordenacao por insercao
// Insere cada elemento na posicao correta em relacao aos antecessores
// Tempo de complexidade no pior caso
// Comparacoes: O(n*n)
// Troca: O(n*n)
void insertionSort(int* v, int n)
{
    int i, j, troca;

    for(j = 1; j < n; j++){
        troca = v[j];

        for(i = j-1; i >= 0 && v[i] > troca; i--)
            v[i+1] = v[i];

        v[i+1] = troca;
    }
}

// Algoritmo de ordenacao em bolha
// Trocas sucessivas em que os elementos menores vao pro inicio e os maiores vao pro final
// Tempo de complexidade no pior caso
// Comparacoes: O(n*n)
// Troca: O(n*n)
void bubbleSort(int* v, int n)
{
    int i, j;

    for(i = n-1; i >= 0; i--)
        for(j = 1; j <= i; j++)
            if(v[j-1] > v[j]){
                troca(&v[j-1], &v[j]);
            }
}

// Entrada: vetor, indice da esquerda, indice do meio, indice da direita
static void intercala(int* v, int e, int m, int d)
{
    int i, j, k, *vet_aux;

    vet_aux = malloc((d-e) * sizeof(int));
    i = e;
    j = m;
    k = 0;

    while(i < m && j < d){
        if(v[i] <= v[j])
            vet_aux[k++] = v[i++];
        else
            vet_aux[k++] = v[j++];
    }

    while(i < m)
        vet_aux[k++] = v[i++];

    while(j < d)
        vet_aux[k++] = v[j++];

    for(i = e; i < d; i++)
        v[i] = vet_aux[i-e];

    free(vet_aux);
}

// Entrada: vetor, indice da esquerda, indice da direita
static void mergeSort_aux(int* v, int e, int d)
{
    if(e < d-1){
        int m = (e+d)/2;

        mergeSort_aux(v, e, m);
        mergeSort_aux(v, m, d);
        intercala(v, e, m, d);
    }
}

// Algoritmo de intercalacao
// Quebra o vetor recursivamente e ordena cada subvetor e ao final obtem o vetor ordenado
// Tempo de complexidade no pior caso
// Comparacoes: O(n log n)
// Troca: O(n log n)
/* Essa implementacao usa um vetor auxiliar que usa mais memoria,
 *existe implementacao com apenas o vetor a ser ordenado
*/
void mergeSort(int* v, int n)
{
    mergeSort_aux(v, 0, n);
}

// Entrada: vetor, indice da esquerda, indice da direita
static int split(int* v, int e, int d)
{
    int pivo, j, k;

    pivo = v[d];
    j = e;

    for(k = e; k < d; k++)
        if(v[k] <= pivo){
            troca(&v[j], &v[k]);
            j++;
        }
    v[d] = v[j];
    v[j] = pivo;

    return j;
}

// Entrada: vetor, indice da esquerda, indice da direita
static void quickSort_aux(int* v, int e, int d)
{
    int j;

    if(e < d){
        j = split(v, e, d);
        quickSort_aux(v, e, j-1);
        quickSort_aux(v, j+1, d);
    }
}

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
void quickSort(int* v, int n)
{
    quickSort_aux(v, 0, n-1);
}

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
void shellSort(int* v, int n)
{
    int i, j, k, s, w;
    int a[n], temp;

    for(i = 0; i < n; i++)
        a[i] = v[i];

    for(w = 0; w < n; w++){
        k = a[w];
        s = -k;

        for(i = k; i < n; i++){
            temp = v[i];
            j = i - k;

            if(s == 0){
                s = -k;
                s++;
                v[s] = temp;
            }

            while(temp < v[j] && j >= 0 && j <= n){
                v[j+k] = v[j];
                j -= k;
            }
            v[j + k] = temp;
        }
    }
}

// Entrada: vetor, numero de elementos, valor referencia
static void heapify(int* v, int n, int i)
{
    int maior = i;
    int e = 2*i+1;
    int d = 2*i+2;

    if(e < n && v[e] > v[maior])
        maior = e;

    if(d < n && v[d] > v[maior])
        maior = d;

    if(maior != i){
        troca(&v[i], &v[maior]);
        heapify(v, n, maior);
    }
}

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
void heapSort(int* v, int n)
{
    int i;

    for(i = n/2-1; i >= 0; i--)
        heapify(v, n, i);

    for(i = n-1; i > 0; i--){
        int troca = v[0];
        v[0] = v[i];
        v[i] = troca;
        heapify(v, i, 0);
    }
}
