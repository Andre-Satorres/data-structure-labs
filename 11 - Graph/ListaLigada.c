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

pNo removerDaLista(pNo lista, Any dado, int (*fcompara)(Any, Any), void (*fdestroi)(Any)) {
    if(lista == NULL)
        return NULL;

    if(fcompara(lista->dado, dado) == 0) { // achei
        pNo prox = lista->prox;
        fdestroi(lista->dado);
        free(lista);
        return prox;
    }

    lista->prox = removerDaLista(lista, dado, fcompara, fdestroi);
    return lista;
}

int estaNaLista(pNo lista, Any dado, int (*fcompara)(Any, Any)) {
    for(pNo atual = lista; atual != NULL; atual = atual->prox)
        if(fcompara(atual->dado, dado) == 0) // achou
            return 1; // true

    return 0; // false
}

void imprimirLista(pNo lista, void (*fimprime)(Any)) {
    printf("[");
    for(pNo t=lista; t!=NULL; t=t->prox) {
        fimprime(t->dado);
        if(t->prox)
            printf(", ");
    }

    printf("]");
}