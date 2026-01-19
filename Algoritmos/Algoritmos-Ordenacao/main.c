#include <stdio.h>
#include "include/ordenacao.h"

int main()
{
    int v[10] = {2, 1, 3, 6, 15, 4, 12, 18, 10, 23};
    int i;

    mergeSort(v, 10);

    for(i = 0; i < 10; i++)
        printf("%d\n", v[i]);

    return 0;
}
