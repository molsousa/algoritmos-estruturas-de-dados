#include <stdio.h>
#include "include/rubronegra.h"

int main()
{
    FILE* f = fopen("arvore.bin", "w+b");

    criar_arvore(f);

    inserir(f, 3);
    inserir(f, 2);
    inserir(f, 32);
    inserir(f, 6);
    inserir(f, 8);
    inserir(f, 27);
    inserir(f, 7);
    inserir(f, 4);
    inserir(f, 5);
    inserir(f, 24);
    inserir(f, 15);
    inserir(f, 18);
    inserir(f, 26);
    inserir(f, 10);
    inserir(f, 21);
    inserir(f, 12);
    inserir(f, 17);
    inserir(f, 1);
    inserir(f, 11);

    imprimir(f, 0);
    printf("\n");
    imprimir_niveis(f);
    printf("\n");
    printf("Total de nos da arvore: %d\n", contar_nos(f));
    printf("Total de nos vermelhos: %d\n", total_nos_vermelhos(f));

    fclose(f);

    return 0;
}
