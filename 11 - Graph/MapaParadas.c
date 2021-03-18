#include "MapaParadas.h"

void destruirParadaGenerico(Any p) {
    return destruirParada(p);
}

Any copiarParadaGenerico(Any p) {
    return copiarParada(p);
}

void imprimirParadaGenerico(Any p) {
    imprimirParada(p);
}

pMapaParadas criarMapaParadas() {
    pMapaParadas mapa = novoPonteiro(sizeof(MapaParadas));
    mapa->n = 0;
    mapa->paradas = criarListaLigada();
    return mapa;
}

void destruirMapaParadas(pMapaParadas mapa) {
    if(mapa == NULL)
        return;

    destruirListaLigada(mapa->paradas, destruirParadaGenerico);
    free(mapa);
}

void inserirParada(pMapaParadas mapa, pParada parada) {
    mapa->paradas = inserirNaLista(mapa->paradas, parada, copiarParadaGenerico);
    mapa->n++;
}

void imprimirMapa(pMapaParadas mapa) {
    printf("Mapa{n=%d, Paradas=", mapa->n);
    imprimirLista(mapa->paradas, imprimirParadaGenerico);
    printf("}");
}