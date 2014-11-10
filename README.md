ABB-Aumentada
=============

Implementação de uma Árvore Binária de Busca Aumentada.

A biblioteca faz uso de templates para suportar variados tipos, porém, no momento, funciona melhor
com inteiros.

Foi adicionado um campo *leftSize*, que armazena a quantidade de nós na subárvore esquerda, em cada
nó para implementar métodos extra que fazem parte de uma ABB Aumentada, como o *posicao()*.

O programa principal pode receber dois arquivos como parâmetros: o primeiro contendo os elementos
a serem inseridos na árvore e o segundo contendo os comandos. Também é possível executar o main
sem enviar arquivos por parâmetro.

Comando para compilação: **g++ *.cpp -o nomeDoExecutavel**

Comando para execução: **./nomeDoExecutavel arquivoDeEntrada arquivoDeComandos**

Os seguintes comandos são suportados:
* ENESIMO N
* POSICAO N
* MEDIANA
* CHEIA
* COMPLETA
* IMPRIMA
* REMOVA N

Exemplo:

IMPRIMA
MEDIANA
ENESIMO 10
