#include <stdlib.h>
#include <time.h>
#include "include/arvoreb.h"

int main()
{
    system("color B");
    srand(time(NULL));

    FILE* f = fopen("arvore-b.bin", "w+b");
    register int i;

    inicializar(f);

    for(i = 0; i < 50; i++)
        inserir(f, (rand()%498+1));
/*
*/
    imprimir_niveis(f);

    fclose(f);

    return 0;
}
