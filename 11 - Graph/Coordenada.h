#ifndef Coordenada_H
#define Coordenada_H

typedef struct Coordenada {
    double x, y;
} Coordenada;

/* Cria e retorna uma nova Coordenada Cartesiana (x, y). */
Coordenada novaCoordenada(double x, double y);

/* Calcula e retorna a distância entre duas Coordenadas. */
double distancia(Coordenada c1, Coordenada c2);

#endif