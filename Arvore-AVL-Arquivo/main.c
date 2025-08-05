#include "include/avl.h"

int main()
{
    FILE* fr = fopen("avl.bin", "w+b");

    inicializar(fr);

    inserir(fr, 1);
    inserir(fr, 43);
    inserir(fr, 12);
    inserir(fr, 76);
    inserir(fr, 13);
    inserir(fr, 23);
    inserir(fr, 18);
    inserir(fr, 5);
    inserir(fr, 50);
    inserir(fr, 55);
    inserir(fr, 38);
    inserir(fr, 25);
    inserir(fr, 32);

    remover(fr, 1);
    remover(fr, 18);

    imprimir_livres(fr);

    inserir(fr, 78);
    inserir(fr, 62);

    imprimir_niveis(fr);

    //remover(fr, 43);
    remover(fr, 50);
    remover(fr, 55);
    remover(fr, 76);
    remover(fr, 78);
    //remover(fr, 43);

    imprimir_livres(fr);

    imprimir_niveis(fr);

    fclose(fr);

    return 0;
}
