#ifndef Grafo_H
#define Grafo_H
#include "Utils.h"

typedef struct Grafo {
    double **adjacencias;
    int n;
} Grafo;

typedef Grafo * pGrafo;

/* Cria e retorna um Grafo de n vértices. */
pGrafo criarGrafo(int n);

/* Libera da memoria o Grafo recebido por parâmetro. */
void destruirGrafo(pGrafo g);

/* Devolve o peso da aresta entre u e v. */
double aresta(pGrafo g, int u, int v);

/* Insere uma aresta que liga u a v com o peso dado. */
void inserirAresta(pGrafo g, int u, int v, double peso);

/* Remove a aresta que liga u a v. */
void removerAresta(pGrafo g, int u, int v);

/* Verifica se há aresta que liga u a v. */
int temAresta(pGrafo g, int u, int v);

/* Imprime todas as arestas do Grafo g na tela. */
void imprimirArestas(pGrafo g);

#endif