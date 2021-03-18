#ifndef Utils_h
#define Utils_h
#include <stdio.h>
#include <stdlib.h>

typedef void * Any;

/* Alloca na memoria e retorna um novo ponteiro de tamanho 'tamanho' bytes. */
Any novoPonteiro(size_t tamanho);

/* Realloca e retorna o ponteiro p dado, com tamanho novo de 'tamanhoNovo' bytes. */
Any reallocaPonteiro(Any p, size_t tamanhoNovo);

#endif