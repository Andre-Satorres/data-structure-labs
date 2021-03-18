#include "Utils.h"

Any novo_ponteiro(size_t tamanho) {
    Any p = malloc(tamanho);
    
    if(!p) {
        printf("Sem memória suficiente! Abortando o programa ...");
        exit(567);
    }

    return p;
}