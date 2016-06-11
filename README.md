# algoritmos-otimizacao

[![Public Domain](https://licensebuttons.net/p/zero/1.0/80x15.png)](http://creativecommons.org/publicdomain/zero/1.0/)

Trabalhos de Algoritmos de Otimização UNISC 2016

## Fluxo Máximo (max\_flow)

Para compilar o código do algoritmo de fluxo máximo não é necessária nenhuma biblioteca adicional. A maneira mais simples de compilar o projeto todo é com o comando

    $ gcc *.c -o max_flow

O programa espera ler a configuração do grafo (nodos, arestas e valores) da entrada padrão. Para executá-lo utilizando um arquivo como fonte de entrada dos dados, pode-se utilizar o comando

    $ ./max_flow < /caminho/do/arquivo.txt

A saída do programa é direcionada à saída padrão, e contém um log descrevendo todos os passos executados pelo algoritmo.


## Caixeiro Viajante (tsp)

Para compilar o código do problema do caixeiro viajante não é necessária nenhuma biblioteca adicional. A maneira mais simples de compilar o projeto todo é com o comando

    $ gcc *.c -o tsp

O programa espera ler os nodos do problema da entrada padrão. Para executá-lo utilizando um arquivo como fonte de entrada dos dados, pode-se utilizar o comando

    $ ./tsp < /caminho/do/arquivo.txt

A saída do programa é direcionada à saída padrão. Por padrão, apenas o resultado final é exibido. Para visualizar todos os passos executados pelo algoritmo, pode ser informada a flag verbose **-v** na execução do programa:

    $ ./tsp -v < /caminho/do/arquivo.txt


## TODO

- [ ] Makefiles para compilação dos programas
- [ ] Organizar saída do programa max\_flow (adicionar opção verbose)
- [ ] Descrever formatos dos arquivos de entrada utilizados

