#include "include/rway.h"

int main()
{
    arvTrie* r = criar_arvore();

    inserir(r, "marcos", 8);
    inserir(r, "sousa", 11);
    inserir(r, "salsa", 9);
    inserir(r, "maria", 12);

    imprimir(r);

    return 0;
}
