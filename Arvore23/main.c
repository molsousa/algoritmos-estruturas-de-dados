#include "Arvore23/arvore23.h"

int main()
{
    arvore23 r = criar_arvore();

    r = inserir(r, 4);
    r = inserir(r, 6);
    r = inserir(r, 15);
    r = inserir(r, 11);
    r = inserir(r, 9);
    r = inserir(r, 50);
    r = inserir(r, 21);
    r = inserir(r, 34);

    r = remover(r, 4);

    imprimir_niveis(r);

    return 0;
}
