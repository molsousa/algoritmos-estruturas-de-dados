#include <stdio.h>
#include "ArvoreRB/arvorerb.h"

int main()
{
    ArvoreRB* r = criar_arvore();

    inserir(r, 1);
    inserir(r, 2);
    inserir(r, 3);
    inserir(r, 4);
    inserir(r, 5);
    inserir(r, 6);
    inserir(r, 7);
    inserir(r, 8);
    inserir(r, 9);

    remover(r, 4);

    printf("Nos vermelhos: %d\n", contar_noVermelho(r));

    preOrdem(r);

    return 0;
}
