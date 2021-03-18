#include <stdio.h>
#include <string.h>
#include "Sala_de_Espera_Handler.h"

void ler_pacientes(p_sala_de_espera sala) {
    char *nome = novo_ponteiro(sizeof(char) * 51);
    char *prioridade = novo_ponteiro(sizeof(char) * 13);
    unsigned int eh_prioritario, codigo = 0;
    char id_fila;

    while(scanf(" \"%[^\"]\" ", nome) != EOF) {
        scanf("%s", prioridade);

        if(strcmp(prioridade, "preferencial") == 0)
            eh_prioritario = 1;
        else
            eh_prioritario = 0;
        
        p_paciente paciente = criar_paciente(codigo, nome, eh_prioritario);

        while(scanf("%c", &id_fila) != EOF) {
            if(id_fila == ' ')
                continue;

            if(id_fila < '1' || id_fila > '9')
                break;

            nova_consulta(paciente, id_fila - '0');
        }

        adicionar_paciente(sala, paciente);
        destruir_paciente(paciente);

        codigo++;
    }

    free(nome);
    free(prioridade);
}

int main() {
    p_sala_de_espera sala = criar_sala_de_espera();
    ler_pacientes(sala);
    fazer_as_consultas(sala);
    destruir_sala_de_espera(sala);
    return 0;
}