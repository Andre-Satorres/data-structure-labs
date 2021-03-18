#ifndef CORRETOR_ORTOGRAFICO_H
#define CORRETOR_ORTOGRAFICO_H

#include "Dicionario.h"

enum NivelCorrecao { VERDE, AMARELO, VERMELHO };

/* Retorna o Nivel de Correcao de 'palavra' usando o Dicionario 'dicionario'. */
int obterNivelCorrecao(Dicionario dicionario, String palavra);

#endif