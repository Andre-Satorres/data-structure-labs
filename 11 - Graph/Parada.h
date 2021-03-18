#ifndef PARADA_H
#define PARADA_H

#include "Coordenada.h"

enum TipoParada { SAIDA, PONTO, INTERESSE };

typedef struct Parada {
    Coordenada coordenada;
    int tipoParada;
} Parada;

typedef Parada * pParada;

/* Cria e retorna uma nova Parada. */
pParada criarParada(double x, double y, int tipoParada);

/* Libera da memoria a Parada recebida por parâmetro. */
void destruirParada(pParada parada);

/* Retorna uma copia da Parada dada. */
pParada copiarParada(pParada parada);

/* Verifica se a Parada fornecida eh do tipo INTERESSE. */
int ehDeInteresse(pParada parada);

/* Imprime a Parada na tela. */
void imprimirParada(pParada parada);

#endif