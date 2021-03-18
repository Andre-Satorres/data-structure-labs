#include "GrafoMapa.h"
#include "MinHeap.h"
#include "limits.h"

int valorInt(Inteiro i) {
    return *i;
}

Inteiro criarInteiro(int i) {
    Inteiro novo = novoPonteiro(sizeof(int));
    *novo = i;
    return novo;
}

Inteiro copiarInteiro(Inteiro i) {
    return criarInteiro(valorInt(i));
}

Any copiarInteiroGenerico(Any i) {
    return copiarInteiro(i);
}

pGrafoMapa criarGrafoMapa(double xInicial, double yInicial) {
    pGrafoMapa grafoMapa = novoPonteiro(sizeof(GrafoMapa));
    grafoMapa->mapaParadas = criarMapaParadas();
    grafoMapa->indicesDeInteresse = criarListaLigada();
    grafoMapa->grafoParadas = NULL;

    pParada saida = criarParada(xInicial, yInicial, SAIDA);
    inserirParada(grafoMapa->mapaParadas, saida);
    destruirParada(saida);
    return grafoMapa;
}

void destruirGrafoMapa(pGrafoMapa grafoMapa) {
    if(grafoMapa == NULL)
        return;

    destruirMapaParadas(grafoMapa->mapaParadas);
    destruirListaLigada(grafoMapa->indicesDeInteresse, free);
    destruirGrafo(grafoMapa->grafoParadas);
    free(grafoMapa);
}

void novaParada(pGrafoMapa grafoMapa, double x, double y, int ehDeInteresse) {
    if(grafoMapa == NULL)
        return;

    if(ehDeInteresse) {
        Inteiro i = criarInteiro(grafoMapa->mapaParadas->n);
        grafoMapa->indicesDeInteresse = inserirNaLista(grafoMapa->indicesDeInteresse, i, copiarInteiroGenerico);
        free(i);
    }

    int tipoParada = ehDeInteresse ? INTERESSE : PONTO;
    pParada parada = criarParada(x, y, tipoParada);
    inserirParada(grafoMapa->mapaParadas, parada);
    destruirParada(parada);
}

void montarGrafo(pGrafoMapa grafoMapa) {
    int qtd = grafoMapa->mapaParadas->n;
    grafoMapa->grafoParadas = criarGrafo(qtd);
    int i = qtd-1, j = qtd-1; // pois insiro no inicio da lista, ou seja, o ponto de saida esta no final

    for(pNo t=grafoMapa->mapaParadas->paradas; t != NULL; t=t->prox) {
        for(pNo r=t; r != NULL; r=r->prox) {
            if(i != j) {
                pParada p1 = t->dado, p2 = r->dado;
                double dist = distancia(p1->coordenada, p2->coordenada);
                inserirAresta(grafoMapa->grafoParadas, i, j, dist);
            }

            j--;
        }

        i--;
        j=i;
    }
}

int deveAlterarDistancia(pGrafo grafoParadas, pMinHeap minHeap, double *distancia, int u, int v) {
    return temAresta(grafoParadas, u, v) 
            && estaNoMinHeap(minHeap, v) 
            && grafoParadas->adjacencias[u][v] < distancia[v];
}

int * acharArvoreGeradoraMinima(pGrafoMapa grafoMapa) {
    int qtd = grafoMapa->grafoParadas->n;
    int *pai = novoPonteiro(sizeof(int) * qtd);
    double *distancia = novoPonteiro(sizeof(double) * qtd);

    pMinHeap minHeap = criarMinHeap(qtd);

    // Inicializar todas as distancias com infinito (int_max)
    for (int i = 0; i < qtd; i++) {
        pai[i] = -1;
        distancia[i] = INT_MAX;
        adicionarNoMinHeap(minHeap, i, distancia[i]);
    }

    distancia[0] = 0; // vai ser pego primeiro

    while(!minHeapEstaVazio(minHeap)) {
        pMinHeapNo verticeExtraido = extrairMinimo(minHeap);
        int u = verticeExtraido->indice; // guardar o numero do vertice extraido

        // Percorrer toda a adjacencia de u e atualizar as distancias
        for(int v = 0; v < qtd; v++) {
            if(deveAlterarDistancia(grafoMapa->grafoParadas, minHeap, distancia, u, v)) {
                distancia[v] = grafoMapa->grafoParadas->adjacencias[u][v];
                pai[v] = u;
                alterarPrioridade(minHeap, v, distancia[v]);
            }
        }

        free(verticeExtraido);
    }

    destruirMinHeap(minHeap);
    free(distancia);
    return pai;
}

double maiorArestaDoCaminhoComArestaMaximaMinima(pGrafoMapa grafoMapa, int *pai, int indiceDestino) {
    int indiceAtual = indiceDestino;
    double maiorAresta = 0;
    while(pai[indiceAtual] != -1) {
        if(aresta(grafoMapa->grafoParadas, indiceAtual, pai[indiceAtual]) > maiorAresta)
            maiorAresta = aresta(grafoMapa->grafoParadas, indiceAtual, pai[indiceAtual]);
        
        indiceAtual = pai[indiceAtual];
    }

    return maiorAresta;
}

void imprimirArvoreGeradoraMinima(int *pai, pGrafoMapa grafoMapa) { 
    printf("Aresta \tDistancia\n"); 
    for (int i = 1; i <  grafoMapa->grafoParadas->n; i++) 
        printf("%d - %d \t%f \n", pai[i], i, grafoMapa->grafoParadas->adjacencias[i][pai[i]]); 
}

double maiorArestaMinimaDoCaminho(pGrafoMapa grafoMapa) {
    int *pai = acharArvoreGeradoraMinima(grafoMapa);
    double menorArestaMaxima = INT_MAX;

    for(pNo indiceInteresse = grafoMapa->indicesDeInteresse; indiceInteresse != NULL; indiceInteresse = indiceInteresse->prox) {
        Inteiro deInteresse = ((Inteiro) (indiceInteresse->dado));
        double arestaAtual= maiorArestaDoCaminhoComArestaMaximaMinima(grafoMapa, pai, valorInt(deInteresse));

        if(arestaAtual < menorArestaMaxima)
            menorArestaMaxima = arestaAtual;
    }

    free(pai);
    return menorArestaMaxima;
}
