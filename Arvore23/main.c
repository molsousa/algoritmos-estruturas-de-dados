#include "Arvore23/arvore23.h"

int main()
{
    Arvore23 raiz = criar_arvore();

    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 11);
    raiz = inserir(raiz, 9);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 21);
    raiz = inserir(raiz, 34);
    raiz = inserir(raiz, 23);
    raiz = inserir(raiz, 13);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 14);
    raiz = inserir(raiz, 18);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 90);
    raiz = inserir(raiz, 17);
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 91);
    raiz = inserir(raiz, 92);
    raiz = inserir(raiz, 12);

    imprimir_niveis(raiz);

    return 0;
}
