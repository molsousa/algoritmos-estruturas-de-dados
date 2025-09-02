#ifndef ARVORE_23_H_INCLUDED
#define ARVORE_23_H_INCLUDED

#include <stdio.h>

// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;

// Estrutura para cabecalho
typedef struct{
    int pos_raiz;
    int pos_topo;
    int pos_livre;
}cabecalho;

// Estrutura para no23
typedef struct{
    int chave_esq;
    int chave_dir;
    int esq;
    int meio;
    int dir;
    int num_chaves;
}no23;

// Funcao para ler cabecalho
// Pre-condicao: arvore criada
// Pos-condicao: retorna cabecalho
// Entrada: arquivo de indice
cabecalho* ler_cabecalho(FILE*);

// Funcao para escrever cabecalho
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, cabecalho
void escrever_cabecalho(FILE*, cabecalho*);

// Funcao para ler no
// Pre-condicao: arvore criada
// Pos-condicao: retorna no buscado
// Entrada: arquivo de indice, posicao do no
no23* ler_no(FILE*, int);

// Funcao para escrever no
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, no a ser escrito, posicao do no
void escrever_no(FILE*, no23*, int);

// Funcao para criar arvore23
// Pre-condicao: nenhuma
// Pos-condicao: inicializa cabecalho
// Entrada: arquivo de indice
void inicializar(FILE*);

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna verdadeiro se vazia
// Entrada: posicao do no
boolean vazia(int);

// Funcao para testar se um no eh folha
// Pre-condicao: arvore criada
// Pos-condicao: retorna verdadeiro se folha
// Entrada: arquivo de indice, posicao do no
boolean eh_folha(FILE*, int);

// Funcao para buscar na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o indice do no buscado
// Entrada: arquivo de indice, posicao do no raiz, chave a ser buscada
int busca(FILE*, int, int);

// Funcao para obter posicao livre
// Pre-condicao: nenhuma
// Pos-condicao: retorna nova posicao ou posicao reaproveitada
// Entrada: arquivo de indice, cabecalho
int obter_pos_livre(FILE*, cabecalho*);

// Funcao auxiliar para inserir em 23
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
// Entrada: arquivo de indice, posicao do no raiz, chave a ser inserida, chave a ser promovida, cabecalho
int inserir_aux(FILE*, int, int, int*, cabecalho*);

// Funcao para aplicar split em determinado no
// Pre-condicao: elemento na espera de ser inserido
// Pos-condicao: separa um no em dois
// Entrada: arquivo de indice, posicao do no pai, chave a ser adicionada, posicao da subarvore, chave a ser promovida, cabecalho
int split(FILE*, int, int, int, int*, cabecalho*);

// Funcao para adicionar para adicionar chave
// Pre-condicao: nenhuma
// Pos-condicao: adiciona chave a esquerda ou a direita a depender do tamanho
// Entrada: arquivo de indice, posicao do no raiz, chave a ser inserida, posicao a ser adicionada a direita
void adiciona_chave(FILE*, int, int, int);

// Funcao auxiliar para criar no23
// Pre-condicao: nenhuma
// Pos-condicao: retorna novo no
// Entrada: arquivo de indice, cabecalho, chave da esquerda, chave da direita,
// no esquerdo, no do meio, no direito, numero de chaves
int cria_no(FILE*, cabecalho*, int, int, int, int, int, int);

// Funcao para inserir elemento na arvore
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
// Entrada: arquivo de indice, chave a ser inserida, cabecalho, posicao do no raiz
int inserir_chave(FILE*, int, cabecalho*, int);

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, chave a ser inserida
void inserir(FILE*, int);

// Funcao para liberar posicao
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, cabecalho, posicao livre
void liberar_pos(FILE*, cabecalho*, int);

// Funcao para encontrar o menor no
// Pre-condicao: nenhuma
// Pos-condicao: retorna menor no a partir do no buscado
// Entrada: arquivo de indice, posicao do no raiz
int encontrar_menor(FILE*, int);

// Funcao para verificar e corrigir balanceamento
// Pre-condicao: removido o elemento
// Pos-condicao: verifica e corrige o balanceamento da arvore
// Entrada: arquivo de indice, cabecalho, posicao do no pai, situacao do no underflow
int corrigir_balanceamento(FILE*, cabecalho*, int, int);

// Funcao para redistribuir chaves
// Pre-condicao: remoção não ocasiona em merge e altera o balanceamento da arvore
// Pos-condicao: retorna ponteiro pai apos redistribuição
// Entrada: arquivo de indice, posicao do no pai, situacao do no underflow
int redistribuir(FILE*, int, int);

// Funcao para juntar dois nos
// Pre-condicao: elemento removido
// Pos-condicao: retorna no pai concatenado com outra chave descendente
// Entrada: arquivo de indice, cabecalho, posicao do no pai, situacao do no underflow
int merge(FILE*, cabecalho*, int, int);

// Funcao auxiliar para remover elemento
// Pre-condicao: nenhuma
// Pos-condicao: remove elemento e rebalanceia a arvore se necessario
// Entrada: arquivo de indice, chave a ser removida, posicao do no raiz, cabecalho
int remover_aux(FILE*, int, int, cabecalho*);

// Funcao para remover elemento
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice, chave a ser removida
void remover(FILE*, int);

// Funcao para verificar posicoes livres
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: arquivo de indice
void imprimir_livres(FILE*);

// Funcao de imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime por niveis
void imprimir_por_niveis(FILE*);

#endif // ARVORE_23_H_INCLUDED
