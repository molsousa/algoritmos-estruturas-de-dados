#include <stdio.h>
#include "include/arvorebp.h"

int main()
{
    noBMais r = criar_arvore();

    r = inserir(r, 5);
    r = inserir(r, 22);
    r = inserir(r, 11);
    r = inserir(r, 23);
    r = inserir(r, 3);
    r = inserir(r, 8);
    r = inserir(r, 1);
    r = inserir(r, 4);
    r = inserir(r, 29);
    r = inserir(r, 65);
    r = inserir(r, 45);
    r = inserir(r, 27);
    r = inserir(r, 19);
    r = inserir(r, 10);
    r = inserir(r, 2);
    r = inserir(r, 12);
    r = inserir(r, 15);
    r = inserir(r, 9);
    r = inserir(r, 24);
    r = inserir(r, 30);
    r = inserir(r, 50);
    r = inserir(r, 55);
    r = inserir(r, 25);
    r = inserir(r, 26);
    r = inserir(r, 21);
    r = inserir(r, 14);
    r = inserir(r, 16);
    r = inserir(r, 13);
    r = inserir(r, 17);
    r = inserir(r, 75);
    r = inserir(r, 71);
    r = inserir(r, 63);
    r = inserir(r, 79);
    r = inserir(r, 68);
    r = inserir(r, 80);
    r = inserir(r, 81);
    r = inserir(r, 99);
    r = inserir(r, 90);
    r = inserir(r, 85);
    r = inserir(r, 82);
    r = inserir(r, 6);
    /*
    */

    imprimir_niveis(r);

    imprimir_intervalo(r, 11, 34, fechado);

    printf("\ntotal nos internos: %d\n", conta_nos(r, interno));
    printf("\ntotal nos folhas: %d\n", conta_nos(r, folha));
    printf("\ntotal nos: %d\n", conta_nos(r, nosTotais));

    return 0;
}
