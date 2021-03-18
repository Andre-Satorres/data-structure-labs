#include <stdio.h>
#include <string.h>
#include "Paciente.h"

void * copiar_int(void *p) {
    int *d = novo_ponteiro(sizeof(int));
    *d = *(int *)p;
    return d;
}

int comparar_int(void *p1, void *p2) {
    return *(int *)p1 - *(int *)p2;
}

void print_int(void *n) { 
   printf("%d", *(int *)n);
}

p_paciente criar_paciente(unsigned int codigo, char *nome, int eh_prioritario) {
    p_paciente paciente = novo_ponteiro(sizeof(Paciente));
    paciente->codigo = codigo;

    paciente->nome = novo_ponteiro(sizeof(char) * strlen(nome) + 1);
    paciente->nome = strcpy(paciente->nome, nome);
    
    paciente->eh_prioritario = eh_prioritario;
    paciente->consultas = criar_deque();

    return paciente;
}

p_paciente copiar_paciente(p_paciente paciente) {
    if(paciente == NULL)
        return NULL;

    p_paciente novo = criar_paciente(paciente->codigo, paciente->nome, paciente->eh_prioritario);
    free(novo->consultas); // pois o copiar_deque vai voltar um deque novo
    novo->consultas = copiar_deque(paciente->consultas, copiar_int);
    return novo;
}

int comparar_paciente(p_paciente paciente1, p_paciente paciente2) {
    if(paciente1 == NULL && paciente2 == NULL)
        return 0;

    if(paciente1 == NULL)
        return -1;

    if(paciente2 == NULL)
        return 1;

    if(paciente1->codigo != paciente2->codigo)
        return paciente1->codigo - paciente2->codigo;

    int cmp = strcmp(paciente1->nome, paciente2->nome);
    if(cmp != 0)
        return cmp;

    if(paciente1->eh_prioritario != paciente2->eh_prioritario)
        return paciente1->eh_prioritario - paciente2->eh_prioritario;

    return comparar_deque(paciente1->consultas, paciente2->consultas, comparar_int);
}

void destruir_paciente(p_paciente paciente) {
    free(paciente->nome);
    destruir_deque(paciente->consultas, free);
    free(paciente);
}

void nova_consulta(p_paciente paciente, int id_consulta) {
    inserir_no_fim(&id_consulta, paciente->consultas, copiar_int);
}

int proxima_consulta(p_paciente paciente) {
    if(vazio(paciente->consultas))
        return -1; // caso ja fez todas as consultas
        
    return *(int *)primeiro(paciente->consultas); // Devolve o id da consulta
}

int fazer_consulta(p_paciente paciente) {
    if(vazio(paciente->consultas))
        return -1;
        
    int id_consulta = *(int *)primeiro(paciente->consultas);
    remover_do_inicio(paciente->consultas, free);
    return id_consulta; // Devolve o id da fila
}

void imprimir_paciente(p_paciente paciente) {
    printf("Paciente(");
    printf("codigo=%d, ", paciente->codigo);
    printf("nome=%s, ", paciente->nome);
    printf("eh_prioritario=%d, ", paciente->eh_prioritario);
    printf("consultas=");
    imprimir_deque(paciente->consultas, print_int);
    printf(")");
}