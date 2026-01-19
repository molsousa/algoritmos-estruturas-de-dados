#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED

// Definicao de tipo para lista encadeada simples
typedef struct lista Lista;

// Funcao para criar lista
// Pre-condicao: nenhuma
// Pos-condicao: retorna nulo para ponteiro do tipo Lista
Lista* criar_lista();

// Funcao para liberar lista
// Pre-condicao: lista valida
// Pos-condicao: libera todos os elementos da lista
void liberar_lista(Lista* l);

// Funcao para verificar se uma lista eh vazia
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se vazia
int vazia(Lista* l);

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento na cabeca
Lista* inserir_elemento(Lista* l, int info);

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento ao final da lista
Lista* inserir_elemento_cauda(Lista* l, int info);

// Funcao para inserir elemento
// Pre-condicao: lista criada
// Pos-condicao: insere elemento ordenado
Lista* inserir_elemento_ordenado(Lista* l, int info);

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove a primeira ocorrencia do elemento buscado
Lista* remover_elemento(Lista* l, int info);

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove a primeira ocorrencia do elemento buscado
Lista* remover_elemento_iterativo(Lista* l, int info);

// Funcao para remover elemento
// Pre-condicao: lista criada
// Pos-condicao: remove todas as ocorrencias do elemento buscado
Lista* remover_elemento_recorrencias(Lista* l, int info);

// Funcao para inverter lista
// Pre-condicao: lista criada
// Pos-condicao: retorna uma nova lista invertida
Lista* inverter_lista(Lista* l);

// Funcao para concatenar listas
// Pre-condicao: listas criadas
// Pos-condicao: retorna uma nova lista concatenada
Lista* concatenar_lista(Lista* l1, Lista* l2);

// Funcao para intercalar listas
// Pre-condicao: listas criadas
// Pos-condicao: retorna uma nova lista intercalada
Lista* intercalar_lista(Lista* l1, Lista* l2);

// Funcao para concatenar listas
// Pre-condicao: listas criadas
// Pos-condicao: concatena a lista 2 na lista 1
Lista* append(Lista* l1, Lista* l2);

// Funcao para contar ocorrencias
// Pre-condicao: lista criada
// Pos-condicao: retorna numero de ocorrencias de determinado elemento
int contar_ocorrencias(Lista* l, int info);

// Funcao para inverter lista
// Pre-condicao: lista criada
// Pos-condicao: retorna a lista original invertida
Lista* inverter_lista_original(Lista* l);

// Funcao para eliminar elementos repetidos
// Pre-condicao: lista criada
// Pos-condicao: elimina todas as ocorrencias repetidas
Lista* eliminar_repetidos(Lista* l);

// Funcao para contar elementos distintos
// Pre-condicao: lista criada
// Pos-condicao: retorna o numero total de elementos distintos
int contar_distintos(Lista* l);

// Funcao para verificar se um valor existe na lista
// Pre-condicao: lista criada
// Pos-condicao: retorna 1 se o valor existe na lista
int valor_existe(Lista* l, int info);

int contar_elementos(Lista* l);

Lista* merge_ord(Lista* l1, Lista* l2);

Lista* intercala(Lista* p, Lista* l1, Lista* l2, int n1, int n2);

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime na tela os elementos inseridos
void imprimir_lista(Lista* l);

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: imprime na tela os elementos inseridos de forma invertida
void imprimir_lista_invertido(Lista* l);

#endif // LISTA_ENCADEADA_H_INCLUDED
