#ifndef JORNADA_MESTRE_POKEMON_H
#define JORNADA_MESTRE_POKEMON_H

#include "GrafoMapa.h"

typedef struct Jornada {
    pGrafoMapa dados;
    char interesse[9];
} Jornada;

typedef Jornada * JornadaMestrePokemon;

/* Cria e retorna uma JornadaMestrePokemon na qual o nome ponto de interesse do jogador eh dado por 'interesse'. */
JornadaMestrePokemon criarJornadaMestrePokemon(char interesse[]);

/* Libera da memória uma JornadaMestrePokemon. */
void destruirJornadaMestrePokemon(JornadaMestrePokemon jornada);

/* Lê o mapa de pontos e o guarda na jornada. */
void lerMapa(JornadaMestrePokemon jornada);

/* Inicia a jornada. */
void iniciarJornada(JornadaMestrePokemon jornada);

/* Encontra um percurso da posição atual até um Lugia em que a maior distância entre duas paradas seja mínima e devolve esta distância em inteiro. */
int maiorDistanciaMinima(JornadaMestrePokemon jornada);

#endif