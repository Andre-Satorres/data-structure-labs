#ifndef Numero_Legal_h
#define Numero_Legal_h
#include "Utils.h"

typedef struct Numero_Legal {
    unsigned long long numero;
    unsigned long long copias;
} Numero_Legal;

typedef Numero_Legal * p_numero_legal;

/* Cria um Numero_Legal com numero passado por parametro. */
p_numero_legal criar_numero_legal(unsigned long long numero);

/* Destroi o Numero_Legal n passado por parametro. */
void destruir_numero_legal(p_numero_legal n);

/* Compara os Numeros Legais n1 e n2 apenas pelo campo numero. Retorna 0 se sao iguais, < 0 se n1 < n2 e > 0 se n1 > n2. */
int comparar_numero_legal(p_numero_legal n1, p_numero_legal n2);

/* Compara um Numero Legal e um inteiro pelo campo 'numero'. Retorna 0 se sao iguais, 
* < 0 se numero < numero_legal->numero e > 0 se numero > numero_legal->numero. */
int comparar_numero_legal_com_numero(unsigned long long numero, p_numero_legal numero_legal);

/* cria e retorna um novo Numero_Legal que eh uma copia de n. */
p_numero_legal copiar_numero_legal(p_numero_legal n);

/* Atualiza o Numero_Legal antigo com a quantidade de copias contida em novo, caso seus numeros sejam iguais. */
void atualizar_numero_legal(p_numero_legal antigo, p_numero_legal novo);

/* Verifica se um Numero_Legal eh legal. */
int eh_legal(p_numero_legal n);

/* Imprime um Numero_Legal na tela. */
void imprimir_numero_legal(p_numero_legal n);

#endif