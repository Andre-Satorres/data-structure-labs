#ifndef Lista_Legal_h
#define Lista_Legal_h
#include "Arvore_Rubro_Negra.h"
#include "Numero_Legal.h"

/* ARVORE BINARIA DE BUSCA BALANCEADA DE Numero_Legal. */

typedef p_no Lista_Legal;

/* Cria uma Lista_Legal. */
Lista_Legal criar_lista_legal();

/* Destroi uma dada Lista_Legal. */
Lista_Legal destruir_lista_legal(Lista_Legal l);

/* Insere um Numero_Legal de numero 'numero' na Lista_Legal l dada. */
Lista_Legal inserir_numero_legal(Lista_Legal l, unsigned long long numero);

/* Verifica a quantidade de ocorrencias de 'numero' na Lista_Legal. */
unsigned long long quantidade_ocorrencias(Lista_Legal l, unsigned long long numero);

/* Verifica se uma dada Lista_Legal l é legal, ou seja, se para todo elemento x pertencente a l existirem exatamente x cópias de x. */
int eh_lista_legal(Lista_Legal l);

/* Devolve quantos elementos de uma dada lista l devem ser removidos para que ela se torne legal. */
int quantos_remover_para_ser_legal(Lista_Legal l);

/* Imprime uma dada Lista_Legal l na tela. */
void imprimir_lista_legal(Lista_Legal l);

#endif