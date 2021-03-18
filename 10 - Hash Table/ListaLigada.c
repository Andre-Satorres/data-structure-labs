#include <stdlib.h>
#include "Utils.h"
#include "ListaLigada.h"

pNo criarListaLigada() {
    return NULL;
}

pNo destruirListaLigada(pNo lista, void (*fdestroi)(Any)) {
    if(lista != NULL) {
        destruirListaLigada(lista->prox, fdestroi);
        fdestroi(lista->dado);
        free(lista);
    }

    return NULL;
}

pNo inserirNaLista(pNo lista, Any dado, Any (*fcopia)(Any)) {
    pNo novo = novoPonteiro(sizeof(No));
    novo->dado = fcopia(dado);
    novo->prox = lista;
    return novo;
}

int estaNaLista(pNo lista, Any dado, int (*fcompara)(Any, Any)) {
    for(pNo atual = lista; atual != NULL; atual = atual->prox)
        if(fcompara(atual->dado, dado) == 0) // achou
            return 1; // true

    return 0; // false
}