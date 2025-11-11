#include <stdio.h>
#include <stdlib.h>
#include "../include/arvorebp.h"

// Estrutura para no B+ com ponteiro para pai
struct nodeBMais{
    int* chave;
    void** ponteiro;
    short num_chaves;
    boolean eh_folha;
    struct nodeBMais* pai;
};

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
boolean vazia(noBMais r)
{
    return (r == NULL);
}

// Funcao para criar arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para tipo noBMais
noBMais criar_arvore()
{
    return NULL;
}

// Funcao para verificar overflow
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
boolean overflow(noBMais r)
{
    return (r->num_chaves == ORDEM);
}

// Funcao para contar folhas totais
// Pre-condicao: nenhuma
// Pos-condicao: insere no ponteiro total o valor total de folhas
void conta_nos_folhas_aux(noBMais r, int* total)
{
    if(vazia(r))
        return;

    int i;

    if(r->eh_folha)
        ++*total;

    for(i = 0; i <= r->num_chaves; i++)
        conta_nos_folhas_aux(r->ponteiro[i], total);
}

// Funcao para contar nos totais
// Pre-condicao: nenhuma
// Pos-condicao: insere no ponteiro total o valor total de nos
void conta_nos_aux(noBMais r, int* total)
{
    if(vazia(r))
        return;

    int i;

    ++*total;

    for(i = 0; i <= r->num_chaves; i++)
        conta_nos_aux(r->ponteiro[i], total);
}

// Funcao chamadora para contar nos
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int conta_nos(noBMais r, modo m)
{
    if(vazia(r))
        return 0;

    int total = 0;
    int aux = 0;

    if(m == folha || m == interno)
        conta_nos_folhas_aux(r, &total);

    else
        conta_nos_aux(r, &total);

    if(m == interno){
        conta_nos_aux(r, &aux);

        total = aux - total;
    }

    return total;
}

// Funcao para separar nos
// Pre-condicao: overflow
// Pos-condicao: retorna o no a direita e a chave sucessora no ponteiro
noBMais split(noBMais r, int* m)
{
    int q, i;

    noBMais y = malloc(sizeof(struct nodeBMais));
    y->chave = malloc(ORDEM * sizeof(int));
    y->ponteiro = calloc((ORDEM+1), sizeof(void*));

    q = r->num_chaves/2;
    *m = r->chave[q];

    y->ponteiro[0] = r->ponteiro[q+1];

    if(r->eh_folha){
        y->num_chaves = r->num_chaves - q;

        y->eh_folha = true;
        r->num_chaves = q;

        for(i = 0; i < y->num_chaves; i++)
            y->chave[i] = r->chave[q+i];
    }
    else{
        y->num_chaves = r->num_chaves - q - 1;

        y->eh_folha = false;
        r->num_chaves = q;

        for(i = 0; i < y->num_chaves; i++){
            y->chave[i] = r->chave[q+i+1];
            y->ponteiro[i+1] = r->ponteiro[q+i+2];
        }
    }

    return y;
}

// Funcao para buscar posicao de pagina B+
// Pre-condicao: arvore criada
// Pos-condicao: retorna verdadeiro se encontrada a chave
boolean busca_pos(noBMais r, int chave, int* pos)
{
    for((*pos) = 0; (*pos) < r->num_chaves; ++*pos)
        if(r->chave[(*pos)] == chave)
            return true;

        else if(chave < r->chave[(*pos)])
            break;

    return false;
}

// Funcao para adicionar chave a direita
// Pre-condicao: nenhuma
// Pos-condicao: insere chave e ponteiro a direita
void adicionar_direita(noBMais r, int pos, int k, noBMais p)
{
    int i;
    for(i = r->num_chaves; i > pos; i--){
        r->chave[i] = r->chave[i-1];
        r->ponteiro[i+1] = r->ponteiro[i];
    }

    if(!vazia(p) && !p->eh_folha)
        corrigir_pai(p);

    if(!vazia(p))
        p->pai = r;

    r->chave[pos] = k;
    r->ponteiro[pos+1] = p;
    r->num_chaves++;
}

// Funcao auxiliar para inserir em pagina B
// Pre-condicao: nenhuma
// Pos-condicao: insere nova chave
void inserir_aux(noBMais r, int chave)
{
    int pos;

    if(!busca_pos(r, chave, &pos)){
        if(r->eh_folha)
            adicionar_direita(r, pos, chave, NULL);

        else{
            inserir_aux(r->ponteiro[pos], chave);

            if(overflow(r->ponteiro[pos])){
                int m;
                noBMais p = split(r->ponteiro[pos], &m);
                adicionar_direita(r, pos, m, p);
            }
        }
    }
}

// Funcao para criar pagina B
// Pre-condicao: nenhuma
// Pos-condicao: cria um ponteiro para pagina B
noBMais criaPagina(int* chave, boolean eh_folha, int num_chaves)
{
    int i;

    noBMais r;

    r = malloc(sizeof(struct nodeBMais));
    r->chave = malloc(ORDEM * sizeof(int));
    r->ponteiro = calloc((ORDEM+1), sizeof(void*));
    r->pai = NULL;

    for(i = 0; i < num_chaves; i++)
        r->chave[i] = chave[i];

    r->eh_folha = eh_folha;
    r->num_chaves = num_chaves;

    return r;
}

// Funcao para correcao de ponteiro para pai
// Pre-condicao: nenhuma
// Pos-condicao: insere ponteiro para pai ao no
void corrigir_pai(noBMais pai)
{
    noBMais r;
    int i;

    for(i = 0; i <= pai->num_chaves; i++){
        r = pai->ponteiro[i];
        r->pai = pai;
    }
}

// Funcao para correcao de intervalos
// Pre-condicao: nenhuma
// Pos-condicao: corrige e insere ponteiros de proximo aos intervalos
void corrigir_intervalo(noBMais r)
{
    void** aux = malloc(conta_nos(r, nosTotais) * sizeof(void*));
    void** nos_intervalo = malloc(conta_nos(r, folha) * sizeof(void*));

    int i, j, k, fim, inicio, nivel;
    k = fim = inicio = 0;

    aux[fim++] = r;

    while(fim > inicio){
        nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            noBMais atual = aux[inicio++];

            if(atual->eh_folha)
                nos_intervalo[k++] = atual;

            for(j = 0; j <= atual->num_chaves; j++)
                if(atual->ponteiro[j] != NULL)
                    aux[fim++] = atual->ponteiro[j];
        }
    }
    free(aux);

    for(i = 0; i < k-1; i++){
        noBMais atual = nos_intervalo[i];
        noBMais prox = nos_intervalo[i+1];

        atual->ponteiro[ORDEM] = prox;
    }

    free(nos_intervalo);
}

// Funcao para inserir chave na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere chave na arvore
noBMais inserir(noBMais r, int chave)
{
    if(vazia(r))
        return criaPagina(&chave, true, 1);

    else{
        inserir_aux(r, chave);

        if(overflow(r)){
            int i;
            int m;

            noBMais x = split(r, &m);
            noBMais nova_raiz = criaPagina(&m, false, 1);

            nova_raiz->ponteiro[0] = r;
            nova_raiz->ponteiro[1] = x;

            r->pai = x->pai = nova_raiz;

            if(!r->eh_folha){
                corrigir_pai(r);
                corrigir_pai(x);
            }

            for(i = (((int)ORDEM/2)+1); i < ORDEM; i++)
                r->ponteiro[i] = NULL;

            corrigir_intervalo(r);

            return nova_raiz;
        }
    }

    corrigir_intervalo(r);

    return r;
}

// Funcao para imprimir intervalo completo de chaves
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void ler_intervalo(noBMais r)
{
    while(!vazia(r->ponteiro[0]))
        r = r->ponteiro[0];

    while(!vazia(r)){
        int i;

        printf("[");
        for(i = 0; i < r->num_chaves; i++){
            printf("%d", r->chave[i]);

            if(i < r->num_chaves-1)
                printf(",");
        }

        printf("]");

        r = r->ponteiro[ORDEM];
    }
    printf("\n");
}

// Funcao auxiliar para imprimir intervalo aberto
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
static void imprimir_aberto(noBMais r, int a, int b)
{
    if(vazia(r))
        return;

    int i;

    for(i = 0; i < r->num_chaves; i++){
        if(r->chave[i] > a && r->chave[i] < b){
            printf("%4d", r->chave[i]);
        }
    }

    imprimir_aberto(r->ponteiro[ORDEM], a, b);
}

// Funcao auxiliar para imprimir intervalo fechado
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
static void imprimir_fechado(noBMais r, int a, int b)
{
    if(vazia(r))
        return;

    int i;

    for(i = 0; i < r->num_chaves; i++){
        if(r->chave[i] >= a && r->chave[i] <= b)
            printf("%4d", r->chave[i]);
    }

    imprimir_fechado(r->ponteiro[ORDEM], a, b);
}

// Funcao chamadora para imprimir intervalo
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_intervalo(noBMais r, int a, int b, intervalo ab)
{
    if(vazia(r))
        return;

    while(!vazia(r->ponteiro[0]))
        r = r->ponteiro[0];

    if(ab == aberto)
        imprimir_aberto(r, a, b);

    else
        imprimir_fechado(r, a, b);

    printf("\n");
}

// Funcao para imprimir por niveis
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_niveis(noBMais r)
{
    if(vazia(r))
        return;

    void** aux = malloc(conta_nos(r, nosTotais) * sizeof(void*));
    int i, j, nivel, inicio, fim;
    fim = inicio = 0;

    aux[fim++] = r;

    while(fim > inicio){
        nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            noBMais atual = aux[inicio++];
            printf("[");

            for(j = 0; j < atual->num_chaves; j++){
                printf("%d", atual->chave[j]);

                if(j < atual->num_chaves - 1)
                    printf("|");
            }

            printf("]");

            if(atual->eh_folha)
                printf("->");

            else
                printf(" ");

            for(j = 0; j <= atual->num_chaves; j++)
                if(atual->ponteiro[j] != NULL)
                    aux[fim++] = atual->ponteiro[j];
        }
        if(fim == inicio && !r->eh_folha)
            printf("NULL\n");

        printf("\n");
    }

    free(aux);
}
