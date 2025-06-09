#include "Lista/lista.h"

int main()
{
    FILE* f = fopen("Lista.bin", "w+b");
    criar_lista(f);

    inserir_elemento(f, 2);
    inserir_elemento(f, 5);
    inserir_elemento(f, 4);
    inserir_elemento(f, 7);
    inserir_elemento(f, 6);
    inserir_elemento(f, 8);
    inserir_elemento(f, 3);

    remover_elemento(f, 6);

    imprimir_lista(f);

    return 0;
}
