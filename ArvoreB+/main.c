#include "include/arvorebp.h"

int main()
{
    noBMais r = criar_arvore();

    r = inserir(r, 5);
    r = inserir(r, 22);
    r = inserir(r, 11);
    r = inserir(r, 23);
    r = inserir(r, 3);
    r = inserir(r, 8);
    r = inserir(r, 1);
    r = inserir(r, 4);
    r = inserir(r, 29);
    r = inserir(r, 65);
    r = inserir(r, 45);
    r = inserir(r, 27);
    r = inserir(r, 19);
    r = inserir(r, 10);
    r = inserir(r, 2);
    r = inserir(r, 12);
    r = inserir(r, 15);
    imprimir_niveis(r);

    return 0;
}
