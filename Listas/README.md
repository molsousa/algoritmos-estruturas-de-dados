## Lista Encadeada e Lista Encadeada em Arquivo

**Inserção:**
  - Cabeça: `O(1)`
  - Cauda: `O(n)`

**Remoção:**
  - Cabeça: `O(1)`
  - Cauda: `O(n)`

**Estrutura:**

- Lista Encadeada:
```C
struct no{
    TipoInfo info;   // Campo para informação
    struct no* prox; // Campo para próximo nó
};
```

- Lista Encadeada em Arquivo:
```C
typedef struct{
    int pos_cabeca; // Campo para o primeiro elemento da lista
    int pos_topo;   // Campo para o próximo índice disponível no arquivo
    int pos_livre;  // Campo para índices livres no arquivo
}Cabecalho;

typedef struct{
    TipoInfo info; // Campo para informação
    int prox;      // Campo para próximo índice
}No;
```

---

<img width="702" height="192" alt="ListaE" src="https://github.com/user-attachments/assets/471e93c2-becd-4f67-a4a7-73b0569966fb" />

## Fila e Fila em Arquivo

Permite inserir e remover em tempo constante, segue a lógica de *primeiro a entrar, primeiro a sair* (FIFO).

**Inserção:**
  - Cauda: `O(1)`

A inserção ocorre apenas no fim da lista.

**Remoção:**
  - Cabeça: `O(1)`

A remoção ocorre apenas no início da lista.

**Estrutura:**

- Fila:

```C
struct no{
    TipoInfo info;   // Campo para informação
    struct no* prox; // Campo para próximo nó
};

struct fila{
    struct no* inicio; // Campo para acessar nó do início da Fila
    struct no* fim;    // Campo para acessar nó do fim da Fila
};
```

- Fila em Arquivo:
```C
typedef struct{
    int pos_cabeca; // Campo para o primeiro índice da Fila
    int pos_ultimo; // Campo para o ultimo índice da Fila
    int pos_topo;   // Campo para o próximo índice disponível no arquivo
    int pos_livre;  // Campo para índices livres no arquivo
}Cabecalho;

typedef struct{
    TipoInfo info; // Campo para informação
    int prox;      // Campo para próximo índice
}No;
```

---

<img width="811" height="212" alt="Fila" src="https://github.com/user-attachments/assets/ad563fa3-0f85-4bae-8f42-cedefc98911b" />

## Pilha

Permite inserir e remover informações em tempo constante, segue a lógica de *último a entrar, primeiro a sair* (LIFO).

**Inserção:**
  - Cabeça: `O(1)`

A inserção ocorre apenas no início da lista.

**Remoção:**
  - Cabeça: `O(1)`

A remoção ocorre apenas no início da lista.

**Estrutura:**

- Pilha:

```C
struct no{
    TipoInfo info;   // Campo para informação
    struct no* prox; // Campo para próximo nó
};

struct fila{
    struct no* topo; // Campo para acessar elemento do início da Pilha
};
```

---

<img width="811" height="212" alt="Pilha" src="https://github.com/user-attachments/assets/581a97ec-5829-44d3-961c-df7a625c9e0f" />

## Lista Duplamente Encadeada

Permite percorrer os elementos da lista sem perder o nó anterior. Tem um potencial de facilitar a busca de elementos em determinada sequência sem reiniciar a busca.

**Estrutura:**

```C
struct no{
    TipoInfo info;   // Campo para informação
    struct no* ant   // Campo para nó anterior
    struct no* prox; // Campo para próximo nó
};
```

---

<img width="751" height="182" alt="ListaDE" src="https://github.com/user-attachments/assets/7bd075a0-5005-4e8b-a1c5-7762cbdfe83f" />

## Lista Duplamente Encadeada Circular

Permite percorrer os elementos da lista de forma circular e sem perder o nó anterior. Não é necessário ter uma "cabeça" pré-determinada, é possível parar em *x* nó e esse ser a nova "cabeça".

**Estrutura:**

```C
struct no{
    TipoInfo info;   // Campo para informação
    struct no* ant   // Campo para nó anterior
    struct no* prox; // Campo para próximo nó
};
```
---

<img width="751" height="182" alt="ListaDC" src="https://github.com/user-attachments/assets/dcbf366b-97da-4459-896b-e12b299b5c64" />

## Lista de Listas

Permite armazenar M listas de diferentes tamanhos cada uma.

**Estrutura:**

```C
struct no{
    TipoInfo info;   // Campo para informação
    struct no* prox; // Campo para próximo nó
};

struct no_listas{
    TipoIdentificador identificador; // Campo para encontrar lista buscada
    struct no* lista;                // Campo para lista encadeada
    struct no_listas* prox;          // Campo para próximo nó de lista de listas
}
```

---

<img width="561" height="401" alt="ListaL" src="https://github.com/user-attachments/assets/882eea90-e419-44d1-8f65-00191f352d9d" />
