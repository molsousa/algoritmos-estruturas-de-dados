#include <stdio.h>
#include "Listas/listas.h"

void demonstrar_duplo();

int main()
{
    Lista* l1 = criar_lista();
    Lista* l2 = criar_lista();

    l1 = inserir_elemento_cauda(l1, 2);
    l1 = inserir_elemento_cauda(l1, 7);
    //l1 = inserir_elemento_cauda(l1, 7);
    //l2 = inserir_elemento_cauda(l2, 2);
    //l2 = inserir_elemento_cauda(l2, 6);
    l2 = inserir_elemento_cauda(l2, 9);
    l2 = inserir_elemento_cauda(l2, 11);

    Lista* l3 = merge_ord(l1, l2);

    imprimir_lista(l3);

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
