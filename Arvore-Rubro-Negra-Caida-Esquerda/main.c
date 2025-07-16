#include "Rubro-Negra/rubro_negra.h"

int main()
{
    ArvoreRN* raiz;

    raiz = criar_arvore();

    inserir_no(raiz, 5);
    inserir_no(raiz, 3);
    inserir_no(raiz, 4);
    inserir_no(raiz, 2);
    inserir_no(raiz, 8);
    inserir_no(raiz, 7);
    inserir_no(raiz, 6);

    imprimir_arvore(raiz);

    raiz = liberar_arvore(raiz);

    return 0;
}
