#include "Arvore23/arvore23.h"

int main()
{
    Arvore23 raiz = criar_arvore();

    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 30);

    imprimir_niveis(raiz);

    return 0;
}
