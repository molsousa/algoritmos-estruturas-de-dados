#include <stdio.h>
#include "Listas/listas.h"

void demonstrar_duplo();

int main()
{
    Lista* l = criar_lista();

    l = inserir_elemento(l, 40);
    l = inserir_elemento(l, 40);
    l = inserir_elemento(l, 40);
    l = inserir_elemento(l, 75);
    l = inserir_elemento(l, 80);
    l = inserir_elemento(l, 70);
    l = inserir_elemento_cauda(l, 45);
    l = inserir_elemento_cauda(l, 45);
    l = inserir_elemento_cauda(l, 60);
    l = inserir_elemento_cauda(l, 60);
    l = inserir_elemento_cauda(l, 60);
    l = inserir_elemento_ordenado(l, 55);
    l = inserir_elemento(l, 45);
    l = inserir_elemento_ordenado(l, 55);
    l = inserir_elemento_ordenado(l, 55);
    l = inserir_elemento_ordenado(l, 45);
    l = inserir_elemento_ordenado(l, 60);
    l = inserir_elemento_ordenado(l, 65);
    l = inserir_elemento_cauda(l, 40);
    printf("Lista original\n");
    imprimir_lista(l);

    printf("\nEliminado o elemento 60\n");
    l = remover_elemento(l, 60);
    imprimir_lista(l);

    printf("\nEliminado recorrencias de 45\n");
    l = remover_elemento_recorrencias(l, 45);
    imprimir_lista(l);

    printf("\n%d elementos distintos\n", contar_distintos(l));
    imprimir_lista(l);

    printf("\n%d ocorrencias para 40\n", contar_ocorrencias(l, 40));
    imprimir_lista(l);

    printf("\nEliminado repetidos\n");
    l = eliminar_repetidos(l);
    imprimir_lista(l);

    liberar_lista(l);

    printf("\n---Demonstracao-com-lista-duas-listas-ou-mais---\n");
    demonstrar_duplo();

    return 0;
}

void demonstrar_duplo()
{
    Lista* l1 = criar_lista();
    Lista* l2 = criar_lista();
    Lista* l3;

    l1 = inserir_elemento(l1, 2);
    l1 = inserir_elemento(l1, 5);
    l1 = inserir_elemento(l1, 6);
    printf("\nLista 1\n");
    imprimir_lista(l1);

    l2 = inserir_elemento_cauda(l2, 9);
    l2 = inserir_elemento_cauda(l2, 4);
    l2 = inserir_elemento_cauda(l2, 8);
    printf("\nLista 2\n");
    imprimir_lista(l2);

    l3 = concatenar_lista(l1, l2);
    printf("\nListas concatenadas\n");
    imprimir_lista(l3);
    liberar_lista(l3);

    l3 = intercalar_lista(l1, l2);
    printf("\nListas intercaladas\n");
    imprimir_lista(l3);
    liberar_lista(l3);

    l3 = inverter_lista(l1);
    printf("\nLista 1 invertida\n");
    imprimir_lista(l3);
    liberar_lista(l3);

    l1 = inverter_lista_original(l1);
    printf("\nLista original invertida\n");
    imprimir_lista(l1);

    l1 = append(l1, l2);
    printf("\nListas originais concatenadas\n");
    imprimir_lista(l1);
}
