#ifndef ARVORE_TST_H_
#define ARVORE_TST_H_

// Definicao de tipo de dado para armazenar o ponteiro principal
typedef struct no_tst* Tst;
// Definicao de tipo de dado para manipular o ponteiro principal
typedef struct no_tst Arv;

// Funcao para criacao de arvore Tst
// Pre-condicao: ponteiro criado
// Pos-condicao: retorna um ponteiro do tipo Tst
Tst *criar_arvore();

// Funcao para inserir nome na arvore
// Pre-condicao: arvore criada, vetor de char nao nulo
// Pos-condicao: nenhuma
void inserir_nome(Tst* arvore, char* palavra, int valor);

// Funcao para remover uma palavra da arvore
// Pre-condicao: arvore criada e vetor de char nao nulo
// Pos-condicao: nenhuma
void remover_palavra(Tst* arvore, char* palavra);

// Funcao para imprimir arvore Tst
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
void imprimir_arvore(Tst* arvore);

// Funcao para buscar nome inserindo nome
// Pre-condicao: arvore criada e vetor de char nao nulo
// Pos-condicao: nenhuma
void busca_arvore(Tst* arvore, char* palavra);

// Funcao para buscar nome inserindo valor
// Pre-condicao: arvore criada e valor valido
// Pos-condicao: nenhuma
void busca_dicionario(Tst* arvore, int valor);

// Funcao para liberar arvore Tst
// Pre-condicao: arvore criada
// Pos-condicao: nenhuma
Tst* liberar_arvore(Tst* arvore);

#endif // ARVORE_TST_H_
