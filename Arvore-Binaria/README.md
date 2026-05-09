## Árvore Binária e Árvore Binária em Arquivo

- No melhor caso, a busca, inserção e remoção ocorre em `O(log n)`.
- No pior caso, a busca, inserção e remoção ocorre em `O(n)`.
- Custo de implementação é baixo.
- A árvore pode crescer muito rapidamente e ser pouco eficiente em Arquivo.

**Estrutura:**

- Árvore Binária:
```C
struct no{
    TipoInfo info;  // Informação do nó atual
    struct no* esq; // Nó para acessar informação menor
    struct no* dir; // Nó para acessar informação maior
}
```

- Árvore Binária em Arquivo:
```C
typedef struct{
    int pos_raiz;  // Índice raiz da árvore
    int pos_topo;  // Índice novo para inserir no arquivo
    int pos_livre; // Índice disponível a ser reaproveitado
};

typedef struct{
    TipoInfo info; // Informação do índice atual
    int esq;       // Índice para acessar informação menor
    int dir;       // Índice para acessar informação maior
}No;
```
---

<img width="501" height="421" alt="ArvoreBinaria" src="https://github.com/user-attachments/assets/459c9cc1-42a6-4fcb-8dc8-4451b58c4400" />

## Árvore AVL e Árvore AVL em Arquivo

- A busca, inserção e remoção sempre ocorre em `O(log n)`.
- Cada nó possui uma altura de no máximo ou no mínimo 1 ou -1 respectivamente.
- Caso um nó esteja com altura 2, aplica-se balanceamento em todo caminho simples percorrido se necessário.
- O custo para balanceamento pode ser considerado alto em Arquivo.
- Custo de implementação é baixo.
- A árvore tende a demorar mais para crescer.

**Estrutura:**

- Árvore AVL:
```C
struct noAVL{
    TipoChave info; // Informação do nó atual
    int altura;     // Altura do índice atual
    struct no* esq; // Nó para acessar informação menor
    struct no* dir; // Nó para acessar informação maior
};
```

- Árvore AVL em Arquivo:
```C
typedef struct{
    int pos_raiz;  // Índice raiz da árvore
    int pos_topo;  // Índice novo para inserir no arquivo
    int pos_livre; // Índice disponível a ser reaproveitado
}Cabecalho;

typedef struct{
    TipoInfo info; // Informação do índice atual
    int altura;    // Altura do índice atual
    int esq;       // Índice para acessar informação menor
    int dir;       // Índice para acessar informação maior
}noAVL;
```

---

<img width="771" height="362" alt="ArvoreAVL" src="https://github.com/user-attachments/assets/f8e59e64-d31d-4135-bd92-4d554b1ce8b4" />


## Árvore Rubro Negra

- A busca, inserção e remoção sempre ocorre em `O(log n)`.
- A árvore rubro negra precisa seguir algumas regras específicas para sua implementação:
    * A raiz sempre é preta.
    * Todo caminho simples contém o mesmo número de nós pretos.
    * Todo nó vermelho possui dois nós pretos.
    * Todo nó vermelho possui um nó pai preto.
    * Toda folha é preta.
- Em algumas implementações é preferível usar o `NIL` um nó falso que serve pra demarcar o fim da árvore.
- O custo de implementação é mais alto que as demais.
- A árvore tende a demorar mais pra crescer.

**Estrutura:**
```C
struct noRB{
    TipoChave chave;           // Chave do nó atual
    enum{VERMELHO, PRETO} cor; // Enumeração para cor do nó atual
    struct noRB* esq;          // Nó para acessar informação menor
    struct noRB* dir;          // Nó para acessar informação maior
    struct noRB* pai;          // Nó para acessar nó pai
}
```
---

<img width="682" height="472" alt="ArvoreRB" src="https://github.com/user-attachments/assets/a5ebe0ef-b74c-4ba1-9014-531668440f70" />

## Árvore Rubro Negra Caída à Esquerda e Árvore Rubro Negra Caída à Esquerda em Arquivo

- A busca, inserção e remoção sempre ocorre em `O(log n)`.
- A árvore rubro negra caída à esquerda precisa seguir algumas regras específicas para sua implementação:
    * A raiz sempre é preta.
    * Todo caminho simples contém o mesmo número de nós pretos.
    * Os nós vermelhos só caem à esquerda.
    * Todo nó vermelho possui um pai e dois filhos pretos.
    * Toda folha é preta.
- Em algumas implementações é preferível usar o `NIL` um nó falso que serve pra demarcar o fim da árvore.
- Segue a mesma lógica da árvore rubro negra com um custo de implementação menor.

**Estrutura:**

- Árvore Rubro Negra Caída à Esquerda
```C
struct noRB{
    TipoChave chave;           // Chave do nó atual
    enum{VERMELHO, PRETO} cor; // Enumeração para cor do nó atual
    struct noRB* esq;          // Nó para acessar informação menor
    struct noRB* dir;          // Nó para acessar informação maior
}
```

- Árvore Rubro Negra Caída à Esquerda em Arquivo

```C

typedef struct{
    int pos_raiz; // Índice raiz da árvore
    int pos_topo; // Índice novo para inserir no arquivo
}cabecalho;


typedef struct{   
    int chave;                 // Chave do nó atual
    enum{VERMELHO, PRETO} cor; // Enumeração para cor do índice atual
    int esq;                   // Índice para acessar informação menor
    int dir;                   // Índice para acessar informação maior
}noRB;

```

---

<img width="661" height="582" alt="ArvoreRBCE" src="https://github.com/user-attachments/assets/9017f141-65e2-4d32-a6dc-eca88900c813" />
