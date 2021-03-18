#include "Arvore_Rubro_Negra.h"

p_no novo_no() {
    p_no novo = novo_ponteiro(sizeof(No));
    novo->esq = novo->dir = NULL;
    novo->info = NULL;
    return novo;
}

p_no novo_no_com(enum Cor cor, Any x, Any (*fcopia)(Any)) {
    p_no novo = novo_ponteiro(sizeof(No));
    novo->esq = novo->dir = NULL;
    novo->info = fcopia(x);
    novo->cor = cor;
    return novo;
}

void destruir_no(p_no raiz, void (*fdestroi)(Any)) {
    if(raiz) {
        fdestroi(raiz->info);
        free(raiz);
    }
}

int eh_vermelho(p_no x) {
    if(x == NULL)
        return 0;

    return x->cor == VERMELHO;
}

int eh_preto(p_no x) {
    if(x == NULL)
        return 1;

    return x->cor == PRETO;
}

p_no criar_abb() {
    return NULL;
}

p_no destruir_abb(p_no raiz, void (*fdestroi)(Any)) {
    if(raiz == NULL)
        return NULL;

    raiz->esq = destruir_abb(raiz->esq, fdestroi);
    raiz->dir = destruir_abb(raiz->dir, fdestroi);
    destruir_no(raiz, fdestroi);
    return NULL;
}

p_no rotaciona_para_esquerda(p_no raiz) {
    if(raiz == NULL)
        return NULL;

    if(raiz->dir == NULL)
        return raiz;
    
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no rotaciona_para_direita(p_no raiz) {
    if(raiz == NULL)
        return NULL;

    if(raiz->esq == NULL)
        return raiz;

    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no sobe_vermelho(p_no raiz) {
    if(raiz == NULL)
        return NULL;

    raiz->cor = VERMELHO;

    if(raiz->esq)
        raiz->esq->cor = PRETO;

    if(raiz->dir)
        raiz->dir->cor = PRETO;

    return raiz;
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

p_no corrigir_arvore(p_no raiz) {
    if(raiz == NULL)
        return NULL;

    if(eh_vermelho(raiz->dir) && eh_preto(raiz->esq))
        return rotaciona_para_esquerda(raiz);

    if(raiz->esq != NULL && eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq))
        return rotaciona_para_direita(raiz);

    if(eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir))
        return sobe_vermelho(raiz);

    return raiz;
}

p_no buscar_na_abb(p_no raiz, Any x, int (*fcompara)(Any, Any)) {
    if(raiz == NULL)
        return NULL;

    int cmp = (*fcompara)(x, raiz->info);

    return cmp == 0 ? raiz : cmp < 0 ? buscar_na_abb(raiz->esq, x, fcompara) : buscar_na_abb(raiz->dir, x, fcompara);
}

p_no inserir_na_abb_rec(p_no raiz, Any x, Any (*fcopia)(Any), int (*fcompara)(Any, Any), void (*fatualiza)(Any, Any)) {
    if(raiz == NULL)
        return novo_no_com(VERMELHO, x, fcopia);
 
    int cmp = (*fcompara)(x, raiz->info);

    if(cmp < 0)
        raiz->esq = inserir_na_abb_rec(raiz->esq, x, fcopia, fcompara, fatualiza);
    else if(cmp > 0)
        raiz->dir = inserir_na_abb_rec(raiz->dir, x, fcopia, fcompara, fatualiza);
    else
        fatualiza(raiz->info, x);

    raiz = corrigir_arvore(raiz);

    return raiz;
}

p_no inserir_na_abb(p_no raiz, Any x, Any (*fcopia)(Any), int (*fcompara)(Any, Any), void (*fatualiza)(Any, Any)) {
    raiz = inserir_na_abb_rec(raiz, x, fcopia, fcompara, fatualiza);
    raiz->cor = PRETO;
    return raiz;
}

p_no remover_da_abb(p_no raiz, Any x, Any (*fcopia)(Any), int (*fcompara)(Any, Any), void (*fdestroi)(Any)) {
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
        Any guarda = raiz->info;
        raiz->info = fcopia(aux->info);
        fdestroi(guarda);
        raiz->dir = remover_da_abb(raiz->dir, aux->info, fcopia, fcompara, fdestroi);
    }

    return raiz;
}

p_no maximo_menor_que(p_no raiz, Any x, int (*fcompara)(Any, Any)) {
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

p_no juntar_todos(p_no raiz, Any (*fjunta)(Any, Any), void (*fdestroi)(Any)) {
    if(raiz == NULL)
        return NULL;

    p_no ret = juntar_todos(raiz->esq, fjunta, fdestroi);

    if(ret) {
        Any guarda = raiz->info;
        raiz->info = fjunta(ret->info, raiz->info); // pois ret esta à esquerda de raiz
        raiz->esq = destruir_abb(raiz->esq, fdestroi);
        fdestroi(guarda);
    }

    ret = juntar_todos(raiz->dir, fjunta, fdestroi);
    if(ret) {
        Any guarda = raiz->info;
        raiz->info = fjunta(raiz->info,  ret->info); // pois ret esta à direita de raiz
        raiz->dir = destruir_abb(raiz->dir, fdestroi);
        fdestroi(guarda);
    }

    return raiz;
}

void imprimir_abb_rec(p_no raiz, int qtd_tabs, void (*fimprime)(Any)) { 
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

void imprimir_abb(p_no raiz, void (*fimprime)(Any)) {
    printf("------------ ABB ------------");
    imprimir_abb_rec(raiz, 0, fimprime);
    printf("\n");
}