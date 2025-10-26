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
// Pos-condicao: inicializa cabecalho
// Entrada: arquivo de indice
void criar_arvore(FILE*);

// Funcao para ler cabecalho
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna o cabecalho do arquivo
// Entrada: arquivo de indice
cabecalho* ler_cabecalho(FILE*);

// Funcao para escrever no cabecalho
// Pre-condicao: arquivo e cabecalho inicializados
// Pos-condicao: escreve no cabecalho
// Entrada: arquivo de indice, cabecalho
void escrever_cabecalho(FILE*, cabecalho*);

// Funcao para ler no
// Pre-condicao: arquivo inicializado
// Pos-condicao: retorna ponteiro para no
// Entrada: arquivo de indice, posicao do no
no* ler_no(FILE, int);

// Funcao para escrever no
// Pre-condicao: arquivo inicializado
// Pos-condicao: escreve no arquivo o no
// Entrada: arquivo de indice, ponteiro para no, posicao do no
void escrever_no(FILE*, no*, int);

// Funcao para retornar cor do no
// Pre-condicao: nenhuma
// Pos-condicao: retorna cor do no ou PRETO se for -1
// Entrada: arquivo de indice, posicao do no
int cor(FILE*, int);

// Funcao para rotacionar a esquerda
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao do no rotacionado para a esquerda
// Entrada: arquivo de indice, posicao do no
int rotacionar_esquerda(FILE*, int);

// Funcao para rotacionar a direita
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao do no rotacionado para a direita
// Entrada: arquivo de indice, posicao do no
int rotacionar_direita(FILE*, int);

// Funcao para trocar cor de nos da arvore
// Pre-condicao: nenhuma
// Pre-condicao: altera cor da raiz e dos dois filhos (se nao forem nulos)
// Entrada: arquivo de indice, posicao do no
void troca_cor(FILE*, int);

// Funcao auxiliar para inserir elemento
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento e aplica balanceamento de cores
// Entrada: arquivo de indice, cabecalho, chave a ser inserida, posicao do no
int inserir_aux(FILE*, cabecalho*, int, int);

// Funcao principal para inserir elemento
// Pre-condicao: arvore criada
// Pos-condicao: garante raiz preta
// Entrada: arquivo de indice, chave a ser inserida
void inserir(FILE*, int);

// Funcao auxiliar para buscar valor na arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna a posicao se encontrado o elemento, -1 se nao
// Entrada: arquivo de indice, chave buscada, posicao do no
int busca_aux(FILE*, int, int);

// Funcao para buscar valor na arvore
// Pre-condicao: nenhuma
// Pos-condicao: retorna a posicao se encontrado o elemento, -1 se nao
// Entrada: arquivo de indice, chave buscada
int busca(FILE*, int);

// Funcao para mover no a esquerda
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao da subarvore rotacionada para a esquerda e com balanceamento de cor
// Entrada: arquivo de indice, posicao do no
int mover_para_esquerda(FILE*, int);

// Funcao para mover no a direita
// Pre-condicao: nenhuma
// Pos-condicao: retorna posicao da subarvore rotacionada para a direita e com balanceamento de cor
// Entrada: arquivo de indice, posicao do no
int mover_para_direita(FILE*, int);

// Funcao auxiliar para balancear apos remocao
// Pre-condicao: nenhuma
// Pos-condicao: aplica balanceamento de cores onde for necessario
// Entrada: arquivo de indice, posicao do no
int balancear(FILE*, int);

// Funcao auxiliar para remover o no menor
// Pre-condicao: nenhuma
// Pos-condicao: remove o menor no da subarvore da direita
// Entrada: arquivo de indice, cabecalho, posicao do no
int remover_no_menor(FILE*, cabecalho*, int);

// Funcao auxiliar para encontrar o menor valor
// Pre-condicao: nenhuma
// Pos-condicao: encontra o no mais a esquerda da subarvore da direita
// Entrada: arquivo de indice, posicao do no
int procurar_menor(FILE*, int);

// Funcao auxiliar para remover elemento
// Pre-condicao: nenhuma
// Pos-condicao: remove o elemento encontrado e aplica o balanceamento de cores
// Entrada: arquivo de indice, cabecalho, chave a inserir, posicao do no
int remover_aux(FILE*, cabecalho*, int, int);

// Funcao principal para remover no
// Pre-condicao: arvore criada
// Pos-condicao: remove o elemento se encontrado
void remover(FILE*, int);

// Funcao auxiliar para imprimir arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore preOrdenada
// Entrada: arquivo de indice, posicao do no
void imprimir_preOrder(FILE*, int);

// Funcao auxiliar para imprimir arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore inOrder
// Entrada: arquivo de indice, posicao do no
void imprimir_inOrder(FILE*, int);

// Funcao auxiliar para imprimir arvore binaria
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore posOrder
// Entrada: arquivo de indice, posicao do no
void imprimir_posOrder(FILE*, int);

// Funcao para imprimir arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, ordem que deseja imprimir
void imprimir(FILE*, int);

// Funcao para imprimir arvore binaria
// Pre-condicao: arvore criada
// Pos-condicao: imprime arvore por niveis
// Entrada: arquivo de indice
void imprimir_niveis(FILE*);

// Funcao auxiliar para contar total de nos
// Pre-condicao: nenhuma
// Pos-condicao: retorna total de nos da arvore
// Entrada: arquivo de indice, posicao do no
int contar_nos_aux(FILE*, int);

// Funcao para contar total de nos
// Pre-condicao: arvore criada
// Pos-condicao: retorna total de nos da arvore
// Entrada: arquivo de indice
int contar_nos(FILE*);

// Funcao auxiliar para contar total de nos vermelhos
// Pre-condicao: nenhuma
// Pos-condicao: retorna total de nos vermelhos
// Entrada: arquivo de indice, posicao do no
int contar_vermelhos_aux(FILE*, int);

// Funcao para contar total de nos vermelhos
// Pre-condicao: arvore criada
// Pos-condicao: retorna total de nos vermelhos
// Entrada: arquivo de indice
int total_nos_vermelhos(FILE*);

#endif
