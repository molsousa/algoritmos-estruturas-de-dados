#include "ArvoreB/arvoreb.h"

int main()
{
    ArvoreB raiz = criar_arvore();

    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 35);
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 45);
    raiz = inserir(raiz, 52);
    raiz = inserir(raiz, 21);
    raiz = inserir(raiz, 17);
    raiz = inserir(raiz, 19);
    raiz = inserir(raiz, 32);
    raiz = inserir(raiz, 42);
    raiz = inserir(raiz, 39);
    raiz = inserir(raiz, 28);
    raiz = inserir(raiz, 11);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 91);
    raiz = inserir(raiz, 73);
    raiz = inserir(raiz, 54);
    raiz = inserir(raiz, 27);
    raiz = inserir(raiz, 65);
    raiz = inserir(raiz, 61);
    raiz = inserir(raiz, 92);
    raiz = inserir(raiz, 24);
    raiz = inserir(raiz, 16);
    raiz = inserir(raiz, 3);

    raiz = remover(raiz, 11);

    imprimir_por_niveis(raiz);

    return 0;
}
