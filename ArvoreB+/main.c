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

    imprimir_niveis(r);

    return 0;
}
