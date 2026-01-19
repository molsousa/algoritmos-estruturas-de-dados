#include "Pilha/pilha.h"

int main()
{
    Pilha* p;

    p = criar_pilha();

    empilhar(p, 1);
    empilhar(p, 2);
    empilhar(p, 3);
    empilhar(p, 4);
    empilhar(p, 5);
    imprimir_pilha(p);

    desempilhar(p);
    imprimir_pilha(p);

    p = liberar_pilha(p);

    return 0;
}
