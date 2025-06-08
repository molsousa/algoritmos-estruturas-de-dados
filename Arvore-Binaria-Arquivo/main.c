#include "Arvore/arvore.h"

int main()
{
    FILE* f = criar_arvore();
    Cabecalho* c = ler_cabecalho(f);

    inserir_no(f, c, 60);
    inserir_no(f, c, 50);
    inserir_no(f, c, 55);
    inserir_no(f, c, 58);
    inserir_no(f, c, 40);
    inserir_no(f, c, 70);
    inserir_no(f, c, 80);
    inserir_no(f, c, 75);

    remover_no(f, c, 60);

    imprimir_arvore(f, c);

    return 0;
}
