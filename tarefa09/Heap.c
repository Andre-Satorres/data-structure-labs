#include "Heap.h"

p_heap criar_heap(int tamanho, size_t tamanho_do_dado, int (*compara_chave)(Any, Any)) {
    p_heap fila_prioridade = novo_ponteiro(sizeof(Heap));
    fila_prioridade->n = 0;
    fila_prioridade->tamanho = tamanho;
    fila_prioridade->compara_chave = compara_chave;
    fila_prioridade->v = novo_ponteiro(tamanho_do_dado * tamanho);
    return fila_prioridade;
}

p_heap destruir_heap(p_heap fila_prioridade, void (*fdestroi)(Any)) {
    if(fila_prioridade == NULL)
        return NULL;

    for(int i=0; i<fila_prioridade->n; i++)
        fdestroi(fila_prioridade->v[i]);

    free(fila_prioridade->v);
    free(fila_prioridade);
    return NULL;
}

void troca(Any *a, Any *b) {
    Any aux = *a;
    *a = *b;
    *b = aux;
}

int tem_filho_esq(p_heap fila_prioridade, int pos) {
    return FILHO_ESQ(pos) < fila_prioridade->n;
}

int tem_filho_dir(p_heap fila_prioridade, int pos) {
    return FILHO_DIR(pos) < fila_prioridade->n;
}

int maior_filho(p_heap fila_prioridade, int pos) {
    if(!tem_filho_esq(fila_prioridade, pos))
        return -1;

    if(!tem_filho_dir(fila_prioridade, pos))
        return FILHO_ESQ(pos);

    int compara_esq_dir = fila_prioridade->compara_chave(fila_prioridade->v[FILHO_ESQ(pos)], fila_prioridade->v[FILHO_DIR(pos)]);
    return compara_esq_dir >= 0 ? FILHO_ESQ(pos) : FILHO_DIR(pos);
}

void sobe_no_heap(p_heap fila_prioridade, int pos) {
    Any subindo = fila_prioridade->v[pos];

    while(pos > 0 && fila_prioridade->compara_chave(subindo, fila_prioridade->v[PAI(pos)]) > 0) {
        fila_prioridade->v[pos] = fila_prioridade->v[PAI(pos)];
        pos = PAI(pos);
    }

    fila_prioridade->v[pos] = subindo;
}

void desce_no_heap(p_heap fila_prioridade, int pos) {
    Any descendo = fila_prioridade->v[pos];
    int maior = maior_filho(fila_prioridade, pos);

    while(maior >= 0 && fila_prioridade->compara_chave(descendo, fila_prioridade->v[maior]) < 0) {
        fila_prioridade->v[pos] = fila_prioridade->v[maior];
        pos = maior;
        maior = maior_filho(fila_prioridade, pos);
    }

    fila_prioridade->v[pos] = descendo;
}

void adicionar_no_heap(p_heap fila_prioridade, Any c, Any (*fcopia)(Any)) {
    if(fila_prioridade == NULL || fila_prioridade->v == NULL || fila_prioridade->n >= fila_prioridade->tamanho)
        return;

    fila_prioridade->v[fila_prioridade->n] = fcopia(c);
    fila_prioridade->n++;
    sobe_no_heap(fila_prioridade, fila_prioridade->n - 1);
}

void remover_do_heap(p_heap fila_prioridade, int pos, void (fdestroi)(Any)) {
    if(fila_prioridade == NULL || fila_prioridade->v == NULL)
        return;

    troca(&fila_prioridade->v[pos], &fila_prioridade->v[fila_prioridade->n - 1]);
    fdestroi(fila_prioridade->v[fila_prioridade->n - 1]);
    fila_prioridade->n--;
    desce_no_heap(fila_prioridade, pos);
}

Any extrair_maximo(p_heap fila_prioridade) {
    if(fila_prioridade == NULL || fila_prioridade->v == NULL || fila_prioridade->n <= 0)
        return NULL;

    Any x = fila_prioridade->v[0];
    troca(&fila_prioridade->v[0], &fila_prioridade->v[fila_prioridade->n - 1]);
    fila_prioridade->n--;
    desce_no_heap(fila_prioridade, 0);
    return x;
}

int buscar_posicao_por_campo(p_heap fila_prioridade, Any campo, int (fcompara_campo)(Any, Any)) {
    if(fila_prioridade == NULL || fila_prioridade->v == NULL)
        return -1;

    for(int i=0; i<fila_prioridade->n; i++) {
        Any atual = fila_prioridade->v[i];
        if(fcompara_campo(atual, campo) == 0)
            return i;
    }
    
    return -1;
}

void imprimir_heap(p_heap fila_prioridade, void (*fimprime)(Any)) {
    printf("Heap={Clientes=[");
    for(int i=0; i<fila_prioridade->n; i++) {
        fimprime(fila_prioridade->v[i]);

        if(i < fila_prioridade->n - 1)
            printf(", ");
    }
    
    printf("], tamanho=%d}", fila_prioridade->tamanho);
}
