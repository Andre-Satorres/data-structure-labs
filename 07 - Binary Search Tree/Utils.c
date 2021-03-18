#include "Utils.h"

void * novo_ponteiro(size_t tamanho) {
    void *p = malloc(tamanho);
    
    if(!p) {
        printf("Sem memória suficiente! Abortando o programa ...");
        exit(567);
    }

    return p;
}