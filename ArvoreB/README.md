## Arvore 2-3, Árvore 2-3 em Arquivo e Árvore 2-3 com ponteiro para pai

- Pode ser vista como uma Árvore Rubro Negra caída à esquerda ou direita.
- Novas chaves são inseridas nas folhas.
- Cada nó possui uma ou duas chaves.
- Cada nó interno possui dois ou três nós filhos.
- Complexidade de busca: `O(1)`.

**Estrutura:**

- Arvore 2-3:
```C
struct no23{
    TipoChave chave_esq; // Chave esquerda
    TipoChave chave_dir; // Chave direita
    struct no23* esq;    // Nó para encontrar chaves menores que a chave esquerda
    struct no23* meio;   // Nó para encontrar chaves menores que a chave direita
    struct no23* dir;    // Nó para encontrar chaves maiores que a chave direita
    int num_chaves;      // Números de chaves no nó atual
};
```

- Arvore 2-3 em Arquivo:

```C
typedef struct{
    int pos_raiz;   // Índice raiz da árvore
    int pos_topo;   // Índice novo para inserir no arquivo
    int pos_livre;  // Índice disponível a ser reaproveitado
}Cabecalho;

typedef struct{
    TipoChave chave_esq;  // Chave esquerda
    TipoChave chave_dir;  // Chave direita
    int esq;        // Índice para encontrar chaves menores que a chave esquerda
    int meio;       // Índice para encontrar chaves menores que a chave direita
    int dir;        // Índice para encontrar chaves maiores que a chave direita
    int num_chaves; // Números de chaves no índice atual
}No23;
```

- Arvore 2-3 com ponteiro para pai:

```C
struct no23{
    TipoChave chave_esq; // Chave esquerda
    TipoChave chave_dir; // Chave direita
    struct no23* esq;    // Nó para encontrar chaves menores que a chave esquerda
    struct no23* meio;   // Nó para encontrar chaves menores que a chave direita
    struct no23* dir;    // Nó para encontrar chaves maiores que a chave direita
    struct no23* pai;    // Nó para encontrar nó pai
    int num_chaves;      // Números de chaves no nó atual
};
```
---

<img width="982" height="372" alt="Arvore23" src="https://github.com/user-attachments/assets/880346b6-01df-44f1-ab57-9591863e17e4" />

## Árvore B e Árvore B em Arquivo

- Novas chaves são inseridas nas folhas.
- Cada página possui no máximo $\mathrm{ORDEM-1}$ chaves.
- Cada página possui no máximo $\mathrm{ORDEM}$ páginas filhas.
- Cada página interna possui no mínimo $\frac{ORDEM}{2}$.
- Todas as folhas estão no mesmo nível.
- Complexidade de busca: `O(1)`.

**Estrutura:**

- Árvore B:

```C
#define ORDEM 5

struct noB{
    TipoChaves[ORDEM];          // Chaves da página atual  
    struct noB* filho[ORDEM+1]; // Ponteiro para acessar páginas filhas
    int num_chaves;             // Número de chaves da página atual
};
```

Árvore B em Arquivo:

```C
#define ORDEM 5

typedef struct{
    int pos_raiz;   // Índice raiz da árvore
    int pos_topo;   // Índice novo para inserir no arquivo
    int pos_livre;  // Índice disponível a ser reaproveitado
}Cabecalho;

typedef struct{
    TipoChaves chaves[ORDEM];  // Chaves no índice atual
    int filho[ORDEM+1]; // Vetor de índices
    int num_chaves;     // Número de chaves no índice atual
}noB;

```

---

<img width="1122" height="222" alt="ArvoreB" src="https://github.com/user-attachments/assets/1220ecf2-9867-4fe8-a637-1745cdcc01a2" />


## Árvore B+

- Todas as chaves existentes estão nas folhas.
- As chaves em páginas internas são chaves índices para acesso às folhas.
- Cada página possui no máximo $\mathrm{ORDEM-1}$ chaves.
- Cada página possui no máximo $\mathrm{ORDEM}$ páginas filhas.
- As folhas são ligadas para permitir acesso sequencial.
- Um nó (exceto raiz) possuí pelo menos $\frac{ORDEM}{2}$ chaves.
- Todas as folhas estão no mesmo nível.
- Complexidade de busca: `O(1)`.
- Custo para acessar página folha vizinha: `O(1)` .

**Estrutura:**

```C
#define ORDEM 5

struct nodeBMais{
    TipoChave* chave;      // Chaves da página atual
    void** ponteiro;       // Ponteiro para acessar páginas inferiores ou páginas vizinhas se for folha
    short num_chaves;      // Número de chaves na página atual  
    int eh_folha;          // Inteiro para saber se a página atual é folha   
    struct nodeBMais* pai; // Nó para buscar a página pai
};
```

---

<img width="2032" height="412" alt="ArvoreB+" src="https://github.com/user-attachments/assets/39e7f2c0-abb4-4394-b3b4-7def40bac7b8" />
