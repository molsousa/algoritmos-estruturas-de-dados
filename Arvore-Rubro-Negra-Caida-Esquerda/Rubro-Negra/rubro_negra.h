#ifndef ARVORE_RUBRO_NEGRA_H_INCLUDED
#define ARVORE_RUBRO_NEGRA_H_INCLUDED

// Definicao de tipo para arvore Rubro Negra
typedef struct no* ArvoreRN;
// Definicao de tipo para manipular nos da arvore
typedef struct no No;

// Definicao de valores para identificar as cores da arvore
enum{
    VERMELHO = 1,
    PRETO = 0,
};

// Funcao para criar arvore Rubro Negra
// Pre-condicao: ponteiro para ArvoreRN criado
// Pos-condicao: retorna arvore criada
ArvoreRN* criar_arvore();

// Funcao para liberar arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro ArvoreRN
ArvoreRN* liberar_arvore(ArvoreRN* raiz);

// Funcao para retornar cor do no
// Pre-condicao: nenhuma
// Pos-condicao: retorna cor do no ou PRETO se for nulo
int cor(No* no);

// Funcao para trocar cor de nos da arvore
// Pre-condicao: ponteiro para no nao nulo
// Pre-condicao: altera cor da raiz e dos dois filhos (se nao forem nulos)
void troca_cor(No* no);

// Funcao para rotacionar a esquerda
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna novo no rotacionado para a esquerda
No* rotacionar_esquerda(No* no);

// Funcao para rotacionar a direita
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna novo no rotacionado para a direita
No* rotacionar_direita(No* no);

// Funcao para mover no a esquerda
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna subarvore rotacionada para a esquerda e com balanceamento de cor
No* mover_para_esquerda(No* no);

// Funcao para mover no a direita
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: retorna subarvore rotacionada para a direita e com balanceamento de cor
No* mover_para_direita(No* no);

// Funcao auxiliar para balancear apos remocao
// Pre-condicao: ponteiro para no nao nulo
// Pos-condicao: aplica balanceamento de cores onde for necessario
No* balancear(No* no);

// Funcao principal para inserir elemento
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento na arvore e garante raiz preta
void inserir_no(ArvoreRN* raiz, int info);

// Funcao principal para remover no
// Pre-condicao: arvore criada
// Pos-condicao: remove o elemento se encontrado
void remover_no(ArvoreRN* raiz, int info);

// Funcao para buscar valor na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se encontrado o elemento, 0 se nao
int buscar_arvore(ArvoreRN* raiz, int info);

// Funcao para imprimir arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: arvore impressa na tela
void imprimir_arvore(ArvoreRN* raiz);

#endif // ARVORE_RUBRO_NEGRA_H_INCLUDED
