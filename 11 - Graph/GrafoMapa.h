#ifndef GRAFO_MAPA_H
#define GRAFO_MAPA_H
#include "MapaParadas.h"
#include "Grafo.h"

typedef struct GrafoMapa {
    pMapaParadas mapaParadas;
    pGrafo grafoParadas;
    pNo indicesDeInteresse;
} GrafoMapa;

typedef int * Inteiro;

typedef GrafoMapa * pGrafoMapa;

/* Cria e retorna um GrafoMapa com saída em (xInicial, yInicial). */
pGrafoMapa criarGrafoMapa(double xInicial, double yInicial);

/* Libera da memoria o GrafoMapa passado por parametro. */
void destruirGrafoMapa(pGrafoMapa grafoMapa);

/* Insere uma nova Parada no Mapa de Paradas. */
void novaParada(pGrafoMapa grafoMapa, double x, double y, int ehDeInteresse);

/* Monta o Grafo de Paradas a partir do um Mapa de Paradas do GrafoMapa. */
void montarGrafo(pGrafoMapa grafoMapa);

/* Devolve o valor da maior aresta do caminho do vertice 0 ate um ponto de interesse cuja maior aresta é mínima. */
double maiorArestaMinimaDoCaminho(pGrafoMapa grafoMapa);

#endif