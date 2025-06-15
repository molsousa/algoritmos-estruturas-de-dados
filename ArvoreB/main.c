#include "ArvoreB/arvoreb.h"

int main()
{
    ArvoreB raiz = criar_arvore();

    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 20);

    raiz = remover(raiz, 5);

    imprimir_por_niveis(raiz);

    return 0;
}
