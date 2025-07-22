#include "include/avl.h"

int main()
{
    arvoreAVL* r;

    r = criar_arvore();

    inserir(r, 1);
    inserir(r, 2);
    inserir(r, 3);
    inserir(r, 4);
    inserir(r, 5);
    inserir(r, 6);
    inserir(r, 7);
    inserir(r, 8);
    inserir(r, 9);
    inserir(r, 10);
    inserir(r, 11);
    inserir(r, 12);
    inserir(r, 13);
    inserir(r, 14);
    inserir(r, 15);

    remover(r, 8);

    imprimir_niveis(r);

    r = liberar_arvore(r);

    return 0;
}
