#include <stdio.h>
#include "include/busca.h"

int main()
{
    //int v[10] = {1, 5, 6, 2, 7, 8, 9, 12, 4, 23};
    int v[10] = {1, 2, 4, 8, 13, 43, 55, 123, 200, 230};

    printf("%d\n", busca_binaria_recursiva(v, 10, -1));

    return 0;
}
