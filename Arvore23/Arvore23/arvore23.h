#ifndef ARVORE_TST_23_H_INCLUDED
#define ARVORE_TST_23_H_INCLUDED

// Definicao de tipo para arvore23
typedef struct no* Arvore23;

// Funcao para criar arvore23
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro Arvore23
Arvore23 criar_arvore();

// Funcao para verificar se uma arvore eh vazia
// Pre-condicao: arvore criada
// Pos-condicao: retorna 1 se vazia
int vazia(Arvore23 raiz);

// Funcao para buscar na arvore
// Pre-condicao: arvore criada
// Pos-condicao: retorna o no buscado
Arvore23 busca(Arvore23 raiz, int chave);

// Funcao auxiliar para inserir em 23
// Pre-condicao: nenhuma
// Pos-condicao: insere elemento
Arvore23 inserir_aux(Arvore23 raiz, int chave, int* chave_promovida);

// Funcao para aplicar split em determinado no
// Pre-condicao: elemento na espera de ser inserido
// Pos-condicao: separa um no em dois
Arvore23 split(Arvore23 p, int chave, Arvore23 subarvore, int* chave_promovida);

// Funcao para adicionar para adicionar chave
// Pre-condicao: nenhuma
// Pos-condicao: adiciona chave a esquerda ou a direita a depender do tamanho
void adiciona_chave(Arvore23 raiz, int chave, Arvore23 p);

// Funcao que verifica se um no eh folha
// Pre-condicao: no nao nulo
// Pos-condicao: retorna 1 se folha
int eh_folha(Arvore23 p);

// Funcao auxiliar para criar no23
// Pre-condicao: nenhuma
// Pos-condicao: retorna novo no
Arvore23 cria_no(int chave_esq, int chave_dir, Arvore23 esq, Arvore23 meio, Arvore23 dir, int num_chaves);

// Funcao para inserir elemento na arvore
// Pre-condicao: arvore criada
// Pos-condicao: insere elemento
Arvore23 inserir(Arvore23 raiz, int chave);

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore em ordem na tela
void inOrdem(Arvore23 raiz);

// Funcao para imprimir arvore23
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore preOrdenada na tela
void preOrdem(Arvore23 raiz);

// Funcao de imprimir arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime por niveis
void imprimir_niveis(Arvore23 raiz);

#endif // ARVORE_TST_2_3_H_INCLUDED
