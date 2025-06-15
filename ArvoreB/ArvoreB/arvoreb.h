#ifndef ARVORE_B_H_INCLUDED
#define ARVORE_B_H_INCLUDED
#define ORDEM 5

// Definicao de itpo para arvore-B
typedef struct no* ArvoreB;

// Funcao para criar arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro ArvoreB
ArvoreB criar_arvore();

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(ArvoreB raiz);

// Funcao que separa nos
// Pre-condicao: arvore criada
// Pos-condicao: retorna o no separado
ArvoreB split(ArvoreB no, int* m);

// Funcao para buscar posicao de um elemento
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se encontrado no
int busca_pos(ArvoreB raiz, int info, int* pos);

// Funcao para verificar se um no eh folha
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se folha
int eh_folha(ArvoreB raiz);

// Funcao para verificar se houve overflow
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se um no estiver cheio
int overflow(ArvoreB raiz);

// Funcao para adicionar uma chave com um filho a um no
// Pre-condicao: nenhuma
// Pos-condicao: adiciona uma chave com um filho a um no e desloca os demais a direita se necessario
void adicionar_direita(ArvoreB raiz, int pos, int k, ArvoreB p);

// Funcao para inserir em arvore-B
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento na arvore
ArvoreB inserir(ArvoreB raiz, int info);

// Funcao auxiliar para inserir
// Pre-condicao: nenhuma
// Pos-condicao: utiliza as funcoes auxiliares para inserir determinado elemento
void inserir_aux(ArvoreB raiz, int info);

ArvoreB remover(ArvoreB raiz, int info);

// Funcao para imprimir em preOrdem
// Pre-condicao: arvore criada
// Pos-condicao: imprime os elementos da arvore em pre-ordenado
void preOrdem(ArvoreB raiz);

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: imprime todos os nos por niveis
void imprimir_por_niveis(ArvoreB raiz);

#endif // ARVORE_B_H_INCLUDED
