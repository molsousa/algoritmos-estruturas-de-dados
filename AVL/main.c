#include "Arvore-AVL/avl.h"

int main()
{
    Arvore_AVL* arvore;

    arvore = criar_arvore();

    inserir_elemento(arvore, 1);
    inserir_elemento(arvore, 2);
    inserir_elemento(arvore, 3);
    inserir_elemento(arvore, 4);
    inserir_elemento(arvore, 5);
    inserir_elemento(arvore, 6);

    imprimir_arvore(arvore);

    arvore = liberar_arvore(arvore);

    return 0;
}
