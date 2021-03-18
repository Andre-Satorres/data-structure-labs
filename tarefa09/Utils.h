#ifndef Utils_h
#define Utils_h
#include <stdio.h>
#include <stdlib.h>

typedef void * Any;

/* Aloca espaço na memória para um ponteiro genérico de tamanho 'tamanho' e o retorna. */
Any novo_ponteiro(size_t tamanho);

#endif