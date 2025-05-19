#ifndef ARVORE_RUBRO_NEGRA_H_INCLUDED
#define ARVORE_RUBRO_NEGRA_H_INCLUDED

typedef struct no* ArvoreRN;
typedef struct no No;

enum{
    VERMELHO = 1,
    PRETO = 0,
};

ArvoreRN* criar_arvore();

ArvoreRN* liberar_arvore(ArvoreRN* raiz);

int cor(No* no);

void troca_cor(No* no);

No* rotacionar_esquerda(No* no);

No* rotacionar_direita(No* no);

int inserir_no(ArvoreRN* raiz, int info);

int remover_no(ArvoreRN* raiz, int info);

void imprimir_arvore(ArvoreRN* raiz);

#endif // ARVORE_RUBRO_NEGRA_H_INCLUDED
