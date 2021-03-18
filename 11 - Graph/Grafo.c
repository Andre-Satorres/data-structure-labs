#include "Grafo.h"

pGrafo criarGrafo(int n) {
    pGrafo g = novoPonteiro(sizeof(Grafo));
    g->n = n;

    g->adjacencias = novoPonteiro(g->n * sizeof(double *));
    for(int i=0; i<g->n; i++)
        g->adjacencias[i] = callocPonteiro(g->n, sizeof(double));

    return g;
}

void destruirGrafo(pGrafo g) {
    if(g == NULL)
        return;

    for(int i=0; i<g->n; i++)
        free(g->adjacencias[i]);

    free(g->adjacencias);
    free(g);
}

double aresta(pGrafo g, int u, int v) {
    return g->adjacencias[u][v];
}

void inserirAresta(pGrafo g, int u, int v, double peso) {
    g->adjacencias[u][v] = peso;
    g->adjacencias[v][u] = peso;
}

void removerAresta(pGrafo g, int u, int v) {
    g->adjacencias[u][v] = -1;
    g->adjacencias[v][u] = -1;
}

int temAresta(pGrafo g, int u, int v) {
    return g->adjacencias[u][v] != -1;
}

void imprimirArestas(pGrafo g) {
    for(int u=0; u<g->n; u++)
        for(int v=0; v<u; v++)
            printf("Aresta{(%d <-> %d), peso=%lf}\n", u, v, g->adjacencias[u][v]);
}