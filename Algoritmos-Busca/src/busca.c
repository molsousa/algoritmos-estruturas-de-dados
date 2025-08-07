#include <stdio.h>
#include "../include/busca.h"

// Funcao para busca linear
// Percorre o vetor ate encontrar o valor desejado
// Caso o valor procurado esteja no final, a busca linear procura ate o valor n
// Complexidade de tempo = O(n)
boolean busca_linear(int* v, int n, int valor)
{
    int i;

    for(i = 0; i < n; i++)
        if(v[i] == valor)
            return true;

    return false;
}

// Funcao para busca binaria
// Conforme o valor buscado seja menor ou maior que o valor inicial
// Quebra o iterador no meio
// O vetor precisa estar ordenado para encontrar o valor
// Complexidade tempo = O(log n)
boolean busca_binaria_iterativa(int* v, int n, int valor)
{
    int e, m, d;

    e = -1;
    d = n;

    while(e < d-1){
        m = (e+d) / 2;

        if(v[m] == valor)
            return true;

        else if(v[m] < valor)
            e = m;

        else
            d = m;
    }

    return false;
}

// Funcao auxiliar para busca binaria
// Entrada: vetor, iterador menor, iterador maior, valor desejado
static boolean busca_binaria_aux(int* v, int e, int d, int valor)
{
    if(v[e] == valor || v[d] == valor)
        return true;

    else if(e == d-1 && v[e] != valor)
        return false;

    else{
        int m = (e+d)/2;

        if(v[m] < valor)
            return busca_binaria_aux(v, m, d, valor);

        else
            return busca_binaria_aux(v, e, m, valor);
    }
}

// Funcao para busca binaria
// Conforme o valor buscado seja menor ou maior que o valor inicial
// Quebra o iterador no meio
// O vetor precisa estar ordenado para encontrar o valor
// Complexidade tempo = O(log n)
boolean busca_binaria_recursiva(int* v, int n, int valor)
{
    return busca_binaria_aux(v, -1, n, valor);
}
