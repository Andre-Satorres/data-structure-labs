#ifndef Passageiro_H
#define Passageiro_H
#include "Coordenada.h"

#define MAX_NOME 16

typedef struct Passageiro {
    char nome[MAX_NOME];
    double estrelas; // dado unico --> será usado como chave
    Coordenada posicao;
    Coordenada destino;
} Passageiro;

typedef Passageiro * p_passageiro;

/* Cria um Passageiro a partir dos dados recebidos por parâmetro. */
p_passageiro criar_passageiro(char *nome, double estrelas, int posicao_x, int posicao_y, int destino_x, int destino_y);

/* Cria e retorna uma cópia para o Passageiro recebido como parâmetro. */
p_passageiro copiar_passageiro(p_passageiro p);

/* Compara dois Passageiros pelo campo estrelas. Retorna 0 se são iguais, 
* > 0 se p1 tem mais estrelas e < 0 se p2 tem mais estrelas. */
int comparar_por_estrelas(p_passageiro p1, p_passageiro p2);

/* Compara um Passageiro pelo seu campo 'nome' com o nome passado por parâmetro. 
* Retorna 0 se os nomes são iguais, > 0 se o nome do Passageiro > nome e < 0 caso contrário. */
int comparar_passageiro_com_campo_nome(p_passageiro p, char *nome);

/* Imprime um Passageiro na tela. */
void imprimir_passageiro(p_passageiro c);

#endif