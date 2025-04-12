#include <stdio.h>
#include "Arvore/arvore.h"

int main()
{
    Arvore* raiz;

    raiz = criar_arvore();

    inserir_no(raiz, 4);
    inserir_no(raiz, 2);
    inserir_no(raiz, 1);
    inserir_no(raiz, 3);
    inserir_no(raiz, 6);
    inserir_no(raiz, 5);
    inserir_no(raiz, 7);

    printf("Encontrado -> %d\n", busca_arvore(raiz, 7));

    remover_no(raiz, 4);

    imprimir_arvore_pre(raiz);

    return 0;
}
