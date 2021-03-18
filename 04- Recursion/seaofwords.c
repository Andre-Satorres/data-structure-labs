#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PALAVRA 21 // limite definido no enunciado (20 + 1 para o \0)

typedef struct Letra {
    char letra;
    int visitado;
} Letra;

int procura(Letra *texto, int pos, char *palavra, int indice, int n, int m) {
    if(indice >= strlen(palavra)) return 1; // achei
    if(pos >= n * m) return 0; // nao achei

    int achei = 0;

    if(!texto[pos].visitado && texto[pos].letra == palavra[indice]) { // achei uma posicao que pode servir
        texto[pos].visitado = 1; // para nao escolher essa letra 2 vezes na mesma palavra

        if( !achei && (pos - m + 1) % m != 0 ) achei = procura(texto, pos + 1, palavra, indice + 1, n, m); // procurar na direita
        if( !achei && pos < m * (n - 1)      ) achei = procura(texto, pos + m, palavra, indice + 1, n, m); // procurar embaixo
        if( !achei && pos % m != 0           ) achei = procura(texto, pos - 1, palavra, indice + 1, n, m); // procurar na esquerda
        if( !achei && pos >= m               ) achei = procura(texto, pos - m, palavra, indice + 1, n, m); // procurar em cima
        
        texto[pos].visitado = 0; // resetar para 0 para poder buscar outra palavra sem problemas
        if(achei) return achei; // consegui achar a palavra inteira
    }

    if(indice > 0) { // tentei procurar uma continuacao da palavra e nao consegui achar/completar
        indice--; // voltar 1 letra
        return 0; // nao achei
    } 
    
    return procura(texto, pos + 1, palavra, indice, n, m); // indice == 0 => vou tentar achar outro inicio
}

int procurar_no_texto(Letra *texto, char *palavra, int n, int m) {
    return procura(texto, 0, palavra, 0, n, m); // uma "casca" para a funcao recursiva
}

int main() {
    int n, m, q;
    Letra *texto; // matriz linearizada
    char palavra[MAX_PALAVRA];

    scanf("%d %d %d", &n, &m, &q);

    texto = malloc(n * m * sizeof(Letra));
    for(int i=0; i<n*m; i++) {
        scanf(" %c", &texto[i].letra);
        texto[i].visitado = 0; // inicializacao
    }

    for(int i=0; i<q; i++) {
        scanf("%s", palavra);

        if(procurar_no_texto(texto, palavra, n, m))
            printf("sim\n");
        else
            printf("nao\n");
    }

    free(texto);
    return 0;
}