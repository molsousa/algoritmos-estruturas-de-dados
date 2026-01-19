#include <stdio.h>
#include <stdlib.h>
#include "arvorerb.h"

// Estrutura para no rubro negro
struct norb{
    int chave;
    enum{VERMELHO, PRETO} cor;
    struct norb* esq;
    struct norb* dir;
    struct norb* pai;
};

// Funcao para criar arvore rubro negra
// Pre-condicao: nenhuma
// Pos-condicao: retorna ponteiro para ArvoreRB
ArvoreRB* criar_arvore()
{
    ArvoreRB* aux;
    noRB* temp;

    aux = malloc(sizeof(ArvoreRB));
    temp = aux->nil = malloc(sizeof(noRB));

    temp->pai = temp->esq = temp->dir = temp;
    temp->cor = PRETO;
    temp->chave = 0;
    temp = aux->raiz = malloc(sizeof(noRB));
    temp->pai = temp->esq = temp->dir = aux->nil;
    temp->chave = 0;
    temp->cor = PRETO;

    return aux;
}

// Funcao auxiliar para buscar no
// Pre-condicao: nenhuma
// Pos-condicao: retorna endereco do valor buscado ou nulo
noRB* busca_aux(ArvoreRB* r, noRB* x, int chave)
{
    if(x == r->nil)
        return NULL;

    else{
        if(x->chave == chave)
            return x;

        else if(x->chave > chave)
            return busca_aux(r, x->esq, chave);

        else
            return busca_aux(r, x->dir, chave);
    }
}

// Funcao para buscar no
// Pre-condicao: arvore criada
// Pos-condicao: retorna no de busca_aux
noRB* busca(ArvoreRB* r, int chave)
{
    return busca_aux(r, r->raiz->esq, chave);
}

// Funcao para rotacionar para a esquerda
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona no x para a esquerda
void rotacao_esq(ArvoreRB* r, noRB* x)
{
    noRB* y;
    noRB* nil = r->nil;
    y = x->dir;
    x->dir = y->esq;

    if(y->esq != nil)
        y->esq->pai = x;

    y->pai = x->pai;

    if(x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
}

// Funcao para rotacionar para a direita
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona no y para a direita
void rotacao_dir(ArvoreRB* r, noRB* y)
{
    noRB* x;
    noRB* nil = r->nil;

    x = y->esq;
    y->esq = x->dir;

    if(nil != x->dir)
        x->dir->pai = y;

    x->pai = y->pai;

    if(y == y->pai->esq)
        y->pai->esq = x;

    else
        y->pai->dir = x;

    x->dir = y;
    y->pai = x;
}

// Funcao para auxiliar para inserir
// Pre-condicao: nenhuma
// Pos-condicao: insere em arvore rubro negra
void insereRB_aux(ArvoreRB* r, noRB* z)
{
    noRB* x;
    noRB* y;
    noRB* nil = r->nil;

    z->esq = z->dir = nil;
    y = r->raiz;
    x = r->raiz->esq;

    while(x != nil){
        y = x;
        if(x->chave > z->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;

    if((y == r->raiz) || (y->chave > z->chave))
        y->esq = z;

    else
        y->dir = z;
}

// Funcao para inserir em arvore rubro negra
// Pre-condicao: arvore criada
// Pos-condicao: insere chave e retorna no inserido
noRB* inserir(ArvoreRB* r, int chave)
{
    noRB* y;
    noRB* x;
    noRB* novoNo;

    x = malloc(sizeof(noRB));
    x->chave = chave;
    insereRB_aux(r, x);
    novoNo = x;
    x->cor = VERMELHO;

    while(x->pai->cor == VERMELHO){
        if(x->pai == x->pai->pai->esq){
            y = x->pai->pai->dir;
            if(y->cor == VERMELHO){
                x->pai->cor = PRETO;
                y->cor = PRETO;
                x->pai->pai->cor = VERMELHO;
                x = x->pai->pai;
            }
            else{
                if(x == x->pai->dir){
                    x = x->pai;
                    rotacao_esq(r, x);
                }
                x->pai->cor = PRETO;
                x->pai->pai->cor = VERMELHO;
                rotacao_dir(r, x->pai->pai);
            }
        }
        else{
            y = x->pai->pai->esq;
            if(y->cor == VERMELHO){
                x->pai->cor = PRETO;
                y->cor = PRETO;
                x->pai->pai->cor = VERMELHO;
                x = x->pai->pai;
            }
            else{
                if(x == x->pai->esq){
                    x = x->pai;
                    rotacao_dir(r, x);
                }
                x->pai->cor = PRETO;
                x->pai->pai->cor = VERMELHO;
                rotacao_esq(r, x->pai->pai);
            }
        }
    }
    r->raiz->esq->cor = PRETO;
    return novoNo;
}

// Funcao para encontrar o minimo
// Pre-condicao: nenhuma
// Pos-condicao: encontra o menor valor da subarvore da direita
noRB* minimo(ArvoreRB* r, noRB* x)
{
    while(x->esq != r->nil)
        x = x->esq;

    return x;
}

// Funcao para encontrar sucessor
// Pre-condicao: nenhuma
// Pos-condicao: retorna no sucessor para o pai
noRB* sucessor(ArvoreRB* r, noRB* x)
{
    if(x != r->nil)
        return minimo(r, x->dir);

    noRB* y = x->pai;

    while(y != r->nil && x == y->dir){
        x = y;
        y = y->pai;
    }

    return y;
}

// Funcao auxiliar para remover no
// Pre-condicao: nenhuma
// Pos-condicao: corrige possiveis violacoes antes da remocao
void removerRB_aux(ArvoreRB* r, noRB* x)
{
    noRB* raiz = r->raiz->esq;
    noRB* w;

    while((x->cor != VERMELHO) && (raiz != x)){
        if(x == x->pai->esq){
            w = x->pai->dir;
            if(w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacao_esq(r, x->pai);
                w = x->pai->dir;
            }
            if((w->dir->cor != VERMELHO) && (w->esq->cor != VERMELHO)){
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{
                if(w->dir->cor != VERMELHO){
                    w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacao_dir(r, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                x->dir->cor = PRETO;
                rotacao_esq(r, x->pai);
                x = raiz;
            }
        }
        else{
            w = x->pai->esq;
            if(w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacao_dir(r, x->pai);
                w = x->pai->esq;
            }
            if((w->dir->cor != VERMELHO) && (w->esq->cor != VERMELHO)){
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{
                if(w->esq->cor != VERMELHO){
                    w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacao_esq(r, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esq->cor = PRETO;
                rotacao_dir(r, x->pai);
                x = raiz;
            }
        }
    }
    x->cor = PRETO;
}

// Funcao cauda para remover no
// Pre-condicao: nenhuma
// Pos-condicao: remove no da arvore rubro negra
void removerRB(ArvoreRB* r, noRB* z)
{
    noRB* y;
    noRB* x;
    noRB* nil = r->nil;
    noRB* raiz = r->raiz;

    y = ((z->esq == nil) || (z->dir == nil)) ? z : sucessor(r, z);
    x = (y->esq == nil) ? y->dir : y->esq;

    if(raiz == (x->pai = y->pai))
        raiz->esq = x;

    else if(y == y->pai->esq)
        y->pai->esq = x;

    else
        y->pai->dir = x;

    if(y != z){
        if(y->cor != VERMELHO)
            removerRB_aux(r, x);

        y->esq = z->esq;
        y->dir = z->dir;
        y->pai = z->pai;
        y->cor = z->cor;
        z->esq->pai = z->dir->pai = y;

        if(z == z->pai->esq)
            z->pai->esq = y;
        else
            z->pai->dir = y;

        free(z);
    }
    else{
        if(y->cor != VERMELHO)
            removerRB_aux(r, x);

        free(y);
    }
}

// Funcao para remover no
// Pre-condicao: arvore criada
// Pos-condicao: remove no
void remover(ArvoreRB* r, int chave)
{
    noRB* no = busca(r, chave);
    if(no == NULL)
        return;

    removerRB(r, no);
}

// Funcao auxiliar para contar nos vermelhos
// Pre-condicao: nenhuma
// Pos-condicao: retorna numero de nos vermelhos
int contar_noVermelho_aux(ArvoreRB* r, noRB* x)
{
    if(r->nil == x)
        return 0;

    if(x->cor == VERMELHO)
        return 1 + contar_noVermelho_aux(r, x->esq) + contar_noVermelho_aux(r, x->dir);

    return contar_noVermelho_aux(r, x->esq) + contar_noVermelho_aux(r, x->dir);
}

// Funcao para contar nos vermelhos
// Pre-condicao: arvore criada
// Pos-condicao: retorna valor da auxiliar
int contar_noVermelho(ArvoreRB* r)
{
    return contar_noVermelho_aux(r, r->raiz->esq);
}

// Funcao auxiliar para imprimir a arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore
void pre_ordem_aux(ArvoreRB* r, noRB* x)
{
    if(x == r->nil)
        return;

    else{
        printf("%d - ", x->chave);
        if(x->cor == VERMELHO)
            printf("VERMELHO\n");

        else
            printf("PRETO\n");

        pre_ordem_aux(r, x->esq);
        pre_ordem_aux(r, x->dir);
    }
}

// Funcao para imprimir a arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void preOrdem(ArvoreRB* r)
{
    pre_ordem_aux(r, r->raiz->esq);
}
