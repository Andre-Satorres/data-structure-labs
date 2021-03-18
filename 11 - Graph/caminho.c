#include "JornadaMestrePokemon.h"

int main() {
    char interesse[] = "Lugia";
    JornadaMestrePokemon jornada = criarJornadaMestrePokemon(interesse);

    lerMapa(jornada);
    iniciarJornada(jornada);
    printf("%d", maiorDistanciaMinima(jornada));

    destruirJornadaMestrePokemon(jornada);
    return 0;
}