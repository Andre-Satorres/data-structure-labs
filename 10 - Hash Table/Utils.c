#include "Utils.h"

void exibeMensagemErroEAborta() {
    printf("Sem memória suficiente! Abortando o programa ...");
    exit(567);
}

Any novoPonteiro(size_t tamanho) {
    Any p = malloc(tamanho);
    
    if(p == NULL)
        exibeMensagemErroEAborta();

    return p;
}

Any reallocaPonteiro(Any p, size_t tamanhoNovo) {
    p = realloc(p, tamanhoNovo);
    
    if(p == NULL)
        exibeMensagemErroEAborta();

    return p;
}