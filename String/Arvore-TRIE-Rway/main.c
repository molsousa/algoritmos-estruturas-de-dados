#include "include/rway.h"

int main()
{
    arvTrie* r = criar_arvore();

    inserir(r, "marcos", 8);
    inserir(r, "sousa", 11);
    inserir(r, "salsa", 9);
    inserir(r, "americo", 23);
    inserir(r, "amavel", 15);
    inserir(r, "chevrolet", 12);
    inserir(r, "maria", 17);
    inserir(r, "pai", 5);
    inserir(r, "pais", 2);

    remover(r, "pai");

    imprimir(r);

    return 0;
}
