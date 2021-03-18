#include "Arvore_Binaria_de_Busca.h"

p_no novo_no() {
    p_no novo = novo_ponteiro(sizeof(No));
    novo->esq = novo->dir = NULL;
    novo->info = NULL;
    return novo;
}

void destruir_no(p_no raiz, void (*fdestroi)(void *)) {
    if(raiz) {
        fdestroi(raiz->info);
        free(raiz);
    }
}

p_no criar_abb() {
    return NULL;
}

p_no destruir_abb(p_no raiz, void (*fdestroi)(void *)) {
    if(raiz == NULL)
        return NULL;

    raiz->esq = destruir_abb(raiz->esq, fdestroi);
    raiz->dir = destruir_abb(raiz->dir, fdestroi);
    destruir_no(raiz, fdestroi);
    return NULL;
}

p_no minimo_absoluto(p_no raiz) {
    if(!raiz || !raiz->esq)
        return raiz;

    return minimo_absoluto(raiz->esq);
}

p_no maximo_absoluto(p_no raiz) {
    if(!raiz || !raiz->dir)
        return raiz;

    return maximo_absoluto(raiz->dir);
}

p_no buscar_na_abb(p_no raiz, void *x, int (*fcompara)(void *, void *)) {
    if(raiz == NULL)
        return NULL;

    int cmp = (*fcompara)(x, raiz->info);

    return cmp == 0 ? raiz : cmp < 0 ? buscar_na_abb(raiz->esq, x, fcompara) : buscar_na_abb(raiz->dir, x, fcompara);
}

p_no inserir_na_abb(p_no raiz, void *x, void *(*fcopia)(void *), int (*fcompara)(void *, void *)) {
    if(raiz == NULL) {
        raiz = novo_no();
        raiz->info = fcopia(x);
    } else {    
        int cmp = (*fcompara)(x, raiz->info);

        if(cmp < 0)
            raiz->esq = inserir_na_abb(raiz->esq, x, fcopia, fcompara);

        if(cmp > 0)
            raiz->dir = inserir_na_abb(raiz->dir, x, fcopia, fcompara);
    }

    return raiz;
}

p_no remover_da_abb(p_no raiz, void *x, void *(*fcopia)(void *), int (*fcompara)(void *, void *), void (*fdestroi)(void *)) {
    if(raiz == NULL)
        return NULL;

    int cmp = (*fcompara)(x, raiz->info);

    if(cmp < 0)
        raiz->esq = remover_da_abb(raiz->esq, x, fcopia, fcompara, fdestroi);
    else if(cmp > 0)
        raiz->dir = remover_da_abb(raiz->dir, x, fcopia, fcompara, fdestroi);
    else {
        p_no aux = raiz->esq == NULL ? raiz->dir : raiz->dir == NULL ? raiz->esq : NULL;
        
        if(!raiz->esq || !raiz->dir) { // só 1 ou nenhum filho
            destruir_no(raiz, fdestroi);
            return aux;
        }

        // 2 filhos
        aux = minimo_absoluto(raiz->dir); // menor dos maiores
        void *guarda = raiz->info;
        raiz->info = fcopia(aux->info);
        fdestroi(guarda);
        raiz->dir = remover_da_abb(raiz->dir, aux->info, fcopia, fcompara, fdestroi);
    }

    return raiz;
}

p_no maximo_menor_que(p_no raiz, void *x, int (*fcompara)(void *, void *)) {
    if(raiz == NULL)
        return NULL;

    int cmp = (*fcompara)(x, raiz->info);

    if(cmp <= 0) { // "x <= raiz->info" --> preciso pegar valores menores (esquerda)
        p_no maior_ate = maximo_menor_que(raiz->esq, x, fcompara);
        return maior_ate ? maior_ate : NULL; // NULL, pois raiz->info >= x, e quero só os info < x
    }

    // x > raiz->info --> continuar pegando maiores
    p_no maior_ate = maximo_menor_que(raiz->dir, x, fcompara);
    return maior_ate ? maior_ate : raiz;
}

p_no juntar_todos(p_no raiz, void *(*fjunta)(void *, void *), void (*fdestroi)(void *)) {
    if(raiz == NULL)
        return NULL;

    p_no ret = juntar_todos(raiz->esq, fjunta, fdestroi);

    if(ret) {
        void *guarda = raiz->info;
        raiz->info = fjunta(ret->info, raiz->info); // pois ret esta à esquerda de raiz
        raiz->esq = destruir_abb(raiz->esq, fdestroi);
        fdestroi(guarda);
    }

    ret = juntar_todos(raiz->dir, fjunta, fdestroi);
    if(ret) {
        void *guarda = raiz->info;
        raiz->info = fjunta(raiz->info,  ret->info); // pois ret esta à direita de raiz
        raiz->dir = destruir_abb(raiz->dir, fdestroi);
        fdestroi(guarda);
    }

    return raiz;
}

void imprimir_abb_rec(p_no raiz, int qtd_tabs, void (*fimprime)(void *)) { 
    if(raiz == NULL) 
        return; 

    qtd_tabs += 2;

    imprimir_abb_rec(raiz->dir, qtd_tabs, fimprime);   

    printf("\n"); 

    for (int i = 0; i < qtd_tabs - 2; i++) 
        printf("\t"); 

    fimprime(raiz->info);

    imprimir_abb_rec(raiz->esq, qtd_tabs, fimprime);
} 

void imprimir_abb(p_no raiz, void (*fimprime)(void *)) {
    printf("------------ ABB ------------");
    imprimir_abb_rec(raiz, 0, fimprime);
    printf("\n");
}