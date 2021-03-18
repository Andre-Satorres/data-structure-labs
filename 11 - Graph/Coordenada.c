#include "Coordenada.h"
#include <math.h>

Coordenada novaCoordenada(double x, double y) {
    Coordenada c;
    c.x = x;
    c.y = y;
    return c;
}

double distancia(Coordenada c1, Coordenada c2) {
    return sqrt(pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2));
}