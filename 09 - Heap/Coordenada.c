#include "Coordenada.h"
#include <stdlib.h>
#include <stdio.h>

Coordenada nova_coordenada(int x, int y) {
    Coordenada c;
    c.x = x;
    c.y = y;
    return c;
}

int distancia(Coordenada c1, Coordenada c2) {
    return abs(c1.x - c2.x) + abs(c1.y - c2.y);
}

void imprimir_coordenada(Coordenada c) {
    printf("(x=%d, y=%d)", c.x, c.y);
}