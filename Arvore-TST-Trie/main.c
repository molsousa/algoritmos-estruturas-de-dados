#include <stdio.h>
#include "TST-Trie/arvoretst.h"

int main()
{
    Tst* arvore;

    arvore = criar_arvore();

    inserir_nome(arvore, "Ana", 5);
    inserir_nome(arvore, "America", 12);
    inserir_nome(arvore, "Adelice", 3);
    inserir_nome(arvore, "Adelia", 15);
    inserir_nome(arvore, "Austria", 2);
    inserir_nome(arvore, "Atraso", 13);
    inserir_nome(arvore, "Atrasado", 9);
    inserir_nome(arvore, "Marcos", 10);
    inserir_nome(arvore, "Maria", 19);

    printf("Impressao da arvore TST\n");
    imprimir_arvore(arvore);

    printf("\n");

    printf("Buscando o nome ->Adelia<- via valor\n");
    busca_dicionario(arvore, 15);

    printf("\n");

    printf("Buscando o ->Austria<- via nome\n");
    busca_arvore(arvore, "Austria");

    arvore = liberar_arvore(arvore);

    return 0;
}
