#ifndef _ARVORE_RUBRO_NEGRA_H_INCLUDED
#define _ARVORE_RUBRO_NEGRA_H_INCLUDED

// Definicao de tipo para no rubro negro
typedef struct norb noRB;

// Definicao de estrutura para Arvore Rubro Negra
typedef struct{
    noRB* raiz;
    noRB* nil;
}ArvoreRB;

// Funcao para criar arvore rubro negra
// Pre-condicao: nenhuma
// Pos-condicao: retorna ponteiro para ArvoreRB
ArvoreRB* criar_arvore();

// Funcao auxiliar para buscar no
// Pre-condicao: nenhuma
// Pos-condicao: retorna endereco do valor buscado ou nulo
noRB* busca_aux(ArvoreRB* r, noRB* x, int chave);

// Funcao para buscar no
// Pre-condicao: arvore criada
// Pos-condicao: retorna no de busca_aux
noRB* busca(ArvoreRB* r, int info);

// Funcao para rotacionar para a esquerda
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona no x para a esquerda
void rotacao_esq(ArvoreRB* r, noRB* x);

// Funcao para rotacionar para a direita
// Pre-condicao: nenhuma
// Pos-condicao: rotaciona no y para a direita
void rotacao_dir(ArvoreRB* r, noRB* y);

// Funcao para auxiliar para inserir
// Pre-condicao: nenhuma
// Pos-condicao: insere em arvore rubro negra
void insereRB_aux(ArvoreRB* r, noRB* z);

// Funcao para inserir em arvore rubro negra
// Pre-condicao: arvore criada
// Pos-condicao: insere chave e retorna no inserido
noRB* inserir(ArvoreRB* r, int chave);

// Funcao para encontrar o minimo
// Pre-condicao: nenhuma
// Pos-condicao: encontra o menor valor da subarvore da direita
noRB* minimo(ArvoreRB* r, noRB* x);

// Funcao para encontrar sucessor
// Pre-condicao: nenhuma
// Pos-condicao: retorna no sucessor para o pai
noRB* sucessor(ArvoreRB* r, noRB* x);

// Funcao auxiliar para remover no
// Pre-condicao: nenhuma
// Pos-condicao: corrige possiveis violacoes antes da remocao
void removerRB_aux(ArvoreRB* r, noRB* x);

// Funcao cauda para remover no
// Pre-condicao: nenhuma
// Pos-condicao: remove no da arvore rubro negra
void removerRB(ArvoreRB* r, noRB* z);

// Funcao para remover no
// Pre-condicao: arvore criada
// Pos-condicao: remove no
void remover(ArvoreRB* r, int info);

// Funcao auxiliar para contar nos vermelhos
// Pre-condicao: nenhuma
// Pos-condicao: retorna numero de nos vermelhos
int contar_noVermelho_aux(ArvoreRB* r, noRB* x);

// Funcao para contar nos vermelhos
// Pre-condicao: arvore criada
// Pos-condicao: retorna valor da auxiliar
int contar_noVermelho(ArvoreRB* r);

// Funcao auxiliar para imprimir a arvore
// Pre-condicao: nenhuma
// Pos-condicao: imprime arvore
void pre_ordem_aux(ArvoreRB* r, noRB* x);

// Funcao para imprimir a arvore
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void preOrdem(ArvoreRB* r);

#endif // _ARVORE_RUBRO_NEGRA_H_INCLUDED
