#include "include/arvoreb.h"

int main()
{
    FILE* f = fopen("arvore-b.bin", "w+b");

    inicializar(f);

    inserir(f, 5);
    inserir(f, 10);
    inserir(f, 7);
    inserir(f, 6);
    /*
    inserir(f, 9);
    inserir(f, 3);
    inserir(f, 1);
    inserir(f, 4);
    inserir(f, 17);
    inserir(f, 12);
    inserir(f, 19);
    inserir(f, 21);
    inserir(f, 8);
    inserir(f, 29);
    inserir(f, 32);
    inserir(f, 34);
    inserir(f, 54);
    inserir(f, 43);
    inserir(f, 28);
    inserir(f, 87);
    inserir(f, 45);
    inserir(f, 55);
    inserir(f, 59);
    inserir(f, 67);
    inserir(f, 69);
    inserir(f, 2);
    inserir(f, 13);
    inserir(f, 91);
    inserir(f, 18);
    inserir(f, 22);
    inserir(f, 26);
    inserir(f, 15);
    */

    remover(f, 5);

    imprimir_niveis(f);

    fclose(f);

    return 0;
}
