#ifndef Sala_de_Espera_Handler_h
#define Sala_de_Espera_Handler_h
#include "Paciente.h"

#define QTD_FILAS 10
#define DURACAO 10

enum Nome_Filas { AUXILIAR, CLINICO_GERAL, RADIOLOGISTA, ENFERMEIRO, OTORRINOLARINGOLOGISTA, PNEUMOLOGISTA, DERMATOLOGISTA, NEUROLOGISTA, ONCOLOGISTA, PSIQUIATRA };

typedef struct Fila_de_Espera {
    p_deque fila; // Deque de pacientes
    unsigned int qtd_profissionais; // qtd de profissionais disponiveis da especialidade
} Fila_de_Espera;

typedef Fila_de_Espera * p_fila_de_espera;

typedef struct Sala_de_Espera {
    p_fila_de_espera *filas_de_espera; // Vetor de ponteiros filas de espera
    unsigned int ciclos;
} Sala_de_Espera;

typedef Sala_de_Espera * p_sala_de_espera;

/* Cria uma Sala de Espera. */
p_sala_de_espera criar_sala_de_espera();

/* destroi a Sala de Espera recebido como parametro. */
void destruir_sala_de_espera(p_sala_de_espera sala);

/* Adiciona um novo Paciente na fila auxiliar da Sala de Espera para depois ser alocado à fila correta. */
void adicionar_paciente(p_sala_de_espera sala, p_paciente paciente);

/* Processa as filas de consultas da Sala para realizar as consultas de todos os Pacientes. */
void fazer_as_consultas(p_sala_de_espera sala);

/* Imprime a Sala de Espera na tela. */
void imprimir_sala(p_sala_de_espera sala);

#endif