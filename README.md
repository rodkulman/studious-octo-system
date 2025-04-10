# studious-octo-system

Repositório de apoio para trabalho do Grau A

## Descrição geral

Considere `n` cidades numeradas que estão interligadas por uma série de estradas de mão única. As ligações entre as cidades são representadas pelos elementos de uma matriz quadrada `L(n x n)`, cujos elementos `L[ij]` assumem o valor `1` ou `0`, conforme exista ou não estrada direta que saia da cidade `i` e chegue à cidade `j`. Assim, os elementos da linha `i` indicam as estradas que saem da cidade `i`, e os elementos da coluna `j` indicam as estradas que chegam à cidade `j`.

### Exemplo

Por convenção `L[ii]` = `1`. A figura mostra um exemplo para `n = 4`.

| Cidade  | 1 | 2 | 3 | 4 |
|---|---|---|---|---|
| **1** | 1 | 1 | 1 | 0 |
| **2** | 0 | 1 | 1 | 0 |
| **3** | 1 | 0 | 1 | 1 |
| **4** | 0 | 0 | 1 | 1 |

1. Dado `k`, determinar quantas estradas saem e quantas chegam à cidade `k`.
1. A qual das cidades chega o maior número de estradas?
1. Dado `k`, verificar se todas as ligações diretas entre a cidade `k` e outras são de mão dupla.
1. Relacionar as cidades que possuem saídas diretas para a cidade `k`.
1. Relacionar, se existirem:
    1. As cidades isoladas, isto é, as que não têm ligação com nenhuma outra;
    1. As cidades das quais não há saída, apesar de haver entrada;
    1. As cidades das quais há saída sem haver entrada.
1. Dada uma seqüência de `m` inteiros cujos valores estão entre `0` e `n-l`, verificar se é possível realizar o roteiro correspondente. No exemplo dado, o roteiro representado pela seqüência `(m=5) 2 3 2 1 0` é impossível.
1. Dados `k`e `p`, determinar se é possível ir da cidade `k` para a cidade `p` pelas estradas existentes.
1. Dado `k`, determinar se é possível, partindo de `k`, passar por todas as outras cidades apenas uma vez e retornar a `k`.
