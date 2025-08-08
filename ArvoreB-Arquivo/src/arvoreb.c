#include <stdlib.h>
#include "../include/fila.h"
#include "../include/arvoreb.h"

void escrever_cabecalho(FILE* f, cabecalho* cab)
{
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, f);
}

cabecalho* ler_cabecalho(FILE* f)
{
    cabecalho* cab = malloc(sizeof(cabecalho));

    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, f);

    return cab;
}

void escrever_no(FILE* f, noB* r, int pos)
{
    fseek(f, sizeof(cabecalho) + sizeof(noB) * pos, SEEK_SET);
    fwrite(r, sizeof(noB), 1, f);
}

noB* ler_no(FILE* f, int pos)
{
    noB* r = malloc(sizeof(noB));

    fseek(f, sizeof(cabecalho) + sizeof(noB) * pos, SEEK_SET);
    fread(r, sizeof(noB), 1, f);

    return r;
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

boolean overflow(FILE* f, int pos)
{
    noB* r = ler_no(f, pos);
    int num_chaves = r->num_chaves;

    free(r);

    if(num_chaves == ORDEM)
        return true;

    return false;
}

int split(FILE* f, int pos, int* m, cabecalho* cab)
{
    noB* r = ler_no(f, pos);
    noB y;
    int nova_pos = cab->pos_topo++;

    int q = r->num_chaves/2;
    y.num_chaves = r->num_chaves - q - 1;
    r->num_chaves = q;
    *m = r->chaves[q];

    int i = 0;
    y.filhos[0] = r->filhos[q+1];

    while(i < y.num_chaves){
        y.chaves[i] = r->chaves[q+i+1];
        y.filhos[i+1] = r->filhos[q+i+2];
        i++;
    }
    escrever_no(f, &y, nova_pos);
    escrever_no(f, r, pos);

    return nova_pos;
}

int busca_pos(FILE* f, int pos, int chave, int* pos_chave)
{
    noB* r = ler_no(f, pos);

    for(*pos_chave = 0; *pos_chave < r->num_chaves; ++*pos_chave){
        if(chave == r->chaves[(*pos_chave)]){
            free(r);
            return 1;
        }
        else if(chave < r->chaves[(*pos_chave)])
            break;
    }
    free(r);

    return 0;
}

void adicionar_direita(FILE* f, int pos_r, int pos_chave, int k, int pos_p)
{
    int i;
    noB* r = ler_no(f, pos_r);

    for(i = r->num_chaves; i > pos_chave; i--){
        r->chaves[i] = r->chaves[i-1];
        r->filhos[i+1] = r->filhos[i];
    }

    r->chaves[pos_chave] = k;
    r->filhos[pos_chave+1] = pos_p;
    r->num_chaves++;

    escrever_no(f, r, pos_r);
    free(r);
}

void inserir(FILE* f, int chave)
{
    cabecalho* cab = ler_cabecalho(f);

    cab->pos_raiz = inserir_chave(f, chave, cab, cab->pos_raiz);
    escrever_cabecalho(f, cab);

    free(cab);
}

int inserir_chave(FILE* f, int chave, cabecalho* cab, int pos)
{
    //printf("alo\n");
    if(pos == -1){
        int i;
        pos = cab->pos_topo++;
        noB novo;
        novo.chaves[0] = chave;

        for(i = 0; i < ORDEM; i++)
            novo.filhos[i] = -1;

        novo.num_chaves = 1;
        escrever_no(f, &novo, pos);
    }
    else{
        inserir_aux(f, chave, cab, pos);

        if(overflow(f, pos)){
            int m;
            int i;

            int pos_split = split(f, pos, &m, cab);
            int nova_pos = cab->pos_topo++;

            noB* nova_raiz = malloc(sizeof(noB));
            noB* r = ler_no(f, pos);

            nova_raiz->chaves[0] = m;
            nova_raiz->filhos[0] = pos;
            nova_raiz->filhos[1] = pos_split;

            for(i = ((ORDEM/2)+1); i < ORDEM; i++)
                r->filhos[i] = -1;

            nova_raiz->num_chaves = 1;
            escrever_no(f, nova_raiz, nova_pos);
            escrever_no(f, r, pos);

            free(r);
            free(nova_raiz);

            return nova_pos;
        }
    }

    return pos;
}

void inserir_aux(FILE* f, int chave, cabecalho* cab, int pos)
{
    noB* r = ler_no(f, pos);
    int nova_pos;

    if(!busca_pos(f, pos, chave, &nova_pos)){
        if(r->filhos[0] == -1){
            adicionar_direita(f, pos, nova_pos, chave, -1);
        }

        else{
            inserir_aux(f, chave, cab, r->filhos[nova_pos]);

            if(overflow(f, nova_pos)){
                int m;

                int pos_aux = split(f, nova_pos, &m, cab);
                adicionar_direita(f, pos, nova_pos, m, pos_aux);
            }
        }
    }
    free(r);
}

void imprimir(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);

    imprimir_aux(f, cab->pos_raiz);
    free(cab);
}

void imprimir_aux(FILE* f, int pos)
{
    if(pos == -1)
        return;

    int i;
    noB* r = ler_no(f, pos);

    for(i = 0; i < r->num_chaves; i++){
        printf("%d ", r->chaves[i]);
        imprimir_aux(f, r->filhos[i]);
    }

    imprimir_aux(f, r->filhos[i]);
    free(r);
}

void imprimir_niveis(FILE* f)
{
    cabecalho* cab = ler_cabecalho(f);
    int pos = cab->pos_raiz;
    free(cab);

    if(pos == -1)
        return;

    Fila fila = criar_fila();
    noB* aux = ler_no(f, pos);

    enqueue(fila, aux);
    enqueue(fila, NULL);

    printf("[");

    while(!fila_vazia(fila)){
        noB* atual = dequeue(fila);

        if(atual == NULL){
            printf("\n");

            if(!fila_vazia(fila)){
                enqueue(fila, NULL);
                printf("[");
            }
        }

        else{
            int i;

            for(i = 0; i < atual->num_chaves; i++){
                printf("%d", atual->chaves[i]);
                if(i < atual->num_chaves-1)
                    printf(", ");

                else
                    printf("] ");
            }

            for(i = 0; atual->filhos[i] != -1 && i < atual->num_chaves+1; i++){
                aux = ler_no(f, atual->filhos[i]);
                enqueue(fila, aux);
            }

            if(!consultar_nulo(fila))
                printf("[");
        }
    }
}
