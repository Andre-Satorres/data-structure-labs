#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string.h>
#include "Utils.h"

typedef char * String;

/* Cria e retorna uma nova String de tamanho 'tamanho'. */
String criarString(int tamanho);

/* Realloca e retorna a String s para o tamanho 'novoTamanho'. */
String reallocaString(String s, size_t novoTamanho);

/* Retorna uma copia da String s dada. */
String copiarString(String s);

/* Verifica se a String s dada esta vazia. */
int estaVazia(String s);

/* Compara duas Strings, usando a funcao strcmp da biblioteca <string.h>. */
int compararString(String s1, String s2);

/* Calcula e retorna o hashCode de uma String dada, sendo max um valor limite para o hashCode. */
int stringHashCode(String str, int max);

#endif