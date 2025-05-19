#include "Rubro-Negra/rubro_negra.h"

int main()
{
    ArvoreRN* raiz;

    raiz = criar_arvore();

    inserir_no(raiz, 50);
    inserir_no(raiz, 60);
    inserir_no(raiz, 65);
    inserir_no(raiz, 10);
    inserir_no(raiz, 20);
    inserir_no(raiz, 15);

    imprimir_arvore(raiz);

    raiz = liberar_arvore(raiz);

    return 0;
}
