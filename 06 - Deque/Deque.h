#ifndef Deque_h
#define Deque_h

#include <stdlib.h>
#include "Utils.h"

typedef struct No {
    void *info;
    struct No *ant, *prox;
} No;

typedef No * p_no;

typedef struct Deque {
    p_no ini, fim;
} Deque;

typedef Deque * p_deque;

/* Iniciliza um Deque */
p_deque criar_deque();

/* Cria uma copia para o Deque passado por parametro e devolve a copia usando fcopia para copiar os infos. */
p_deque copiar_deque(p_deque deque, void *(*fcopia)(void *));

/* Compara dois deques usando fcompara para comparar os infos. */
int comparar_deque(p_deque d1, p_deque d2, int (*fcompara)(void *, void *));

/* Ordena um deque usando fcompara para comparar os infos. */
void ordenar_deque(p_deque deque, int (*fcompara)(void *, void *));

/* Destroi o Deque passado por parametro usando fdestroi para destruir os infos. */
void destruir_deque(p_deque deque, void (*fdestroi)(void *));

/* Devolve 0 (falso) se o deque não está vazio e != 0 (verdadeiro) se está vazio. */
int vazio(p_deque);

/* Retorna o campo info do primeiro No do Deque, ou NULL caso esteja vazio. */
void * primeiro(p_deque deque);

/* Retorna o campo info do último dado do Deque, ou NULL caso esteja vazio */
void * ultimo(p_deque deque);

/* Insere x no início do Deque usando fcopia para criar um dado independente do parametro. */
void inserir_no_inicio(void *x, p_deque deque, void *(*fcopia)(void *));

/* Insere x no fim do Deque usando fcopia para criar um dado independente do parametro. */
void inserir_no_fim(void *x, p_deque deque, void *(*fcopia)(void *));

/* Remove um item do início do Deque usando fdestroi para destruir o info. */
void remover_do_inicio(p_deque deque, void (*fdestroi)(void *));

/* Remove um item do fim do Deque usando fdestroi para destruir o info. */
void remover_do_fim(p_deque deque, void (*fdestroi)(void *));

/* Imprime um Deque na tela. */
void imprimir_deque(p_deque deque, void (*fptr)(void *));

/* Imprime um Deque na tela de trás para frente. */
void imprimir_contrario_deque(p_deque deque, void (*fptr)(void *));

#endif