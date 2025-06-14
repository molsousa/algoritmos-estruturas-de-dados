#include <stdio.h>
#include "Arvore/arvore.h"

int main()
{
    Arvore raiz = criar_arvore();

    raiz = inserir_no(raiz, 50);
    raiz = inserir_no(raiz, 40);
    raiz = inserir_no(raiz, 45);
    raiz = inserir_no(raiz, 30);
    raiz = inserir_no(raiz, 20);
    raiz = inserir_no(raiz, 35);
    raiz = inserir_no(raiz, 60);
    raiz = inserir_no(raiz, 55);
    raiz = inserir_no(raiz, 70);
    raiz = inserir_no(raiz, 65);
    raiz = inserir_no(raiz, 75);

    imprimir_por_niveis(raiz);

    return 0;
}
