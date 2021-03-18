#include "Numero_Legal.h"

p_numero_legal criar_numero_legal(unsigned long long numero) {
    p_numero_legal novo = novo_ponteiro(sizeof(Numero_Legal));
    novo->numero = numero;
    novo->copias = 1;
    return novo;
}

void destruir_numero_legal(p_numero_legal n) {
    if(n != NULL)
        free(n);
}

int comparar_numero_legal(p_numero_legal n1, p_numero_legal n2) {
    if(n1 == n2)
        return 0;

    if(n1 == NULL)
        return -1;

    if(n2 == NULL)
        return 1;

    if(n1->numero > n2->numero)
        return 1;

    if(n1->numero < n2->numero)
        return -1;

    return 0;
}

int comparar_numero_legal_com_numero(unsigned long long numero, p_numero_legal numero_legal) {
    if(numero_legal == NULL)
        return 1;

    if(numero > numero_legal->numero)
        return 1;

    if(numero < numero_legal->numero)
        return -1;

    return 0;
}

p_numero_legal copiar_numero_legal(p_numero_legal n) {
    if(n == NULL)
        return NULL;

    p_numero_legal novo = criar_numero_legal(n->numero);
    novo->copias = n->copias;
    return novo;
}

void atualizar_numero_legal(p_numero_legal antigo, p_numero_legal novo) {
    if(novo == NULL || antigo == NULL)
        return;

    if(antigo->numero != novo->numero)
        return;

    antigo->copias += novo->copias;
}

int eh_legal(p_numero_legal n) {
    if(n == NULL)
        return 1;

    return n->numero == n->copias;
}

void imprimir_numero_legal(p_numero_legal n) {
    printf("Numero_Legal(");
    printf("numero=%llu, copias=%llu", n->numero, n->copias);
    printf(")");
}