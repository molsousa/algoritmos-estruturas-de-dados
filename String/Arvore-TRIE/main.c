#include "include/trie.h"

int main()
{
    TST_TRIE* h = criar_arvore();

    inserir(h, "Marcos", 17);
    inserir(h, "Ana", 10);
    inserir(h, "Simone", 19);
    inserir(h, "Zaire", 21);
    inserir(h, "Zimbabue", 25);
    inserir(h, "Solange", 23);
    inserir(h, "Lucas", 15);
    inserir(h, "Ledio", 24);
    inserir(h, "Maria", 9);
    inserir(h, "Hector", 28);
    inserir(h, "Joao", 27);
    inserir(h, "Murilo", 3);
    inserir(h, "Medico", 12);
    inserir(h, "Luana", 5);

    remover(h, "Ledio");

    imprimir(h);

    imprimir_dicionario(h);

    h = liberar(h);

    return 0;
}
