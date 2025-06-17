#include "ArvoreB/arvoreb.h"

int main()
{
    ArvoreB raiz = criar_arvore();

    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 35);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 45);

    raiz = remover(raiz, 15);

    imprimir_por_niveis(raiz);

    return 0;
}
