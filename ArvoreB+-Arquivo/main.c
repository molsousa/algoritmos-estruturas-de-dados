#include "include/arvoreb+.h"

int main()
{
    FILE* f = fopen("arvoreB+.bin", "w+b");

    inicializar(f);

    insere(f, 5);
    insere(f, 22);
    insere(f, 3);
    insere(f, 45);
    insere(f, 12);
    insere(f, 23);
    insere(f, 55);
    insere(f, 65);
    insere(f, 78);
    insere(f, 98);
    insere(f, 39);
    //insere(f, 5);

    imprimir_niveis(f);

    return 0;
}
