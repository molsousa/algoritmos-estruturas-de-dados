#include "src/circular.h"

int main()
{
    Lista* l = criar_lista();

    inserir_elemento(l, 2);
    inserir_elemento(l, 4);
    inserir_elemento(l, 1);
    inserir_elemento(l, 3);
    inserir_elemento(l, 5);
    inserir_elemento(l, 8);
    inserir_elemento(l, 7);
    inserir_elemento(l, 9);

    remover_elemento(l, 2);

    imprimir_lista(l);

    l = (Lista*) liberar_lista(l);

    return 0;
}
