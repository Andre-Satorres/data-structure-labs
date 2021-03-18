#ifndef Heap_H
#define Heap_H
#include "Utils.h"

#define PAI(i) ((i - 1) / 2)
#define FILHO_ESQ(i) (2 * i + 1)
#define FILHO_DIR(i) (2 * i + 2)

typedef struct Heap {
    Any *v;
    int n, tamanho;
    int (*compara_chave)(Any, Any);
} Heap;

typedef Heap * p_heap;

/* Cria e retorna um novo Heap. 'compara_chave' é usada para comparar as chaves dos dados no Heap. */
p_heap criar_heap(int tamanho, size_t tamanho_do_dado, int (*compara_chave)(Any, Any));

/* Destroi o Heap passado por parâmetro. */
p_heap destruir_heap(p_heap fila_prioridade, void (*fdestroi)(Any));

/* Adiciona o x recebido por parâmetro no Heap usando fcopia para criar uma cópia de x. */
void adicionar_no_heap(p_heap fp, Any x, Any (*fcopia)(Any));

/* Remove do Heap o dado da posicao 'pos' usando fdestroi para liberá-lo da memória. */
void remover_do_heap(p_heap fila_prioridade, int pos, void (fdestroi)(Any));

/* Remove e retorna o dado de prioridade máxima do Heap. */
Any extrair_maximo(p_heap fila_prioridade);

/* Percorre o Heap retornando o índice do dado com um campo com valor 'campo', usando fcompara_campo para comparar tal campo. */
int buscar_posicao_por_campo(p_heap fila_prioridade, Any campo, int (fcompara_campo)(Any, Any));

/* Imprime o Heap na tela. */
void imprimir_heap(p_heap fila_prioridade, void (*fimprime)(Any));

#endif