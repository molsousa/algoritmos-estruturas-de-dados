#ifndef ARVORE_AVL_H_
#define ARVORE_AVL_H_

// Definicao de tipo para arvore AVL
typedef struct noAVL* arvoreAVL;

// Funcao para criar arvore AVL
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna arvore vazia
arvoreAVL* criar_arvore();

// Verificar se um no eh vazio
// Pre-condicao: nenhum
// Pos-condicao: retorna 1 se vazio
int vazia(struct noAVL* r);

// Funcao para liberar arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: retorna nulo para ponteiro vazio
void* liberar_arvore(arvoreAVL* raiz);

// Funcao auxiliar para liberar arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: destroi nos da arvore
void liberar_no(struct noAVL* r);

// Funcao para encontrar maior entre dois valores
// Pre-condicao: nenhuma
// Pos-condicao: retorna maior valor
int maior(int x, int y);

// Funcao para retornar altura do no
// Pre-condicao: arvore criada
// Pos-condicao: retorna altura da arvore
int altura_no(struct noAVL* no);

// Funcao para retornar a diferenca de altura das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna diferenca de altura das subarvores
int fator_balanceamento(struct noAVL* no);

// Funcao para procurar menor no das subarvores
// Pre-condicao: arvore criada
// Pos-condicao: retorna melhor valor da subarvore da esquerda
struct noAVL* procura_menor(struct noAVL* aux);

// Funcao para aplicar rotacao simples a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a direita
void rotacao_ll(arvoreAVL* raiz);

// Funcao para aplicar rotacao simples a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona duas vezes para a esquerda
void rotacao_rr(arvoreAVL* raiz);

// Funcao para aplicar rotacao dupla a esquerda
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a esquerda e outra para a direita
void rotacao_lr(arvoreAVL* raiz);

// Funcao para aplicar rotacao dupla a direita
// Pre-condicao: arvore criada, desbalanceada
// Pos-condicao: rotaciona uma vez para a direita e outra para a esquerda
void rotacao_rl(arvoreAVL* raiz);

// Funcao para inserir elemento na arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int inserir(arvoreAVL* raiz, int chave);

// Funcao para remover elemento da arvore AVL
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
int remover(arvoreAVL* raiz, int chave);

// Funcao para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void imprimir_arvore(arvoreAVL* raiz);

// Funcao auxiliar para imprimir arvore AVL
// Pre-condicao: nenhuma
// Pos-condicao: imprime em percurso pre-order
void imprimir_aux(struct noAVL* r);

// Funcao para imprimir por niveis
// Pre-condicao: arvore criada
// Pos-condicao: imprime os nos por niveis
void imprimir_niveis(arvoreAVL* r);

#endif // ARVORE_AVL_H_
