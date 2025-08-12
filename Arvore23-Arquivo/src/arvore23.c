#include <stdlib.h>
#include "../include/arvore23.h"
#include "../include/fila.h"

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

no23* ler_no(FILE* f, int pos)
{
    no23* r = malloc(sizeof(no23));

    fseek(f, sizeof(cabecalho) + sizeof(no23) * pos, SEEK_SET);
    fread(r, sizeof(no23), 1, f);

    return r;
}

void escrever_no(FILE* f, no23* r, int pos)
{
    fseek(f, sizeof(cabecalho) + sizeof(no23) * pos, SEEK_SET);
    fwrite(r, sizeof(no23), 1, f);
}

void inicializar(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escrever_cabecalho(f, cab);
    free(cab);
}

boolean vazia(int pos)
{
    if(pos == -1)
        return true;

    return false;
}

boolean eh_folha(FILE* f, int pos)
{
    no23* r = ler_no(f, pos);

    if(vazia(r->esq) && vazia(r->meio) && vazia(r->dir)){
        free(r);
        return true;
    }
    free(r);

    return false;
}

int busca(FILE* f, int chave, int pos)
{
    if(vazia(pos))
        return pos;

    if(ler_no(f, pos)->chave_esq == chave)
        return pos;

    if(ler_no(f, pos)->num_chaves == 2 && ler_no(f, pos)->chave_dir == chave)
        return pos;

    if(chave < ler_no(f, pos)->chave_esq)
        return busca(f, chave, ler_no(f, pos)->esq);

    else if(ler_no(f, pos)->num_chaves == 1)
        return busca(f, chave, ler_no(f, pos)->meio);

    else if(chave < ler_no(f, pos)->chave_dir)
        return busca(f, chave, ler_no(f, pos)->meio);

    else
        return busca(f, chave, ler_no(f, pos)->dir);
}

int inserir_aux(FILE* f, int pos, int chave, int* chave_promovida, cabecalho* cab)
{
    no23* r = ler_no(f, pos);

    if(eh_folha(f, pos)){
        if(r->num_chaves == 1){
            adiciona_chave(f, pos, chave, -1);
            free(r);
            return -1;
        }
        else{
            free(r);
            return split(f, pos, chave, -1, chave_promovida, cab);
        }
    }
    else{
        int p_aux;
        int chave_aux;

        if(chave < r->chave_esq)
            p_aux = inserir_aux(f, r->esq, chave, &chave_aux, cab);

        else if((r->num_chaves == 1) || (chave < r->chave_dir))
            p_aux = inserir_aux(f, r->meio, chave, &chave_aux, cab);

        else
            p_aux = inserir_aux(f, r->dir, chave, &chave_aux, cab);

        if(vazia(p_aux)){
            free(r);
            return -1;
        }

        if(r->num_chaves == 1){
            free(r);
            adiciona_chave(f, pos, chave_aux, p_aux);
            return -1;
        }
        else{
            free(r);
            return split(f, pos, chave_aux, p_aux, chave_promovida, cab);
        }
    }
}

int split(FILE* f, int pos, int chave, int pos_subarvore, int* chave_promovida, cabecalho* cab)
{
    int p_aux;
    no23* r = ler_no(f, pos);

    if(chave > r->chave_dir){
        *chave_promovida = r->chave_dir;
        p_aux = r->dir;
        r->dir = -1;
        r->num_chaves = 1;

        escrever_no(f, r, pos);
        free(r);

        return cria_no(f, cab, chave, 0, p_aux, pos_subarvore, -1, 1);
    }
    else if(chave >= r->chave_esq){
        *chave_promovida = chave;
        p_aux = r->dir;
        r->dir = -1;
        r->num_chaves = 1;

        int chave_dir = r->chave_dir;

        escrever_no(f, r, pos);
        free(r);

        return cria_no(f, cab, chave_dir, 0, pos_subarvore, p_aux, -1, 1);
    }
    else{
        *chave_promovida = r->chave_esq;
        p_aux = cria_no(f, cab, r->chave_dir, 0, r->meio, r->dir, -1, 1);
        r->chave_esq = chave;
        r->num_chaves = 1;
        r->dir = -1;
        r->meio = pos_subarvore;

        escrever_no(f, r, pos);
        free(r);

        return p_aux;
    }
}

void adiciona_chave(FILE* f, int pos, int chave, int pos_aux)
{
    no23* r = ler_no(f, pos);

    if(r->chave_esq < chave){
        r->chave_dir = chave;
        r->dir = pos_aux;
    }
    else{
        r->chave_dir = r->chave_esq;
        r->chave_esq = chave;
        r->dir = r->meio;
        r->meio = pos_aux;
    }
    r->num_chaves = 2;

    escrever_no(f, r, pos);
    free(r);
}

int cria_no(FILE* f, cabecalho* cab, int chave_esq, int chave_dir, int esq, int meio, int dir, int num_chaves)
{
    int nova_pos = cab->pos_topo++;

    no23 novo;

    novo.chave_esq = chave_esq;
    novo.chave_dir = (num_chaves == 2) ? chave_dir : 0;
    novo.esq = esq;
    novo.meio = meio;
    novo.dir = (num_chaves == 2) ? dir : -1;
    novo.num_chaves = num_chaves;

    escrever_no(f, &novo, nova_pos);

    return nova_pos;
}

int inserir_chave(FILE* f, int chave, cabecalho* cab, int pos)
{
    if(vazia(pos))
        return cria_no(f, cab, chave, 0, -1, -1, -1, 1);

    else{
        int chave_promovida;

        int p_aux = inserir_aux(f, pos, chave, &chave_promovida, cab);

        if(!vazia(p_aux))
            return cria_no(f, cab, chave_promovida, 0, pos, p_aux, -1, 1);

        else
            return pos;
    }
}

void inserir(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    cab->pos_raiz = inserir_chave(f, chave, cab, cab->pos_raiz);
    escrever_cabecalho(f, cab);

    free(cab);
}

void liberar_pos(FILE* f, cabecalho* cab, int pos_livre)
{
    if(pos_livre == -1)
        return;

    no23* no_livre = ler_no(f, pos_livre);

    no_livre->esq = no_livre->meio = no_livre->dir = cab->pos_livre;
    cab->pos_livre = pos_livre;

    escrever_no(f, no_livre, pos_livre);
    free(no_livre);
}

int encontrar_menor(FILE* f, int pos)
{
    if(vazia(pos))
        return -1;

    no23* aux = ler_no(f, pos);
    int pos_esq = pos;

    while(aux->esq != -1){
        pos_esq = aux->esq;
        free(aux);
        aux = ler_no(f, pos_esq);
    }
    free(aux);

    return pos_esq;
}

void remover(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    if(busca(f, chave, cab->pos_raiz) == -1){
        free(cab);
        return;
    }

    cab->pos_raiz = remover_aux(f, chave, cab->pos_raiz, cab);

    if(cab->pos_raiz != -1 && ler_no(f, cab->pos_raiz)->num_chaves == 0){
        no23* r = ler_no(f, cab->pos_raiz);
        int pos_esq = r->esq;

        liberar_pos(f, cab, cab->pos_raiz);

        cab->pos_raiz = pos_esq;
    }
    escrever_cabecalho(f, cab);
    free(cab);
}

void imprimir_niveis(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_raiz;
    free(cab);

    if(vazia(pos))
        return;

    Fila fila = criar_fila();
    no23* r = ler_no(f, pos);

    no23* aux[10000];
    int j = 0;

    enqueue(fila, r);
    enqueue(fila, NULL);
    aux[j++] = r;

    while(!fila_vazia(fila)){
        no23* atual = dequeue(fila);

        if(atual == NULL){
            printf("\n");

            if(!fila_vazia(fila))
                enqueue(fila, NULL);
        }

        else{
            printf("[%d", atual->chave_esq);

            if(atual->num_chaves == 2)
                printf(",%d] ", atual->chave_dir);

            else
                printf(",-] ");

            if(atual->esq != -1){
                r = ler_no(f, atual->esq);
                enqueue(fila, r);
                aux[j++] = r;
            }

            if(atual->meio != -1){
                r = ler_no(f, atual->meio);
                enqueue(fila, r);
                aux[j++] = r;
            }

            if(atual->dir != -1){
                r = ler_no(f, atual->dir);
                enqueue(fila, r);
                aux[j++] = r;
            }
        }
    }

    while(j >= 0)
        free(aux[--j]);
}
