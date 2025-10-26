#ifndef ARVORE_AVL_H_
#define ARVORE_AVL_H_

#define maior(x, y) ((x) > (y) ? (x) : (y))

// Definicao de tipo para arvore AVL
typedef struct noAVL* arvoreAVL;
// Definicao de tipo booleano
typedef enum{false = 0, true = 1}boolean;

// Funcao para criar arvore AVL
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna arvore vazia
// Entrada: nenhuma
arvoreAVL* criar_arvore();

// Verificar se um no eh vazio
// Pre-condicao: nenhum
// Pos-condicao: retorna true se vazio
// Entrada: nó AVL
boolean vazia(struct noAVL*);

// Funcao para liberar arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro vazio
// Entrada: ponteiro para arvore AVL
void* liberar_arvore(arvoreAVL*);

// Funcao auxiliar para liberar arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: destroi nos da arvore
// Entrada: nó AVL
void liberar_no(struct noAVL*);

// Funcao para retornar altura do no
// Pre-condicao: arvore criada
// Pos-condicao: retorna altura da arvore
int altura_no(struct noAVL*);

// Funcao para retornar a diferenca de altura das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna diferenca de altura das subarvores
int fator_balanceamento(struct noAVL*);

// Funcao para procurar menor no das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna melhor valor da subarvore da esquerda
struct noAVL* procura_menor(struct noAVL*);

// Funcao para aplicar rotacao simples a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a direita
void rotacao_ll(arvoreAVL*);

// Funcao para aplicar rotacao simples a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a esquerda
void rotacao_rr(arvoreAVL*);

// Funcao para aplicar rotacao dupla a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a esquerda e outra para a direita
void rotacao_lr(arvoreAVL*);

// Funcao para aplicar rotacao dupla a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a direita e outra para a esquerda
void rotacao_rl(arvoreAVL*);

// Funcao para inserir elemento na arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int inserir(arvoreAVL*, int);

// Funcao para remover elemento da arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int remover(arvoreAVL*, int);

// Funcao para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore(arvoreAVL*);

// Funcao auxiliar para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: imprime em percurso pre-order
void imprimir_aux(struct noAVL*);

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: imprime os nos por niveis
void imprimir_niveis(arvoreAVL*);

#endif // ARVORE_AVL_H_
