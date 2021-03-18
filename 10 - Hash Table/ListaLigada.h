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

/* Insere um dado no início da Lista Ligada dada, usando fcopia para criar uma copia de dado. */
pNo inserirNaLista(pNo lista, Any dado, Any (*fcopia)(Any));

/* Verifica se 'dado' está na Lista Ligada dada, usando fcompara para comparar os infos. */
int estaNaLista(pNo lista, Any dado, int (*fcompara)(Any, Any));

#endif
