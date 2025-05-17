#include "Rubro-Negra/rubro_negra.h"

int main()
{
    ArvoreRN* raiz = criar_arvore();

    inserir_no(raiz, 5);
    inserir_no(raiz, 10);
    inserir_no(raiz, 15);
    inserir_no(raiz, 20);
    inserir_no(raiz, 25);
    inserir_no(raiz, 30);

    imprimir_arvore(raiz);

    raiz = liberar_arvore(raiz);

    return 0;
}
