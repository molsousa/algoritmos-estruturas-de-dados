#include "Listas/listas.h"

int main()
{
    Lista *l;

    l = criar_lista();

    inserir_elemento(l, 'a');
    inserir_elemento(l, 'b');
    inserir_elemento(l, 'c');
    inserir_elemento(l, 'd');
    inserir_elemento(l, 'e');

    imprimir_lista(l);

    remover_elemento(l, 'c');

    imprimir_lista(l);

    l = liberar_lista(l);

    return 0;
}
