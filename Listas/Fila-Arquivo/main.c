#include "include/fila.h"

int main()
{
    FILE* f = fopen("fila.bin", "w+b");

    criar_fila(f);

    enfilerar(f, 5);
    enfilerar(f, 3);
    enfilerar(f, 4);

    defilerar(f);
    defilerar(f);
    defilerar(f);

    enfilerar(f, 6);
    enfilerar(f, 3);

    defilerar(f);
    defilerar(f);

    enfilerar(f, 3);
    enfilerar(f, 2);
    enfilerar(f, 8);
    enfilerar(f, 1);
    enfilerar(f, 4);

    defilerar(f);
    defilerar(f);

    enfilerar(f, 12);
    enfilerar(f, 5);

    imprimir_fila(f);
    imprimir_pos_livre(f);

    fclose(f);

    return 0;
}
