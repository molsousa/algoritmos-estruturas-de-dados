#ifndef _ARVORE_TST_23_H_INCLUDED
#define _ARVORE_TST_23_H_INCLUDED

// Definicao de tipo para arvore23
typedef struct no23* arvore23;

// Funcao para criar arvore23
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro Arvore23
arvore23 criar_arvore();

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
// Entrada: no a ser testado
int vazia(arvore23);

// Funcao para buscar na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o no buscado
// Entrada: raiz, chave a ser buscada
arvore23 busca(arvore23, int);

// Funcao auxiliar para inserir em 23
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
// Entrada: raiz, chave a ser adicionada, chave a ser promovida
arvore23 inserir_aux(arvore23, int, int*);

// Funcao para aplicar split em determinado no
// Pre-condicao: elemento na espera de ser inserido
// Pos-condicao: separa um no em dois
// Entrada: ponteiro a receber o split, chave a ser inserida, subarvore a ser adicionada, chave a ser promovida
arvore23 split(arvore23, int, arvore23, int*);

// Funcao para adicionar para adicionar chave
// Pre-condicao: nenhuma
// Pos-condicao: adiciona chave a esquerda ou a direita a depender do tamanho
// Entrada: no atual, chave a ser adicionada, ponteiro a ser adicionado
void adiciona_chave(arvore23, int, arvore23);

// Funcao que verifica se um no eh folha
// Pre-condicao: no nao nulo
// Pos-condicao: retorna 1 se folha
// Entrada: no a ser verificado
int eh_folha(arvore23);

// Funcao auxiliar para criar no23
// Pre-condicao: nenhuma
// Pos-condicao: retorna novo no
// Entrada: chave esquerda, chave direita, ponteiro esquerdo, ponteiro do meio, ponteiro direito, numero de chaves
arvore23 cria_no(int, int, arvore23, arvore23, arvore23, int);

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento
// Entrada: raiz, chave a inserir
arvore23 inserir(arvore23, int);

// Funcao para encontrar o menor no
// Pre-condicao: nenhuma
// Pos-condicao: retorna menor no a partir do no buscado
// Entrada: raiz
arvore23 encontrar_menor(arvore23);

// Funcao para verificar e tratar underflow
// Pre-condicao: removido o elemento
// Pos-condicao: verifica e corrige o balanceamento da arvore
// Entrada: no pai, posicao do filho com underflow
arvore23 tratar_underflow(arvore23, int);

// Funcao para redistribuir chaves
// Pre-condicao: remoção não ocasiona em merge e altera o balanceamento da arvore
// Pos-condicao: retorna ponteiro pai apos redistribuição
// Entrada: no pai, posicao do filho com underflow
arvore23 redistribuir(arvore23, int);

// Funcao para juntar dois nos
// Pre-condicao: elemento removido
// Pos-condicao: retorna no pai concatenado com outra chave descendente
// Entrada: no pai, posicao do filho com underflow
arvore23 merge(arvore23, int);

// Funcao auxiliar para remover elemento
// Pre-condicao: nenhuma
// Pos-condicao: remove elemento e rebalanceia a arvore se necessario
// Entrada: raiz, chave a remover
arvore23 remover_aux(arvore23, int);

// Funcao para remover elemento
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
// Entrada: raiz, chave a remover
arvore23 remover(arvore23, int);

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore em ordem na tela
// Entrada: raiz
void inOrdem(arvore23);

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore preOrdenada na tela
// Entrada: raiz
void preOrdem(arvore23);

// Funcao de imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime por niveis
// Entrada: raiz
void imprimir_niveis(arvore23);

#endif
