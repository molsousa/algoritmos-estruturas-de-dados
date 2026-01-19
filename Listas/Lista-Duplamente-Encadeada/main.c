#include "Lista/listade.h"

int main()
{
    Lista* l = criar_lista();

    inserir_elemento_ordenado(l, 3);
    inserir_elemento_ordenado(l, 1);
    inserir_elemento_ordenado(l, 5);
    inserir_elemento_ordenado(l, 6);
    inserir_elemento_ordenado(l, 9);
    inserir_elemento_ordenado(l, 4);
    inserir_elemento_ordenado(l, 8);
    inserir_elemento_ordenado(l, 7);
    inserir_elemento_ordenado(l, 2);

    remover_elemento(l, 5);

    imprimir_ida_volta(l);

    l = liberar_lista(l);

    return 0;
}
