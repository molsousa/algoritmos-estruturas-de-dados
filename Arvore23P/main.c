#include <stdio.h>
#include "include/arvore23.h"

int main()
{
    arvore23 r = criar_arvore();

    r = inserir(r, 5);
    r = inserir(r, 13);
    r = inserir(r, 27);
    r = inserir(r, 19);
    r = inserir(r, 9);
    r = inserir(r, 23);
    r = inserir(r, 17);
    r = inserir(r, 34);
    r = inserir(r, 54);
    r = inserir(r, 42);
    r = inserir(r, 58);
    r = inserir(r, 39);
    r = inserir(r, 29);
    r = inserir(r, 65);
    r = inserir(r, 59);

    r = remover(r, 59);
    r = remover(r, 23);
    r = remover(r, 27);
    r = remover(r, 34);

    imprimir_niveis(r);

    return 0;
}
