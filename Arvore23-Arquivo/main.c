#include "include/arvore23.h"

int main()
{
    FILE* f = fopen("arvore-23.bin", "w+b");

    inicializar(f);

    inserir(f, 4);
    inserir(f, 6);
    inserir(f, 15);
    inserir(f, 11);
    inserir(f, 9);
    inserir(f, 50);
    inserir(f, 21);
    inserir(f, 34);
    inserir(f, 23);
/*
    inserir(f, 13);
    inserir(f, 7);
    inserir(f, 14);
    inserir(f, 18);
    inserir(f, 60);
    inserir(f, 90);
    inserir(f, 17);
    inserir(f, 8);
    inserir(f, 91);
    inserir(f, 92);
*/
    remover(f, 21);

    imprimir_niveis(f);

    return 0;
}
