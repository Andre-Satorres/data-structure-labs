#ifndef ListaLigada_H
#define ListaLigada_H
#include "Utils.h"

typedef struct No {
    Any dado;
    struct No *prox;
} No;

typedef No * pNo;

/* Inicializa uma Lista Ligada. */
pNo criarListaLigada();

/* Destroi, liberando da memória, uma Lista Ligada. */
pNo destruirListaLigada(pNo lista, void (*fdestroi)(Any));

/* Insere um dado no ínicio da Lista Ligada dada, usando fcopia para criar uma copia de dado. */
pNo inserirNaLista(pNo lista, Any dado, Any (*fcopia)(Any));

/* Remove 'dado' da lista ligada dada, usando fcompara para comparar os dados e fdestroi para liberá-lo da memória. */
pNo removerDaLista(pNo lista, Any dado, int (*fcompara)(Any, Any), void (*fdestroi)(Any));

/* Verifica se 'dado' está na Lista Ligada dada, usando fcompara para comparar os infos. */
int estaNaLista(pNo lista, Any dado, int (*fcompara)(Any, Any));

/* Imprime uma Lista Ligada na tela. */
void imprimirLista(pNo lista, void (*fimprime)(Any));

#endif