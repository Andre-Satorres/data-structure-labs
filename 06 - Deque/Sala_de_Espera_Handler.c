#include <stdio.h>
#include "Sala_de_Espera_Handler.h"

int comparar_paciente_generico(void *p1, void *p2) {
    return comparar_paciente(p1, p2);
}

void * copiar_paciente_generico(void *paciente) {
    return copiar_paciente(paciente);
}

void destruir_paciente_generico(void *p) {
    destruir_paciente(p);
}

void imprimir_paciente_generico(void  *p) {
    imprimir_paciente(p);
}

void criar_nova_fila_espera(p_sala_de_espera sala, int id, unsigned int qtd_profissionais) {
    if(id < 0 || id > QTD_FILAS) {
        printf("Id inválido!");
        exit(1);
    }

    p_fila_de_espera fila_espera = novo_ponteiro(sizeof(Fila_de_Espera));
    fila_espera->fila = criar_deque();
    fila_espera->qtd_profissionais = qtd_profissionais;
    sala->filas_de_espera[id] = fila_espera;
}

p_sala_de_espera criar_sala_de_espera() {
    p_sala_de_espera sala = novo_ponteiro(sizeof(Sala_de_Espera));
    sala->filas_de_espera = novo_ponteiro(sizeof(p_fila_de_espera) * QTD_FILAS);
    sala->ciclos = 0;

    criar_nova_fila_espera(sala, AUXILIAR, 0); // esta fila 0 será usada de auxiliar, apenas
    criar_nova_fila_espera(sala, CLINICO_GERAL, 10);
    criar_nova_fila_espera(sala, RADIOLOGISTA, 2);
    criar_nova_fila_espera(sala, ENFERMEIRO, 5);
    criar_nova_fila_espera(sala, OTORRINOLARINGOLOGISTA, 3);
    criar_nova_fila_espera(sala, PNEUMOLOGISTA, 4);
    criar_nova_fila_espera(sala, DERMATOLOGISTA, 7);
    criar_nova_fila_espera(sala, NEUROLOGISTA, 2);
    criar_nova_fila_espera(sala, ONCOLOGISTA, 1);
    criar_nova_fila_espera(sala, PSIQUIATRA, 4);

    return sala;
}

void destruir_sala_de_espera(p_sala_de_espera sala) {
    for(int i=0; i<QTD_FILAS; i++) {
        destruir_deque(sala->filas_de_espera[i]->fila, destruir_paciente_generico);
        free(sala->filas_de_espera[i]);
    }

    free(sala->filas_de_espera);
    free(sala);
}

void imprimir_saida(p_sala_de_espera sala, p_paciente paciente) {
    int horas, minutos;
    minutos = sala->ciclos * DURACAO; // quantos atendimentos a pessoa teve * a duração de cada atendimento
    horas = 8; // comeca 8 da manha
    horas += minutos / 60;
    horas %= 24; // em caso passe de 24hrs
    minutos %= 60; // depois de contabilizar as horas

    if(horas < 10)
        printf("0");
    printf("%d:", horas);

    if(minutos < 10)
        printf("0");
    printf("%d ", minutos);

    printf("%s\n", paciente->nome);
}

void inserir_paciente_na_fila(p_sala_de_espera sala, p_paciente paciente) {
    int id = fazer_consulta(paciente); // remove a consulta atual da lista de consultas do paciente

    if(id == -1) { // paciente ja terminou todas as suas consultas
        imprimir_saida(sala, paciente);
        return;
    }

    p_deque fila_da_consulta = sala->filas_de_espera[id]->fila;
    
    if(paciente->eh_prioritario) {
        inserir_no_inicio(paciente, fila_da_consulta, copiar_paciente_generico);
    } else {
        inserir_no_fim(paciente, fila_da_consulta, copiar_paciente_generico);
    }
}

void processar_fila_auxiliar(p_sala_de_espera sala) {
    p_deque fila_aux = sala->filas_de_espera[AUXILIAR]->fila;

    ordenar_deque(fila_aux, comparar_paciente_generico); // para corrigir desempate

    while(!vazio(fila_aux)) {
        p_paciente paciente = primeiro(fila_aux);
        inserir_paciente_na_fila(sala, paciente);
        remover_do_inicio(fila_aux, destruir_paciente_generico);
    }
}

void inserir_na_fila_auxiliar(p_sala_de_espera sala, p_paciente paciente) {
    p_deque fila_auxiliar = sala->filas_de_espera[AUXILIAR]->fila;
    inserir_no_fim(paciente, fila_auxiliar, copiar_paciente_generico);
}

void adicionar_paciente(p_sala_de_espera sala, p_paciente paciente) { // melhor para o cliente chamar uma funcao "adicionar_paciente" do que "inserir_na_fila_auxiliar"
    inserir_na_fila_auxiliar(sala, paciente);
}

void fazer_todas_consultas_fila(p_sala_de_espera sala, int id) {
    p_fila_de_espera f = sala->filas_de_espera[id];
    
    if(f == NULL)
        return;

    for(int i=0; i < f->qtd_profissionais; i++) {
        if(vazio(f->fila))
            return;
        
        p_paciente paciente = primeiro(f->fila);
        inserir_na_fila_auxiliar(sala, paciente);
        remover_do_inicio(f->fila, destruir_paciente_generico);
    }
}

void fazer_as_consultas(p_sala_de_espera sala) {
    p_deque fila_aux = sala->filas_de_espera[AUXILIAR]->fila;
    while(!vazio(fila_aux)) {
        processar_fila_auxiliar(sala);
        for(int i=0; i<QTD_FILAS; i++) {
            fazer_todas_consultas_fila(sala, i);
        }

        sala->ciclos++;
    }
}

void imprimir_fila_de_espera(p_fila_de_espera f, int id) {
    printf("Fila_de_Espera(pacientes=");
    imprimir_deque(f->fila, imprimir_paciente_generico);
    printf(", id=%d, qtd_profs=%d", id, f->qtd_profissionais);
    printf(")");
}

void imprimir_sala(p_sala_de_espera sala) {
    printf("Sala_de_Espera(");
    printf("ciclos=%d, ", sala->ciclos);
    printf("filas=[");
    
    for(int i=0; i<QTD_FILAS; i++) {
        imprimir_fila_de_espera(sala->filas_de_espera[i], i+1);

        if(i < QTD_FILAS - 1)
            printf(", ");
    }

    printf("])\n");
}