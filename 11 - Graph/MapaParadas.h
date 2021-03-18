#ifndef MapaParadas_H
#define MapaParadas_H
#include "Parada.h"
#include "ListaLigada.h"

typedef struct MapaParadas {
    pNo paradas;
    int n;
} MapaParadas;

typedef MapaParadas * pMapaParadas;

/* Cria e retorna um novo MapaParadas. */
pMapaParadas criarMapaParadas();

/* libera da memoria o MapaParadas recebido por parâmetro. */
void destruirMapaParadas(pMapaParadas mapa);

/* Insere uma nova Parada no MapaParadas. */
void inserirParada(pMapaParadas mapa, pParada parada);

/* Imprime o MapaParadas dado na tela. */
void imprimirMapa(pMapaParadas mapa);

#endif