#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Deque.h"

p_no novo_no() {
    p_no novo = novo_ponteiro(sizeof(No));
    novo->prox = novo->ant = NULL;
    return novo;
}

p_deque criar_deque() {
    p_deque deque = novo_ponteiro(sizeof(Deque));
    deque->ini = deque->fim = NULL;
    return deque;
}

p_deque copiar_deque(p_deque deque, void *(*fcopia)(void *)) { 
    if (deque == NULL)
        return NULL; 

    p_deque novo = criar_deque();
    for(p_no atual = deque->ini; atual; atual = atual->prox)
        inserir_no_fim(atual->info, novo, fcopia);
        
    return novo;
} 

int comparar_deque(p_deque d1, p_deque d2, int (*fcompara)(void *, void *)) {
    if(d1 == NULL && d2 == NULL)
        return 0;

    if(d1 == NULL) 
        return -1;

    if(d2 == NULL) 
        return 1;

    p_no atual1 = d1->ini;
    p_no atual2 = d2->ini;

    while(atual1 && atual2) {
        int cmp = (*fcompara)(atual1->info, atual2->info);
        if(cmp != 0)
            return cmp;

        atual1 = atual1->prox;
        atual2 = atual2->prox;
    }

    return atual1 == NULL ? -1 : atual2 == NULL ? 1 : 0;
}

void ordenar_deque(p_deque deque, int (*fcompara)(void *, void *)) {  
    p_no atual = NULL, indice = NULL;  
    void *temp;

    if(deque->ini == NULL)
        return;
 
    for(atual = deque->ini; atual->prox != NULL; atual = atual->prox) {  
        for(indice = atual->prox; indice != NULL; indice = indice->prox) {
            int cmp = (*fcompara)(atual->info, indice->info);
            if(cmp > 0) {
                temp = atual->info;
                atual->info = indice->info;
                indice->info = temp;
            }
        }  
    }
} 

void destruir_deque(p_deque deque, void (*fdestroi)(void *)) {
    if(deque == NULL)
        return;

    p_no atual = deque->ini;

    while(atual) {
        p_no prox = atual->prox;
        (*fdestroi)(atual->info);
        free(atual);
        atual = prox;
    }

    free(deque);
}

int vazio(p_deque deque) {
    return deque == NULL || deque->ini == NULL;
}

void * primeiro(p_deque deque) {
    return vazio(deque) ? NULL : deque->ini->info;
}

void * ultimo(p_deque deque) {
    return vazio(deque) ? NULL : deque->fim->info;
}

void inserir_em_vazio(p_deque deque, p_no novo) {
    if(deque == NULL)
        deque = criar_deque();

    deque->ini = novo; // prox e ant ficaram NULL em "novo_no"
    deque->fim = deque->ini;
}

void inserir_no_inicio(void *x, p_deque deque, void *(*fcopia)(void *)) {
    p_no novo = novo_no();
    novo->info = (*fcopia)(x);
    
    if(vazio(deque)) {
        inserir_em_vazio(deque, novo);
    } else {
        novo->prox = deque->ini;
        novo->prox->ant = novo;
        deque->ini = novo;
    }
}

void inserir_no_fim(void *x, p_deque deque, void *(*fcopia)(void *)) {
    p_no novo = novo_no();
    novo->info = (*fcopia)(x);
    
    if(vazio(deque)) {
        inserir_em_vazio(deque, novo);
    } else {
        novo->ant = deque->fim;
        novo->ant->prox = novo;
        deque->fim = novo;
    }
}

void remover_do_inicio(p_deque deque, void (*fdestroi)(void *)) {
    if(vazio(deque)) {
        printf("Underflow!!\n");
        exit(1);
    }

    p_no a_remover = deque->ini;
    deque->ini = a_remover->prox;

    if(deque->ini) { // se n vai ficar vazio apos remover
        deque->ini->ant = NULL;
    } else {
        deque->fim = deque->ini = NULL;
    }

    (*fdestroi)(a_remover->info);
    free(a_remover);
}

void remover_do_fim(p_deque deque, void (*fdestroi)(void *)) {
    if(vazio(deque)) {
        printf("Underflow!!\n");
        exit(1);
    }

    p_no a_remover = deque->fim;
    deque->fim = a_remover->ant;

    if(deque->fim) { // se ainda n ta vazio
        deque->fim->prox = NULL;
    } else {
        deque->ini = deque->fim = NULL;
    }

    (*fdestroi)(a_remover->info);
    free(a_remover);
}

void imprimir_deque(p_deque deque, void (*fptr)(void *)) {
    printf("[");
    if(deque != NULL) {
        p_no atual = deque->ini;

        while (atual) { 
            (*fptr)(atual->info); 
            atual = atual->prox;

            if(atual)
                printf(", ");
        } 
    }

    printf("]");
}

void imprimir_contrario_deque(p_deque deque, void (*fptr)(void *)) {
    printf("[");
    if(deque != NULL) {
        p_no atual = deque->fim;

        while (atual) { 
            (*fptr)(atual->info); 
            atual = atual->ant;
        }

        if(atual)
            printf(", ");
    }

    printf("]");
}
