#ifndef Paciente_h
#define Paciente_h
#include "Deque.h"

typedef struct Paciente {
    unsigned int codigo; // vai ser usado para ordenar
    char *nome;
    int eh_prioritario; // 0 se é normal e 1 se é prioritário
    p_deque consultas; // Deque de ints
} Paciente;

typedef Paciente * p_paciente;

/* Cria um Paciente a partir do codigo, nome e prioridade recebidos por parametro. */
p_paciente criar_paciente(unsigned int codigo, char *nome, int eh_prioritario);

/* cria e devolve uma copia para o Paciente recebido por parametro. */
p_paciente copiar_paciente(p_paciente paciente);

/* Devolve 0 se os dois Pacientes sao iguais, > 0 se p1 > p2 e < 0 se p1 < p2. */
int comparar_paciente(p_paciente paciente1, p_paciente paciente2);

/* Destroi o Paciente recebido por parametro. */
void destruir_paciente(p_paciente paciente);

/* Insere um novo id de consulta no deque de consultas do Paciente. */
void nova_consulta(p_paciente paciente, int id_consulta);

/* Devolve o id da proxima consulta que deve ser realizada pelo paciente, ou -1 se ele ja terminou. */
int proxima_consulta(p_paciente paciente);

/* Remove a proxima consulta do deque de consultas do Paciente e retorna o id. */
int fazer_consulta(p_paciente paciente);

/* Imprime o Paciente recebido por parametro. */
void imprimir_paciente(p_paciente paciente);

#endif