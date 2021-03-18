#include "Utils.h"
#include "Parada.h"

pParada criarParada(double x, double y, int tipoParada) {
    pParada nova = novoPonteiro(sizeof(Parada));
    nova->coordenada = novaCoordenada(x, y);
    nova->tipoParada = tipoParada;
    return nova;
}

void destruirParada(pParada parada) {
    if(parada != NULL)
        free(parada);
}

pParada copiarParada(pParada parada) {
    return criarParada(parada->coordenada.x, parada->coordenada.y, parada->tipoParada);
}

int ehDeInteresse(pParada parada) {
    if(parada == NULL)
        return 0; // FALSE
        
    return parada->tipoParada == INTERESSE;
}

void imprimirParada(pParada parada) {
    if(parada != NULL) {
        printf("Parada{(%lf, %lf), tipoParada=%d}", parada->coordenada.x, parada->coordenada.y, parada->tipoParada);
    }
}