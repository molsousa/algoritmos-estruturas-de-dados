#include "include/lista_listas.h"
#include "include/lista.h"

int main()
{
    Lista_Listas* ll = criar();

    Lista l1 = criar_lista();
    Lista l2 = criar_lista();
    Lista l3 = criar_lista();
    Lista l4 = criar_lista();

    l1 = inserir_no(l1, 4);
    l1 = inserir_no(l1, 8);
    l1 = inserir_no(l1, 1);

    ll = inserir(ll, 5, l1);

    l2 = inserir_no(l2, 2);
    l2 = inserir_no(l2, 7);
    l2 = inserir_no(l2, 10);
    l2 = inserir_no(l2, 12);
    l2 = inserir_no(l2, 11);

    ll = inserir(ll, 12, l2);

    l3 = inserir_no(l3, 44);
    l3 = inserir_no(l3, 23);
    l3 = inserir_no(l3, 17);
    l3 = inserir_no(l3, 25);
    l3 = inserir_no(l3, 99);

    ll = inserir(ll, 23, l3);

    l4 = inserir_no(l4, 26);
    l4 = inserir_no(l4, 19);
    l4 = inserir_no(l4, 17);
    l4 = inserir_no(l4, 71);

    ll = inserir(ll, 14, l4);

    l1 = inserir_no(l1, 97);
    l2 = inserir_no(l2, 13);
    l3 = inserir_no(l3, 4);
    l4 = inserir_no(l4, 90);

    ll = inserir(ll, 9, l1);
    ll = inserir(ll, 7, l2);
    ll = inserir(ll, 11, l3);
    ll = inserir(ll, 16, l4);

    ll = remover(ll, 11);

    imprimir(ll);

    return 0;
}
