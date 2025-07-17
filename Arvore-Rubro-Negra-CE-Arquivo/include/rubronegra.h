#ifndef _ARVORE_RUBRO_NEGRA_H_INCLUDED
#define _ARVORE_RUBRO_NEGRA_H_INCLUDED
#include <stdio.h>

// Estrutura para cabecalho
typedef struct{
    int pos_raiz;
    int pos_topo;
}cabecalho;

// Estrutura para no rubro negro
typedef struct{
    int chave;
    enum{VERMELHO, PRETO} cor;
    int esq;
    int dir;
}no;

// Funcao para criar uma arvore rubro negra
// Pre-condicao: nenhuma
// Pos-condicao: retorna o cabecalho inicializado
void criar_arvore(FILE* f);

// Funcao para ler cabecalho
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o cabecalho do arquivo
cabecalho* ler_cabecalho(FILE* f);

// Funcao para escrever no cabecalho
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: escreve no cabecalho
void escrever_cabecalho(FILE* f, cabecalho* cab);

// Funcao para ler no
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna ponteiro para no
no* ler_no(FILE* f, int pos);

// Funcao para escrever no
// Pre-condicao: arquivo inicializado
// Pos-condicao: escreve no arquivo o no
void escrever_no(FILE* f, no* x, int pos);

// Funcao para retornar cor do no
// Pre-condicao: nenhuma
// Pos-condicao: retorna cor do no ou PRETO se for -1
int cor(FILE* f, int pos);

// Funcao para rotacionar a esquerda
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao do no rotacionado para a esquerda
int rotacionar_esquerda(FILE* f, int pos);

// Funcao para rotacionar a direita
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao do no rotacionado para a direita
int rotacionar_direita(FILE* f, int pos);

// Funcao para trocar cor de nos da arvore
// Pre-condicao: nenhuma
// Pre-condicao: altera cor da raiz e dos dois filhos (se nao forem nulos)
void troca_cor(FILE* f, int pos);

// Funcao auxiliar para inserir elemento
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento e aplica balanceamento de cores
int inserir_aux(FILE* f, cabecalho* cab, int chave, int pos);

// Funcao principal para inserir elemento
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento na arvore e garante raiz preta
void inserir(FILE* f, int chave);

// Funcao auxiliar para buscar valor na arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna a posicao se encontrado o elemento, -1 se nao
int busca_aux(FILE* f, int chave, int pos);

// Funcao para buscar valor na arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna a posicao se encontrado o elemento, -1 se nao
int busca(FILE* f, int chave);

// Funcao para mover no a esquerda
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao da subarvore rotacionada para a esquerda e com balanceamento de cor
int mover_para_esquerda(FILE* f, int pos);

// Funcao para mover no a direita
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao da subarvore rotacionada para a direita e com balanceamento de cor
int mover_para_direita(FILE* f, int pos);

// Funcao auxiliar para balancear apos remocao
// Pre-condicao: nenhuma
// Pos-condicao: aplica balanceamento de cores onde for necessario
int balancear(FILE* f, int pos);

// Funcao auxiliar para remover o no menor
// Pre-condicao: nenhuma
// Pos-condicao: remove o menor no da subarvore da direita
int remover_no_menor(FILE* f, cabecalho* cab, int pos);

// Funcao auxiliar para encontrar o menor valor
// Pre-condicao: nenhuma
// Pos-condicao: encontra o no mais a esquerda da subarvore da direita
int procurar_menor(FILE* f, int pos);

// Funcao auxiliar para remover elemento
// Pre-condicao: nenhuma
// Pos-condicao: remove o elemento encontrado e aplica o balanceamento de cores
int remover_aux(FILE* f, cabecalho* cab, int chave, int pos);

// Funcao principal para remover no
// Pre-condicao: arvore criada
// Pos-condicao: remove o elemento se encontrado
void remover(FILE* f, int chave);

// Funcao auxiliar para imprimir arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore preOrdenada
void imprimir_preOrder(FILE* f, int pos);

// Funcao auxiliar para imprimir arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore inOrder
void imprimir_inOrder(FILE* f, int pos);

// Funcao auxiliar para imprimir arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore posOrder
void imprimir_posOrder(FILE* f, int pos);

// Funcao para imprimir arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir(FILE* f, int ordem);

// Funcao para imprimir arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: imprime arvore por niveis
void imprimir_niveis(FILE* f);

// Funcao auxiliar para contar total de nos
// Pre-condicao: nenhuma
// Pos-condicao: retorna total de nos da arvore
int contar_nos_aux(FILE* f, int pos);

// Funcao para contar total de nos
// Pre-condicao: arvore criada
// Pos-condicao: retorna total de nos da arvore
int contar_nos(FILE* f);

// Funcao auxiliar para contar total de nos vermelhos
// Pre-condicao: nenhuma
// Pos-condicao: retorna total de nos vermelhos
int contar_vermelhos_aux(FILE* f, int pos);

// Funcao para contar total de nos vermelhos
// Pre-condicao: arvore criada
// Pos-condicao: retorna total de nos vermelhos
int total_nos_vermelhos(FILE* f);

#endif
