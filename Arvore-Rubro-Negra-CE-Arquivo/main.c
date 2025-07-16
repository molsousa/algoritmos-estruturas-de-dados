#include <stdio.h>
#include "include/rubronegra.h"

int main()
{
    FILE* f = fopen("arvore.bin", "w+b");

    criar_arvore(f);

    inserir(f, 50);
    inserir(f, 65);
    inserir(f, 75);
    inserir(f, 55);
    inserir(f, 70);
    inserir(f, 45);
    inserir(f, 40);

    imprimir(f);

    return 0;
}
