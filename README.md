# Algoritmos e Estruturas de Dados em C

Esse repositório contém implementações de diversas estruturas de dados. Diferentes estruturas implementadas em memória e muitas delas em arquivo binário com lógica de remoção e reaproveitamento de posições livres.

## Motivação

- O repositório foi criado com objetivo único de acúmulo de conhecimento sobre Algoritmos e Estruturas de Dados.

- Todas as estruturas e algoritmos foram implementados em C.

## Sobre implementações em arquivo binário

- Com exceção da Árvore Rubro Negra Caída a Esquerda e Árvore B, todas as árvore reaproveitam nós livres para novas inserções após determinada remoção.

## Sobre as estruturas

- Especialmente AVL e Rubro Negra Caída a Esquerda aprendi com o professor André Backes.

- O restante foi durante o período de graduação e durante a matéria de Algoritmos e Estruturas de Dados.

## Sobre implementações em geral

- A Árvore B foi implementada considerando chaves de tamanho N, e com filhos N+1, isso facilita o split. Pois, tendo chaves N, e filhos N+1, é possível haver um overflow real, sem precisar simular e com isso avaliar e aplicar uma separação de páginas B.

- As Árvores Rubro Negra Caída à Esquerda funcionam com as mesmas regras da Rubro Negra padrão, com a única alteração que é ter nós vermelhos apenas na esquerda.
