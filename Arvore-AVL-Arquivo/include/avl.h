#ifndef ARVORE_AVL_H_INCLUDED
#define ARVORE_AVL_H_INCLUDED

#include <stdio.h>

#define maior(x, y) ((x > y) ? (x) : (y))

// Definicao de estrutura para cabecalho
typedef struct{
    int pos_raiz;
    int pos_livre;
    int pos_topo;
}cabecalho;

// Definicao de estrutura para arvore AVL
typedef struct{
    int chave;
    int fb;
    int esq;
    int dir;
}no;

// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;

// Funcao para ler cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: nenhuma
// Entrada: arquivo de indice
cabecalho* ler_cabecalho(FILE*);

// Funcao para escrever cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: atualiza cabecalho
// Entrada: arquivo de indice
void escrever_cabecalho(FILE*, cabecalho*);

// Funcao para ler no
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, posicao do no
no* ler_no(FILE*, int);

// Funcao para escrever no
// Pre-condicao: arvore criada
// Pos-condicao: atualiza no
// Entrada: arquivo de indice, ponteiro para no, posicao do no
void escrever_no(FILE*, no*, int);

// Funcao para criar arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: cria arvore em arquivo binario
// Entrada: arquivo de indice
void inicializar(FILE*);

// Funcao para verificar se um no eh vazio
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: posicao do no
boolean vazia(int);

// Funcao para verificar altura da arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, posicao do no
int altura(FILE*, int);

// Funcao para verificar fator de balanceamento
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, ponteiro para no
int fator_balanceamento(FILE*, no*);

// Funcao para procurar menor valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, posicao do no
int procurar_menor(FILE*, int);

// Funcao para procurar maior valor da arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, posicao do no
int procurar_maior(FILE*, int);

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona o no a esquerda
// Entrada: arquivo de indice, posicao do no
int rotacaoLL(FILE*, int);

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona o no a direita
// Entrada: arquivo de indice, posicao do no
int rotacaoRR(FILE*, int);

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona duplamente o no alvo
// Entrada: arquivo de indice, posicao do no
int rotacaoLR(FILE*, int);

// Funcao para rotacionar subarvore
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona duplamente o no alvo
// Entrada: arquivo de indice, posicao do no
int rotacaoRL(FILE*, int);

// Funcao para inserir chave
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, chave a ser inserida
void inserir(FILE*, int);

// Funcao auxiliar para inserir chave
// Pre-condicao: nenhuma
// Pos-condicao: insere chave na arvore
// Entrada: arquivo de indice, chave a ser inserida, cabecalho, posicao do no
int inserir_aux(FILE*, int, cabecalho*, int);

// Funcao para remover chave
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, chave a ser removida
void remover(FILE*, int);

// Funcao auxiliar para remover chave
// Pre-condicao: nenhuma
// Pos-condicao: remove no buscado (se constar)
// Entrada: arquivo de indice, chave a ser removida, cabecalho, posicao do no
int remover_aux(FILE*, int, cabecalho*, int);

// Funcao para busca
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, chave buscada
boolean busca(FILE*, int);

// Funcao auxiliar para busca
// Pre-condicao: nenhuma
// Pos-condicao: retorna true se a chave constar
// Entrada: arquivo de indice, chave buscada, posicao do no
boolean busca_aux(FILE*, int, int);

// Funcao para imprimir arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice
void imprimir(FILE*);

// Funcao auxiliar para imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: arquivo de indice e posicao do no
void imprimir_aux(FILE*, int);

// Funcao para imprimir registros lvires
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice
void imprimir_livres(FILE*);

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice
void imprimir_niveis(FILE*);

#endif // ARVORE_AVL_H_INCLUDED
