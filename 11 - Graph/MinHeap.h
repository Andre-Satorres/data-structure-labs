#ifndef Min_Heap_H
#define Min_Heap_H
#include "Utils.h"

#define PAI(i) ((i - 1) / 2)
#define FILHO_ESQ(i) (2 * i + 1)
#define FILHO_DIR(i) (2 * i + 2)

typedef struct MinHeapNo {
    int indice;
    double prioridade;
} MinHeapNo;

typedef MinHeapNo * pMinHeapNo;

typedef struct minHeap {
    pMinHeapNo *vetor;
    int *posicao; // necessaria para alterar prioridade
    int n, tamanho;
} MinHeap;

typedef MinHeap * pMinHeap;

/* Cria e retorna um novo MinHeap. */
pMinHeap criarMinHeap(int tamanho);

/* Destroi o MinHeap passado por parâmetro. */
pMinHeap destruirMinHeap(pMinHeap minHeap);

/* Adiciona o No com valores indice e prioridade recebidos por parâmetro no MinHeap */
void adicionarNoMinHeap(pMinHeap minHeap, int indice, double prioridade);

/* Altera a prioridade do item com indice 'indice', atualizando-o com a prioridade novaPrioridade. */
void alterarPrioridade(pMinHeap minHeap, int indice, double novaPrioridade);

/* Remove e retorna o dado de prioridade mínima do MinHeap. */
pMinHeapNo extrairMinimo(pMinHeap minHeap);

/* Verifica se o dado com indice 'indice' está no minHeap. */
int estaNoMinHeap(pMinHeap minHeap, int indice);

/* Verifica se o minHeap está vazio, retornando 1 se sim e 0 caso contrário. */
int minHeapEstaVazio(pMinHeap minHeap);

/* Imprime o MinHeap na tela. */
void imprimirMinHeap(pMinHeap minHeap);

#endif