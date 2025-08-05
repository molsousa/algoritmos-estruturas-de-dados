#include "include/avl.h"

int main()
{
    FILE* fr = fopen("avl.bin", "w+b");

    inicializar(fr);

    inserir(fr, 50);
    inserir(fr, 55);
    inserir(fr, 45);
    inserir(fr, 40);
    inserir(fr, 35);
    inserir(fr, 30);

    imprimir_niveis(fr);

    fclose(fr);

    return 0;
}
