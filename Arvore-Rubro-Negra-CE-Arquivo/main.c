#include <stdio.h>
#include "include/rubronegra.h"

int main()
{
    FILE* f = fopen("arvore.bin", "w+b");

    criar_arvore(f);

    inserir(f, 5);
    inserir(f, 3);
    inserir(f, 8);
    inserir(f, 6);
    inserir(f, 1);
    inserir(f, 4);
    inserir(f, 2);

    return 0;
}
