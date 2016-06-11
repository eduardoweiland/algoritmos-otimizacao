# algoritmos-otimizacao

[![Public Domain](https://licensebuttons.net/p/zero/1.0/80x15.png)](http://creativecommons.org/publicdomain/zero/1.0/)

Trabalhos de Algoritmos de Otimização UNISC 2016

## Fluxo Máximo (max\_flow)

Para compilar o código do algoritmo de fluxo máximo não é necessária nenhuma biblioteca adicional. A maneira mais simples de compilar o projeto todo é com o comando

    $ gcc *.c -o max_flow

O programa espera ler a configuração do grafo (nodos, arestas e valores) da entrada padrão. Para executá-lo utilizando um arquivo como fonte de entrada dos dados, pode-se utilizar o comando

    $ ./max_flow < /caminho/do/arquivo.txt

A entrada para o programa deve ser fornecida em texto simples. A primeira linha da entrada deve conter três números inteiros positivos **N**, **A** e **M**, onde **N** é o número de nodos do grafo, **A** é o número de arestas ligando todos os nodos do grafo e **M** é o maior número de arestas ligadas a um único nodo do grafo. Em seguida, deve haver **A** linhas, cada uma representando uma aresta do grafo e contendo três números inteiros positivos: **O** (1 <= O <= N), **D** (1 <= D <= N) e **V**, onde **O** é o número do nodo de origem da aresta, **D** é o número do nodo de destino e **V** é o valor disponível para transporte.

A saída do programa é direcionada à saída padrão, e contém um log descrevendo todos os passos executados pelo algoritmo.


## Caixeiro Viajante (tsp)

Para compilar o código do problema do caixeiro viajante não é necessária nenhuma biblioteca adicional. A maneira mais simples de compilar o projeto todo é com o comando

    $ gcc *.c -o tsp

O programa espera ler os nodos do problema da entrada padrão. Para executá-lo utilizando um arquivo como fonte de entrada dos dados, pode-se utilizar o comando

    $ ./tsp < /caminho/do/arquivo.txt

A entrada para o programa deve ser fornecida em texto simples. A primeira linha da entrada deve conter um único número inteiro positivo **Q** que representa a quantidade de nodos do grafo. Em seguida, deve haver **Q** linhas, cada uma representando um nodo do grafo e contendo um número inteiro positivo **N** (1 <= N <= Q) e dois números reais positivos **X** e **Y**, onde **N** é o número do nodo e **X** e **Y** são a posição do nodo em um plano cartesiano.

A saída do programa é direcionada à saída padrão. Por padrão, apenas o resultado final é exibido. Para visualizar todos os passos executados pelo algoritmo, pode ser informada a flag verbose **-v** na execução do programa:

    $ ./tsp -v < /caminho/do/arquivo.txt


## TODO

- [ ] Makefiles para compilação dos programas

