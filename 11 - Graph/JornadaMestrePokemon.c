#include "JornadaMestrePokemon.h"
#include <string.h>
#include <math.h>

JornadaMestrePokemon criarJornadaMestrePokemon(char interesse[]) {
    double x, y;
    scanf("%lf %lf", &x, &y); // ponto inicial
    JornadaMestrePokemon jornada = novoPonteiro(sizeof(Jornada));
    jornada->dados = criarGrafoMapa(x, y);
    strcpy(jornada->interesse, interesse);
    return jornada;
}

void destruirJornadaMestrePokemon(JornadaMestrePokemon jornada) {
    if(jornada == NULL)
        return;

    destruirGrafoMapa(jornada->dados);
    free(jornada);
}

void lerMapa(JornadaMestrePokemon jornada) {
    double x, y;
    char tipoPonto[9];

    while(scanf("%lf %lf %s", &x, &y, tipoPonto) != EOF) {
        int ehDeInteresse = strcmp(tipoPonto, jornada->interesse) == 0;
        novaParada(jornada->dados, x, y, ehDeInteresse);
    }
}

void iniciarJornada(JornadaMestrePokemon jornada) {
    montarGrafo(jornada->dados);
}

int maiorDistanciaMinima(JornadaMestrePokemon jornada) {
    return (int) ceil(maiorArestaMinimaDoCaminho(jornada->dados));
}