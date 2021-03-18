#include "CorretorOrtografico.h"

void imprimeNivelCorrecao(int nivel) {
    switch (nivel) {
        case 0:
            printf("verde\n");
            break;
        case 1:
            printf("amarelo\n");
            break;
        case 2:
            printf("vermelho\n");
        default:
            break;
    }
}

int main() {
    int n, q;
    char palavra[26];
    int nivelCorrecao;

    if(scanf("%d %d", &n, &q) == EOF)
        return 0;

    Dicionario dicionario = criarDicionario(n * 10); // para deixar bem espalhado no dicionario

    for(int i=0; i<n; i++) {
        if(scanf("%s", palavra))
            guardarNoDicionario(dicionario, palavra);
    }

    for(int i=0; i<q; i++) {
        if(scanf("%s", palavra)) {
            nivelCorrecao = obterNivelCorrecao(dicionario, palavra);
            imprimeNivelCorrecao(nivelCorrecao);
        }
    }

    destruirDicionario(dicionario);
    return 0;
}
