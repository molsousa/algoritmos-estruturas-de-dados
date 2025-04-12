#include "Filas/fila.h"

int main()
{
    Fila* f;

    f = criar_fila();

    enfileirar(f, 1);
    enfileirar(f, 2);
    enfileirar(f, 3);
    enfileirar(f, 4);
    enfileirar(f, 5);
    enfileirar(f, 6);

    imprimir_fila(f);

    desenfileirar(f);

    imprimir_fila(f);

    f = liberar_fila(f);

    return 0;
}
