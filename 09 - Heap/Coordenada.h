#ifndef Coordenada_H
#define Coordenada_H

typedef struct Coordenada {
    int x, y;
} Coordenada;

/* Cria uma nova Coordenada a partir de x e y dados. */
Coordenada nova_coordenada(int x, int y);

/* Calcula a distância de Manhattan entre duas Coordenadas. */
int distancia(Coordenada c1, Coordenada c2);

/* Imprime uma Coordenada na tela. */
void imprimir_coordenada(Coordenada c);

#endif