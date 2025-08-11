#include "Arvore23/arvore23.h"

int main()
{
    arvore23 raiz = criar_arvore();

    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 21);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 9);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 34);
    raiz = inserir(raiz, 23);
    raiz = inserir(raiz, 13);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 11);

    //raiz = remover(raiz, 4);
    //raiz = remover(raiz, 50);
    raiz = remover(raiz, 6);

    imprimir_niveis(raiz);

    return 0;
}
