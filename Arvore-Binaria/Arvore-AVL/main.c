#include "include/avl.h"

int main()
{
    arvoreAVL* r;

    r = criar_arvore();

    inserir(r, 2);
    inserir(r, 1);
    inserir(r, 60);
    inserir(r, 22);
    inserir(r, 13);
    inserir(r, 24);
    inserir(r, 54);
    inserir(r, 8);
    inserir(r, 34);
    inserir(r, 48);
    inserir(r, 11);
    inserir(r, 4);
    inserir(r, 18);

    remover(r, 22);
    remover(r, 24);

    imprimir_niveis(r);

    r = liberar_arvore(r);

    return 0;
}
