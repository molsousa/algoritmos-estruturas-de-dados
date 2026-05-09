## Árvore TRIE RWay

- Cada nó possui um vetor com o tamanho do alfabeto em ponteiros.
- O custo de implementação é menor que na TST, porém o custo de memória é muito elevado.
- Uma palavra completa é identificada pelo valor ao final da palavra.
- Pode ser escrita ou maiúscula ou minúscula a depender do valor ASCII pré-definido anteriormente.

**Estrutura:**

```C
#define ASCII_CODE 65
#define TAM_ALFABETO 26

struct noTRIE{
    struct noTRIE* filho[TAM_ALFABETO]; // Vetor de nós para acessar cada letra do alfabeto
    int valor;                          // Valor que define se uma palavra está completa
};

struct trie{
    struct noTRIE* raiz;                // Nó descritor para inicializar a árvore TRIE
};
```

---

<img width="771" height="622" alt="ArvoreRway" src="https://github.com/user-attachments/assets/d7a7149e-c83f-4e45-bc9b-2eca1a51c436" />

## Árvore TRIE TST

- As palavras não são escritas por complexo, são completadas a partir das anteriores.
- Não é necessário uma implementação com nó descritor.
- O custo de implementação é maior que a RWay, porém o custo de memória é consideravelmente menor.
- Uma palavra completa é identificada pelo valor ao final da palavra.
- Pode ser escrita toda minúscula ou maiúscula.

**Estrutura:**

```C
struct noTST{
    char letra;         // Letra do nó atual
    int valor;          // Valor que define se uma palavra está completa
    struct noTST* esq;  // Nó para acessar a letra menor que a do nó atual
    struct noTST* meio; // Nó para acessar a continuação da palavra vigente.
    struct noTST* dir;  // Nó para acessar a letra maior que a do nó atual
};
```

---

<img width="501" height="622" alt="ArvoreTST" src="https://github.com/user-attachments/assets/5585a927-64a2-41b0-be1b-f57fa9918ed2" />
