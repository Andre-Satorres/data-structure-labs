#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "HashTable.h"
#include "StringUtils.h"

typedef pHashTable Dicionario;

/* Cria e retorna um novo Dicionario de tamanho 'tamanho'. */
Dicionario criarDicionario(int tamanho);

/* Libera da memoria o Dicionario dado. */
void destruirDicionario(Dicionario dicionario);

/* Adiciona no Dicionario dado a palavra 'palavra'. */
void guardarNoDicionario(Dicionario dicionario, String palavra);

/* Verifica se a palavra 'palavra' está no Dicionario dado. */
int estaNoDicionario(Dicionario dicionario, String palavra);

#endif