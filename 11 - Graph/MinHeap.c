#include "MinHeap.h"

pMinHeapNo criarMinHeapNo(int indice, double prioridade) {
    pMinHeapNo novo = novoPonteiro(sizeof(MinHeapNo));
    novo->indice = indice;
    novo->prioridade = prioridade;
    return novo;
}

int compararMinHeapNo(pMinHeapNo n1, pMinHeapNo n2) {
    if(n1 == n2)
        return 0;

    if(n1 == NULL)
        return -1;

    if(n2 == NULL)
        return 1;

    if(n1->prioridade < n2->prioridade)
        return -1;

    if(n1->prioridade > n2->prioridade)
        return 1;

    return 0;
}

pMinHeap criarMinHeap(int tamanho) {
    pMinHeap minHeap = novoPonteiro(sizeof(MinHeap));
    minHeap->n = 0;
    minHeap->tamanho = tamanho;
    minHeap->vetor = novoPonteiro(sizeof(MinHeapNo) * tamanho);
    minHeap->posicao = novoPonteiro(sizeof(int) * tamanho);
    return minHeap;
}

pMinHeap destruirMinHeap(pMinHeap minHeap) {
    if(minHeap == NULL)
        return NULL;

    for(int i=0; i<minHeap->n; i++)
        free(minHeap->vetor[i]);

    free(minHeap->vetor);
    free(minHeap->posicao);
    free(minHeap);
    return NULL;
}

void troca(pMinHeap minHeap, pMinHeapNo *a, pMinHeapNo *b) {
    pMinHeapNo aux = *a;
    int posAux = minHeap->posicao[(*a)->indice];
    
    minHeap->posicao[(*a)->indice] = minHeap->posicao[(*b)->indice];
    minHeap->posicao[(*b)->indice] = posAux;

    *a = *b;
    *b = aux;
}

int temFilhoEsq(pMinHeap minHeap, int pos) {
    return FILHO_ESQ(pos) < minHeap->n;
}

int temFilhoDir(pMinHeap minHeap, int pos) {
    return FILHO_DIR(pos) < minHeap->n;
}

int menorFilho(pMinHeap minHeap, int pos) {
    if(!temFilhoEsq(minHeap, pos))
        return -1;

    if(!temFilhoDir(minHeap, pos))
        return FILHO_ESQ(pos);

    int comparaEsqDir = compararMinHeapNo(minHeap->vetor[FILHO_ESQ(pos)], minHeap->vetor[FILHO_DIR(pos)]);
    return comparaEsqDir <= 0 ? FILHO_ESQ(pos) : FILHO_DIR(pos);
}

void sobeNoHeap(pMinHeap minHeap, int pos) {
    pMinHeapNo subindo = minHeap->vetor[pos];

    while(pos > 0 && compararMinHeapNo(subindo, minHeap->vetor[PAI(pos)]) < 0) {
        pMinHeapNo paiAtual = minHeap->vetor[PAI(pos)];
        minHeap->vetor[pos] = paiAtual;
        minHeap->posicao[paiAtual->indice] = pos;
        pos = PAI(pos);
    }

    minHeap->vetor[pos] = subindo;
    minHeap->posicao[subindo->indice] = pos;
}

void desceNoHeap(pMinHeap minHeap, int pos) {
    pMinHeapNo descendo = minHeap->vetor[pos];
    int menor = menorFilho(minHeap, pos);

    while(menor >= 0 && compararMinHeapNo(descendo, minHeap->vetor[menor]) > 0) {
        pMinHeapNo menorAtual = minHeap->vetor[menor];
        minHeap->vetor[pos] = menorAtual;
        minHeap->posicao[menorAtual->indice] = pos;
        pos = menor;
        menor = menorFilho(minHeap, pos);
    }

    minHeap->vetor[pos] = descendo;
    minHeap->posicao[descendo->indice] = pos;
}

void adicionarNoMinHeap(pMinHeap minHeap, int indice, double prioridade) {
    if(minHeap == NULL || minHeap->vetor == NULL || minHeap->n >= minHeap->tamanho)
        return;

    pMinHeapNo novo = criarMinHeapNo(indice, prioridade);
    minHeap->vetor[minHeap->n] = novo;
    minHeap->posicao[indice] = minHeap->n;
    minHeap->n++;
    sobeNoHeap(minHeap, minHeap->n - 1);
}

void alterarPrioridade(pMinHeap minHeap, int indice, double novaPrioridade) {
    if(minHeap == NULL || indice < 0 || indice >= minHeap->tamanho)
        return;

    int posicaoIndice = minHeap->posicao[indice];
    double antigaPrioridade = minHeap->vetor[posicaoIndice]->prioridade;
    minHeap->vetor[posicaoIndice]->prioridade = novaPrioridade;

    if(antigaPrioridade < novaPrioridade)
        desceNoHeap(minHeap, posicaoIndice);
    else if(antigaPrioridade > novaPrioridade)
        sobeNoHeap(minHeap, posicaoIndice);
}

pMinHeapNo extrairMinimo(pMinHeap minHeap) {
    if(minHeap == NULL || minHeap->vetor == NULL || minHeap->n <= 0)
        return NULL;

    pMinHeapNo x = minHeap->vetor[0];
    troca(minHeap, &minHeap->vetor[0], &minHeap->vetor[minHeap->n - 1]);
    minHeap->n--;
    desceNoHeap(minHeap, 0);
    return x;
}

int estaNoMinHeap(pMinHeap minHeap, int indice) {
    return minHeap == NULL ? 0 : minHeap->posicao[indice] < minHeap->n;
}

int minHeapEstaVazio(pMinHeap minHeap) {
    return minHeap == NULL ? 1 : minHeap->n == 0;
}

void imprimirMinHeap(pMinHeap minHeap) {
    printf("MinHeap={MinHeapNos=[");
    for(int i=0; i<minHeap->n; i++) {
        printf("{%d %lf}", minHeap->vetor[i]->indice, minHeap->vetor[i]->prioridade);

        if(i < minHeap->n - 1)
            printf(", ");
    }
    
    printf("], tamanho=%d}", minHeap->tamanho);
}
