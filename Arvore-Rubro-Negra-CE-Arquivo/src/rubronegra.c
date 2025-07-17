#include <stdio.h>
#include <stdlib.h>
#include "../include/rubronegra.h"
#include "../include/fila.h"

void criar_arvore(FILE* f)
{
    system("color C");
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;

    escrever_cabecalho(f, cab);
    free(cab);
}

cabecalho* ler_cabecalho(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, f);

    return cab;
}

void escrever_cabecalho(FILE* f, cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, f);
}

no* ler_no(FILE* f, int pos)
{
    no* x = malloc(sizeof(no));

    fseek(f, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fread(x, sizeof(no), 1, f);

    return x;
}

void escrever_no(FILE* f, no* x, int pos)
{
    fseek(f, sizeof(cabecalho) + sizeof(no)*pos, SEEK_SET);
    fwrite(x, sizeof(no), 1, f);
}

int cor(FILE* f, int pos)
{
    if(pos == -1)
        return PRETO;

    no* x = ler_no(f, pos);
    int res = x->cor;
    free(x);

    return res;
}

int rotacionar_esquerda(FILE* f, int pos)
{
    no* h = ler_no(f, pos);
    int pos_x = h->dir;
    no* x = ler_no(f, pos_x);

    h->dir = x->esq;
    x->esq = pos;

    x->cor = h->cor;
    h->cor = VERMELHO;

    escrever_no(f, h, pos);
    escrever_no(f, x, pos_x);

    free(h);
    free(x);

    return pos_x;
}

int rotacionar_direita(FILE* f, int pos)
{
    no* h = ler_no(f, pos);
    int pos_x = h->esq;
    no* x = ler_no(f, pos_x);

    h->esq = x->dir;
    x->dir = pos;

    x->cor = h->cor;
    h->cor = VERMELHO;

    escrever_no(f, h, pos);
    escrever_no(f, x, pos_x);

    free(h);
    free(x);

    return pos_x;
}

void troca_cor(FILE* f, int pos)
{
    no* x = ler_no(f, pos);
    x->cor = !x->cor;

    if(x->esq != -1){
        no* filho_esq = ler_no(f, x->esq);
        filho_esq->cor = !filho_esq->cor;
        escrever_no(f, filho_esq, x->esq);
        free(filho_esq);
    }

    if(x->dir != -1){
        no* filho_dir = ler_no(f, x->dir);
        filho_dir->cor = !filho_dir->cor;
        escrever_no(f, filho_dir, x->dir);
        free(filho_dir);
    }
    escrever_no(f, x, pos);
    free(x);
}

int inserir_aux(FILE* f, cabecalho* cab, int chave, int pos)
{
    if(pos == -1){
        no novo;
        novo.chave = chave;
        novo.cor = VERMELHO;
        novo.dir = novo.esq = -1;

        int nova_pos = cab->pos_topo++;
        escrever_no(f, &novo, nova_pos);
        return nova_pos;
    }
    no* aux = ler_no(f, pos);

    if(aux->chave > chave)
        aux->esq = inserir_aux(f, cab, chave, aux->esq);

    else if(aux->chave < chave)
        aux->dir = inserir_aux(f, cab, chave, aux->dir);

    else{
        free(aux);
        return pos;
    }

    escrever_no(f, aux, pos);

    if(cor(f, aux->dir) == VERMELHO && cor(f, aux->esq) == PRETO){
        pos = rotacionar_esquerda(f, pos);
        free(aux);
        aux = ler_no(f, pos);
    }

    if(cor(f, aux->esq) == VERMELHO && cor(f, ler_no(f, aux->esq)->esq) == VERMELHO){
        pos = rotacionar_direita(f, pos);
        free(aux);
        aux = ler_no(f, pos);
    }

    if(cor(f, aux->esq) == VERMELHO && cor(f, aux->dir) == VERMELHO)
        troca_cor(f, pos);

    free(aux);

    return pos;
}

void inserir(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);
    cab->pos_raiz = inserir_aux(f, cab, chave, cab->pos_raiz);

    no* x = ler_no(f, cab->pos_raiz);
    if(x->cor != PRETO){
        x->cor = PRETO;
        escrever_no(f, x, cab->pos_raiz);
    }

    escrever_cabecalho(f, cab);

    free(x);
    free(cab);
}

int busca_aux(FILE* f, int chave, int pos)
{
    if(pos == -1)
        return pos;

    no* h = ler_no(f, pos);

    if(h->chave > chave){
        int ptr_esq = h->esq;
        free(h);
        return busca_aux(f, chave, ptr_esq);
    }

    else if(h->chave < chave){
        int ptr_dir = h->dir;
        free(h);
        return busca_aux(f, chave, ptr_dir);
    }

    else{
        free(h);
        return pos;
    }
}

int busca(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    int res = busca_aux(f, chave, cab->pos_raiz);
    free(cab);

    return res;
}

int mover_para_esquerda(FILE* f, int pos)
{
    troca_cor(f, pos);

    if(cor(f, (ler_no(f, ler_no(f, pos)->dir)->esq)) == VERMELHO){
        no* h = ler_no(f, pos);
        h->dir = rotacionar_direita(f, h->dir);

        escrever_no(f, h, pos);

        pos = rotacionar_esquerda(f, pos);
        free(h);
        troca_cor(f, pos);
    }

    return pos;
}

int mover_para_direita(FILE* f, int pos)
{
    troca_cor(f, pos);

    if(cor(f, ler_no(f, ler_no(f, pos)->esq)->esq) == VERMELHO){
        pos = rotacionar_direita(f, pos);
        troca_cor(f, pos);
    }

    return pos;
}

int balancear(FILE* f, int pos)
{
    if(cor(f, ler_no(f, pos)->dir) == VERMELHO)
        pos = rotacionar_esquerda(f, pos);

    no* h = ler_no(f, pos);

    if(h->esq != -1 && cor(f, h->esq) == VERMELHO && cor(f, ler_no(f, h->esq)->esq) == VERMELHO)
        pos = rotacionar_direita(f, pos);

    free(h);

    if(cor(f, ler_no(f, pos)->esq) == VERMELHO && cor(f, ler_no(f, pos)->dir) == VERMELHO)
        troca_cor(f, pos);

    return pos;
}

int remover_no_menor(FILE* f, cabecalho* cab, int pos)
{
    if(ler_no(f, pos)->esq == -1)
        return -1;

    if(cor(f, ler_no(f, pos)->esq) == PRETO && cor(f, ler_no(f, ler_no(f, pos)->esq)->esq) == PRETO)
        pos = mover_para_esquerda(f, pos);

    no* h = ler_no(f, pos);
    h->esq = remover_no_menor(f, cab, h->esq);

    escrever_no(f, h, pos);

    free(h);

    return balancear(f, pos);
}

int procurar_menor(FILE* f, int pos)
{
    no* t = ler_no(f, pos);
    int pos_menor = pos;

    while(t->esq != -1){
        pos_menor = t->esq;
        free(t);
        ler_no(f, pos_menor);
    }
    free(t);

    return pos_menor;
}

int remover_aux(FILE* f, cabecalho* cab, int chave, int pos)
{
    no* h = ler_no(f, pos);

    if(chave < h->chave){
        if(cor(f, h->esq) == PRETO && cor(f, ler_no(f, h->esq)->esq) == PRETO)
            pos = mover_para_esquerda(f, pos);

        free(h);
        h = ler_no(f, pos);

        h->esq = remover_aux(f, cab, chave, h->esq);
    }

    else{
        if(cor(f, h->esq) == VERMELHO)
            pos = rotacionar_direita(f, pos);

        free(h);
        h = ler_no(f, pos);

        if(chave == h->chave && h->dir == -1){
            free(h);
            return -1;
        }

        if(cor(f, h->dir) == PRETO && cor(f, ler_no(f, h->dir)->esq) == PRETO){
            pos = mover_para_direita(f, pos);
            free(h);
            h = ler_no(f, pos);
        }

        if(chave == h->chave){
            no* aux = ler_no(f, procurar_menor(f, h->dir));

            h->chave = aux->chave;
            free(aux);
            h->dir = remover_no_menor(f, cab, h->dir);
        }
        else
            h->dir = remover_aux(f, cab, chave, h->dir);
    }
    escrever_no(f, h, pos);
    free(h);

    return balancear(f, pos);
}

void remover(FILE* f, int chave)
{
    if(busca(f, chave) == -1)
        return;

    cabecalho* cab = ler_cabecalho(f);

    cab->pos_raiz = remover_aux(f, cab, chave, cab->pos_raiz);

    if(cab->pos_raiz != -1){
        no* h = ler_no(f, cab->pos_raiz);
        h->cor = PRETO;
        escrever_no(f, h, cab->pos_raiz);
    }

    escrever_cabecalho(f, cab);

    free(cab);
}

void imprimir_aux(FILE* f, int pos)
{
    if(pos == -1)
        return;

    no* aux = ler_no(f, pos);

    printf("%d - ", aux->chave);
    if(aux->cor == VERMELHO)
        printf("VERMELHO\n");

    else
        printf("PRETO\n");

    imprimir_aux(f, aux->esq);
    imprimir_aux(f, aux->dir);

    free(aux);
}

void imprimir(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_raiz;

    imprimir_aux(f, pos);

    free(cab);
}

void imprimir_niveis(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);

    if(cab->pos_raiz == -1){
        free(cab);
        return;
    }

    no* x = ler_no(f, cab->pos_raiz);
    no* aux[1000];
    int i = 0;

    Fila fila = criar_fila();
    enqueue(fila, x);
    enqueue(fila, NULL);
    aux[i++] = x;
    printf("< ");

    while(!fila_vazia(fila)){
        no* atual = dequeue(fila);

        if(atual == NULL){
            printf(" >\n");

            if(!fila_vazia(fila)){
                printf("< ");
                enqueue(fila, NULL);
            }
        }
        else{
            printf("%d", atual->chave);

            if(atual->esq != -1){
                x = ler_no(f, atual->esq);
                enqueue(fila, x);
                aux[i++] = x;
            }
            if(atual->dir != -1){
                x = ler_no(f, atual->dir);
                enqueue(fila, x);
                aux[i++] = x;
            }
            if(!consultar_nulo(fila))
                printf(" ");
        }
    }
    i--;
    while(i >= 0)
        free(aux[i--]);

    fila = liberar_fila(fila);
    free(cab);
}

int contar_nos(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);

    int res = contar_nos_aux(f, cab->pos_raiz);
    free(cab);

    return res;
}

int contar_nos_aux(FILE* f, int pos)
{
    if(pos == -1)
        return 0;

    no* aux = ler_no(f, pos);
    int pos_esq = aux->esq;
    int pos_dir = aux->dir;
    free(aux);

    return 1 + contar_nos_aux(f, pos_esq) + contar_nos_aux(f, pos_dir);
}
