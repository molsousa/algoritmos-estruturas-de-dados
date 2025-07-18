#include "include/trie.h"

int main()
{
    Trie h = criar_arvore();

    h = inserir(h, "Marcos", 17);
    h = inserir(h, "Ana", 10);
    h = inserir(h, "Simone", 19);
    h = inserir(h, "Zaire", 21);
    h = inserir(h, "Zimbabue", 25);
    h = inserir(h, "Solange", 23);
    h = inserir(h, "Lucas", 15);
    h = inserir(h, "Ledio", 24);
    h = inserir(h, "Maria", 9);
    h = inserir(h, "Hector", 28);
    h = inserir(h, "Joao", 27);
    h = inserir(h, "Murilo", 3);
    h = inserir(h, "Medico", 12);
    h = inserir(h, "Luana", 5);

    h = remover(h, "Ledio");

    imprimir(h);

    h = liberar(h);

    return 0;
}
