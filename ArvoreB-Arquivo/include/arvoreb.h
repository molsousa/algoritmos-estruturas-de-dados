#ifndef _ARVORE_B_H_INCLUDED
#define _ARVORE_B_H_INCLUDED

#include <stdio.h>

#define ORDEM 7
#define MIN_CHAVES ((ORDEM-1)/2)

// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;

// Estrutura para cabecalho
typedef struct{
    int pos_livre;
    int pos_raiz;
    int pos_topo;
}cabecalho;

// Estrutura para pagina de arvore-B
typedef struct{
    int num_chaves;
    int chaves[ORDEM];
    int filhos[ORDEM+1];
}noB;

// Funcao para escrever no cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, cabecalho
void escrever_cabecalho(FILE*, cabecalho*);

// Funcao para ler cabecalho
// Pre-condicao: cabecalho inicializado
// Pos-condicao: retorna cabecalho na condicao atual
// Entrada: arquivo de indice
cabecalho* ler_cabecalho(FILE*);

// Funcao para escrever em pagina B
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, pagina B, posicao da pagina
void escrever_no(FILE*, noB*, int);

// Funcao para ler pagina B
// Pre-condicao: nenhuma
// Pos-condicao: retorna pagina B na condicao atual
// Entrada: arquivo de indice, posicao da pagina B
noB* ler_no(FILE*, int);

// Funcao para inicializar arquivo binario
// Pre-condicao: nenhuma
// Pos-condicao: cria cabecalho
// Entrada: arquivo de indice
void inicializar(FILE*);

boolean vazia(int);

boolean eh_folha(FILE*, int);

// Funcao para verificar se houve overflow
// Pre-condicao: nenhuma
// Pos-condicao: retorna verdadeiro se um no estiver cheio
// Entrada: arquivo de indice, posicao da pagina B
boolean overflow(FILE*, int);

// Funcao para separar paginas
// Pre-condicao: arvore criada
// Pos-condicao: retorna posicao da pagina separada
// Entrada: arquivo de indice, posicao da pagina B, chave sucessora, cabecalho
int split(FILE*, int, int*, cabecalho*);

// Funcao para buscar posicao para inserir um elemento
// Pre-condicao: nenhuma
// Pos-condicao: retorna 1 se encontrado no
// Entrada: arquivo de indice, posicao da pagina B, chave a ser inserida, posicao buscada
int busca_pos(FILE*, int, int, int*);

// Funcao para adicionar uma chave com um filho a uma pagina
// Pre-condicao: nenhuma
// Pos-condicao: adiciona uma chave com um filho a uma pagina e desloca as demais a direita se necessario
// Entrada: arquivo de indice, posicao da pagina B, posicao da chave, valor de chave, posicao de determinado ponteiro (inclusive nulo)
void adicionar_direita(FILE*, int, int, int, int);

// Funcao para inserir em arvore-B
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, chave a ser inserida
void inserir(FILE*, int);

// Funcao para inserir em arvore-B
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento na arvore
// Entrada: arquivo de indice, chave a ser inserida, cabecalho e posicao da pagina raiz
int inserir_chave(FILE*, int, cabecalho*, int);

// Funcao auxiliar para inserir
// Pre-condicao: nenhuma
// Pos-condicao: utiliza as funcoes auxiliares para inserir determinado elemento
// Entrada: arquivo de indice, chave a ser inserida, cabecalho e posicao de determinada pagina
void inserir_aux(FILE*, int, cabecalho*, int);

boolean underflow(FILE*, int);

void remover(FILE*, int);

int remover_aux(FILE*, int, cabecalho*, int);

int tratar_underflow(FILE*, int, int, cabecalho*);

int obter_pos_livre(FILE*, cabecalho*);

void liberar_pos(FILE*, cabecalho*, int);

void posicoes_livres(FILE*);

// Funcao para imprimir arvore em linha
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice
void imprimir(FILE*);

// Funcao auxiliar para imprimir em preOrdem
// Pre-condicao: nenhuma
// Pos-condicao: imprime os elementos da arvore em pre-ordenado
// Entrada: arquivo de indice, posicao de determinada pagina
void imprimir_aux(FILE*, int);

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: imprime todos os nos por niveis
// Entrada: arquivo de indice
void imprimir_niveis(FILE*);

#endif // _ARVORE_B_H_INCLUDED
