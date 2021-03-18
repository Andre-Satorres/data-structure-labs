#include "Lista_Legal.h"

Any copiar_numero_legal_generico(Any n) {
    return copiar_numero_legal(n);
}

int comparar_numero_legal_generico(Any n1, Any n2) {
    return comparar_numero_legal(n1, n2);
}

int comparar_numero_legal_com_numero_generico(Any numero, Any numero_legal) {
    return comparar_numero_legal_com_numero(*(unsigned long long *)numero, numero_legal);
}

void imprimir_numero_legal_generico(Any n) {
    imprimir_numero_legal(n);
}

void atualizar_numero_legal_generico(Any n1, Any n2) {
    atualizar_numero_legal(n1, n2);
}

void destruir_numero_legal_generico(Any n) {
    return destruir_numero_legal(n);
}

Lista_Legal criar_lista_legal() {
    return criar_abb();
}

Lista_Legal destruir_lista_legal(Lista_Legal l) {
    return destruir_abb(l, destruir_numero_legal_generico);
}

Lista_Legal inserir_numero_legal(Lista_Legal l, unsigned long long numero) {
    p_numero_legal n = criar_numero_legal(numero);
    l = inserir_na_abb(l, n, copiar_numero_legal_generico, comparar_numero_legal_generico, atualizar_numero_legal_generico);
    destruir_numero_legal(n);
    return l;
}

unsigned long long quantidade_ocorrencias(Lista_Legal l, unsigned long long numero) {
    p_no local = buscar_na_abb(l, &numero, comparar_numero_legal_com_numero_generico);

    if(local == NULL || local->info == NULL)
        return 0; // nao esta na 'Lista' de Numeros Legais

    p_numero_legal numero_legal = local->info;
    return numero_legal->copias;
}

int eh_lista_legal(Lista_Legal l) {
    if(l == NULL)
        return 1;

    return eh_lista_legal(l->esq) && eh_legal(l->info) && eh_lista_legal(l->dir);
}

int quantos_remover_para_ser_legal(Lista_Legal l) {
    if(l == NULL)
        return 0;

    p_numero_legal numero_legal = l->info;

    int quantos = 0;
    
    if(!eh_legal(numero_legal)) {
        quantos = numero_legal->copias - numero_legal->numero;

        if(quantos < 0)
            quantos = numero_legal->copias;
    }

    return quantos + quantos_remover_para_ser_legal(l->esq) + quantos_remover_para_ser_legal(l->dir);
}

void imprimir_lista_legal(Lista_Legal l) {
    imprimir_abb(l, imprimir_numero_legal_generico);
    printf("\n");
}