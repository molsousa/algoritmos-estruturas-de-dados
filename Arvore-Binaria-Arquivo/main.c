#include "Arvore/arvore.h"

int main()
{
    FILE* f = fopen("Arvore.bin", "w+b");
    criar_arvore(f);

    inserir_no(f, 4);
    inserir_no(f, 2);
    inserir_no(f, 3);
    inserir_no(f, 1);
    inserir_no(f, 6);
    inserir_no(f, 5);
    inserir_no(f, 7);

    remover_no(f, 4);

    imprimir_arvore(f);

    return 0;
}
