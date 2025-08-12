#include <stdio.h>
#include <stdlib.h>
#include "arvore23.h"

// Estrutura para arvore23
struct no23{
    int chave_esq;
    int chave_dir;
    struct no23* esq;
    struct no23* meio;
    struct no23* dir;
    int num_chaves;
};

// Funcao para criar arvore23
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro Arvore23
arvore23 criar_arvore()
{
    return NULL;
}

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(arvore23 r)
{
    return (r == NULL);
}

// Funcao para buscar na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o no buscado
arvore23 busca(arvore23 r, int chave)
{
    if(vazia(r))
        return r;

    if(r->chave_esq == chave)
        return r;

    if(r->num_chaves == 2 && r->chave_dir == chave)
        return r;

    if(chave < r->chave_esq)
        return busca(r->esq, chave);

    else if(r->num_chaves == 1)
        return busca(r->meio, chave);

    else if(chave < r->chave_dir)
        return busca(r->meio, chave);

    else
        return busca(r->dir, chave);
}

// Funcao auxiliar para inserir em 23
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
arvore23 inserir_aux(arvore23 r, int chave, int* chave_promovida)
{
    if(eh_folha(r)){
        if(r->num_chaves == 1){
            adiciona_chave(r, chave, NULL);
            return NULL;
        }
        else
            return split(r, chave, NULL, chave_promovida);
    }
    else{
        arvore23 p_aux;
        int chave_aux;

        if(chave < r->chave_esq)
            p_aux = inserir_aux(r->esq, chave, &chave_aux);

        else if((r->num_chaves == 1) || (chave < r->chave_dir))
            p_aux = inserir_aux(r->meio, chave, &chave_aux);

        else
            p_aux = inserir_aux(r->dir, chave, &chave_aux);

        if(p_aux == NULL)
            return NULL;

        if(r->num_chaves == 1){
            adiciona_chave(r, chave_aux, p_aux);
            return NULL;
        }
        else
            return split(r, chave_aux, p_aux, chave_promovida);
    }
}

// Funcao para aplicar split em determinado no
// Pre-condicao: elemento na espera de ser inserido
// Pos-condicao: separa um no em dois
arvore23 split(arvore23 p, int chave, arvore23 subarvore, int* chave_promovida)
{
    arvore23 p_aux;

    if(chave > p->chave_dir){
        *chave_promovida = p->chave_dir;
        p_aux = p->dir;
        p->dir = NULL;
        p->num_chaves = 1;
        return cria_no(chave, 0, p_aux, subarvore, NULL, 1);
    }

    else if(chave >= p->chave_esq){
        *chave_promovida = chave;
        p_aux = p->dir;
        p->dir = NULL;
        p->num_chaves = 1;
        return cria_no(p->chave_dir, 0, subarvore, p_aux, NULL, 1);
    }

    else{
        *chave_promovida = p->chave_esq;
        p_aux = cria_no(p->chave_dir, 0, p->meio, p->dir, NULL, 1);
        p->chave_esq = chave;
        p->num_chaves = 1;
        p->dir = NULL;
        p->meio = subarvore;
        return p_aux;
    }
}

// Funcao para adicionar para adicionar chave
// Pre-condicao: nenhuma
// Pos-condicao: adiciona chave a esquerda ou a direita a depender do tamanho
void adiciona_chave(arvore23 r, int chave, arvore23 p)
{
    if(r->chave_esq < chave){
        r->chave_dir = chave;
        r->dir = p;
    }
    else{
        r->chave_dir = r->chave_esq;
        r->chave_esq = chave;
        r->dir = r->meio;
        r->meio = p;
    }
    r->num_chaves = 2;
}

// Funcao que verifica se um no eh folha
// Pre-condicao: no nao nulo
// Pos-condicao: retorna 1 se folha
int eh_folha(arvore23 p)
{
    return (!p->esq && !p->meio && !p->dir);
}

// Funcao auxiliar para criar no23
// Pre-condicao: nenhuma
// Pos-condicao: retorna novo no
arvore23 cria_no(int chave_esq, int chave_dir, arvore23 esq, arvore23 meio, arvore23 dir, int num_chaves)
{
    arvore23 novo = malloc(sizeof(struct no23));
    novo->chave_esq = chave_esq;
    novo->chave_dir = (num_chaves == 2) ? chave_dir : 0;
    novo->esq = esq;
    novo->meio = meio;
    novo->dir = (num_chaves == 2) ? dir : NULL;
    novo->num_chaves = num_chaves;

    return novo;
}

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento
arvore23 inserir(arvore23 r, int chave)
{
    if(vazia(r))
        return cria_no(chave, 0, NULL, NULL, NULL, 1);

    else{
        int chave_promovida;
        arvore23 aux = inserir_aux(r, chave, &chave_promovida);

        if(!vazia(aux))
            return cria_no(chave_promovida, 0, r, aux, NULL, 1);

        else
            return r;
    }
}

// Funcao para encontrar o menor no
// Pre-condicao: nenhuma
// Pos-condicao: retorna menor no a partir do no buscado
arvore23 encontrar_menor(arvore23 r)
{
    if(vazia(r))
        return NULL;

    arvore23 aux = r;

    while(aux->esq != NULL)
        aux = aux->esq;

    return aux;
}

// Funcao para verificar e tratar underflow
// Pre-condicao: removido o elemento
// Pos-condicao: verifica e corrige o balanceamento da arvore
arvore23 tratar_underflow(arvore23 pai, int pos_filho)
{
    if(pos_filho == 0)
        return (pai->meio->num_chaves == 2) ? redistribuir(pai, 0) : merge(pai, 0);

    if(pos_filho == 1){
        if(pai->esq->num_chaves == 2)
            return redistribuir(pai, 1);

        if(pai->dir != NULL && pai->dir->num_chaves == 2)
            return redistribuir(pai, 1);

        return merge(pai, 1);
    }
    return (pai->meio->num_chaves == 2) ? redistribuir(pai, 2) : merge(pai, 2);
}

// Funcao para redistribuir chaves
// Pre-condicao: remoção não ocasiona em merge e altera o balanceamento da arvore
// Pos-condicao: retorna ponteiro pai apos redistribuição
arvore23 redistribuir(arvore23 pai, int pos_filho)
{
    arvore23 esq = pai->esq;
    arvore23 meio = pai->meio;
    arvore23 dir = pai->dir;
    arvore23 no_underflow = (pos_filho == 0) ? esq : ((pos_filho == 1) ? meio : dir);

    if(pos_filho == 0){
        no_underflow->chave_esq = pai->chave_esq;
        pai->chave_esq = meio->chave_esq;
        meio->chave_esq = meio->chave_dir;
        meio->chave_dir = 0;
        meio->num_chaves = 1;
        no_underflow->num_chaves = 1;

        if(!eh_folha(meio)){
            no_underflow->meio = meio->esq;
            meio->esq = meio->meio;
            meio->meio = meio->dir;
            meio->dir = NULL;
        }
    }
    else if(pos_filho == 1){
        if(esq->num_chaves == 2){
            no_underflow->meio = no_underflow->esq;
            no_underflow->chave_esq = pai->chave_esq;
            pai->chave_esq = esq->chave_dir;
            esq->chave_dir = 0; esq->num_chaves = 1;
            no_underflow->num_chaves = 1;

            if(!eh_folha(esq)){
                no_underflow->esq = esq->dir;
                esq->dir = NULL;
            }
        }
        else{
            no_underflow->chave_esq = pai->chave_dir;
            pai->chave_dir = dir->chave_esq;
            dir->chave_esq = dir->chave_dir;
            dir->chave_dir = 0;
            dir->num_chaves = 1;
            no_underflow->num_chaves = 1;

            if(!eh_folha(dir)){
                no_underflow->meio = dir->esq;
                dir->esq = dir->meio;
                dir->meio = dir->dir;
                dir->dir = NULL;
            }
        }
    }
    else{
        no_underflow->meio = no_underflow->esq;
        no_underflow->chave_esq = pai->chave_dir;
        pai->chave_dir = meio->chave_dir;
        meio->chave_dir = 0;
        meio->num_chaves = 1;
        no_underflow->num_chaves = 1;

        if(!eh_folha(meio)){
            no_underflow->esq = meio->dir;
            meio->dir = NULL;
        }
    }
    return pai;
}

// Funcao para juntar dois nos
// Pre-condicao: elemento removido
// Pos-condicao: retorna no pai concatenado com outra chave descendente
arvore23 merge(arvore23 pai, int pos_filho)
{
    if(pos_filho <= 1){
        arvore23 esq = pai->esq;
        arvore23 meio = pai->meio;

        if(pos_filho == 0){
            esq->chave_esq = pai->chave_esq;
            esq->chave_dir = meio->chave_esq;

            if(!eh_folha(meio))
                esq->meio = meio->esq;

            esq->dir = meio->meio;
        }
        else{
            esq->chave_dir = pai->chave_esq;
            if(!eh_folha(meio))
                esq->dir = meio->esq;
        }

        esq->num_chaves = 2;
        free(meio);

        pai->chave_esq = pai->chave_dir;
        pai->chave_dir = 0;
        pai->meio = pai->dir;
        pai->dir = NULL;
        pai->num_chaves--;
    }
    else{
        arvore23 meio = pai->meio;
        arvore23 dir = pai->dir;

        meio->chave_dir = pai->chave_dir;
        meio->num_chaves = 2;

        if(!eh_folha(dir))
            meio->dir = dir->esq;

        free(dir);

        pai->dir = NULL;
        pai->chave_dir = 0;
        pai->num_chaves--;
    }
    return pai;
}

// Funcao auxiliar para remover elemento
// Pre-condicao: nenhuma
// Pos-condicao: remove elemento e rebalanceia a arvore se necessario
arvore23 remover_aux(arvore23 r, int chave)
{
    if(vazia(r))
        return NULL;

    int pos_filho_underflow = -1;

    if(eh_folha(r)){
        if(r->num_chaves == 2){
            if(r->chave_dir == chave)
                r->chave_dir = 0;

            else if(r->chave_esq == chave){
                r->chave_esq = r->chave_dir;
                r->chave_dir = 0;
            }

            r->num_chaves = 1;
        }
        else
            if(r->chave_esq == chave)
                r->num_chaves = 0;

        return r;
    }

    if(r->chave_esq == chave || (r->num_chaves == 2 && r->chave_dir == chave)){
        arvore23 sucessor;

        if(r->chave_esq == chave){
            sucessor = encontrar_menor(r->meio);
            int chave_sucessor = sucessor->chave_esq;
            r->chave_esq = chave_sucessor;
            r->meio = remover_aux(r->meio, chave_sucessor);
            pos_filho_underflow = 1;
        }
        else{
            sucessor = encontrar_menor(r->dir);
            int chave_sucessor = sucessor->chave_esq;
            r->chave_dir = chave_sucessor;
            r->dir = remover_aux(r->dir, chave_sucessor);
            pos_filho_underflow = 2;
        }
    }
    else{
        if(chave < r->chave_esq){
            r->esq = remover_aux(r->esq, chave);
            pos_filho_underflow = 0;
        }
        else if(r->num_chaves == 1 || chave < r->chave_dir){
            r->meio = remover_aux(r->meio, chave);
            pos_filho_underflow = 1;
        }
        else{
            r->dir = remover_aux(r->dir, chave);
            pos_filho_underflow = 2;
        }
    }

    if(pos_filho_underflow != -1){
        arvore23 filho;

        if(pos_filho_underflow == 0)
            filho = r->esq;

        else if(pos_filho_underflow == 1)
            filho = r->meio;

        else
            filho = r->dir;

        if(filho != NULL && filho->num_chaves == 0)
            r = tratar_underflow(r, pos_filho_underflow);
    }

    return r;
}

// Funcao para remover elemento
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
arvore23 remover(arvore23 r, int chave)
{
    if(busca(r, chave) == NULL)
        return r;

    r = remover_aux(r, chave);

    if(r != NULL && r->num_chaves == 0){
        arvore23 nova_raiz = r->esq;
        free(r);
        return nova_raiz;
    }
    return r;
}

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore ordenada na tela
void inOrdem(arvore23 r)
{
    if(vazia(r))
        return;

    inOrdem(r->esq);
    printf("%d\n", r->chave_esq);
    inOrdem(r->meio);
    if(r->num_chaves == 2)
        printf("%d\n", r->chave_dir);

    if(r->num_chaves == 2)
        inOrdem(r->dir);
}

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore preOrdenada na tela
void preOrdem(arvore23 r)
{
    if(vazia(r))
        return;

    printf("%d - ", r->chave_esq);

    if(r->num_chaves == 2)
        printf("%d\n", r->chave_dir);

    preOrdem(r->esq);
    preOrdem(r->meio);

    if(r->num_chaves == 2)
        preOrdem(r->dir);
}

// Funcao de imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime por niveis
void imprimir_niveis(arvore23 r)
{
    if(vazia(r))
        return;

    int inicio, fim, i;
    arvore23* fila = malloc(1000 * sizeof(arvore23));

    inicio = fim = 0;
    fila[fim++] = r;

    while(inicio < fim){
        int nivel = fim - inicio;

        for(i = 0; i < nivel; i++){
            arvore23 atual = fila[inicio++];

            printf("[");
            if(atual->num_chaves >= 1)
                printf("%d", atual->chave_esq);
            if(atual->num_chaves == 2)
                printf(",%d", atual->chave_dir);

            else
                printf(",-");
            printf("] ");

            if(atual->esq != NULL)
                fila[fim++] = atual->esq;
            if(atual->meio != NULL)
                fila[fim++] = atual->meio;
            if(atual->num_chaves == 2 && atual->dir != NULL)
                fila[fim++] = atual->dir;
        }
        printf("\n");
    }
    free(fila);
}
