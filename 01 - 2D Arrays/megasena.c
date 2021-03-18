#include <stdio.h>

#define MAX_NUMEROS_POSSIVEIS 15
#define MAX_SORTEIO 6
#define PERCENTUAL_SENA 62
#define PERCENTUAL_QUINA 19
#define PERCENTUAL_QUADRA 19
#define MAX_APOSTADORES 1000

void lerMatrizesBinarias(int m, int numerosApostados [][MAX_NUMEROS_POSSIVEIS]);
void imprimirGanhos(double valorTotal, int qtdAcertosPorJogador[], int qtdQuadras, int qtdQuinas, int qtdSenas, int m);

int main() {
    int m, sorteados [MAX_SORTEIO], qtdIguais, qtdSenas, qtdQuinas, qtdQuadras;
    double n;
    qtdIguais = qtdSenas = qtdQuinas = qtdQuadras = 0;
    int numerosApostados[MAX_APOSTADORES][MAX_NUMEROS_POSSIVEIS];  /* representa os numeros apostados por cada apostador (max de 15 por apostador) */
    int qtdAcertosPorJogador [MAX_APOSTADORES]; /* armazena quantos acertos cada apostador obteve, para saber se ganhou quadra, quina, sena ou nada*/

    scanf("%d", &m); /* quantidade de apostadores*/
    scanf("%lf", &n); /* valor total do premio*/
    
    lerMatrizesBinarias(m, numerosApostados);  /* le cada matriz binaria e preenche o vetor de numeros apostados por jogador */
    
    for(int i=0; i<MAX_SORTEIO; i++)
        scanf("%d", &sorteados[i]);  /* le os 6 numeros sorteados na mega da virada */
    
    for(int i=0; i<m; i++) {  /* para cada jogador*/
        for(int j=0; j<MAX_NUMEROS_POSSIVEIS; j++) {  /*ler cada numero que o jodagor apostou*/
            for(int k=0; k<MAX_SORTEIO; k++) 
                if(numerosApostados[i][j] == sorteados[k]) /* e ver se eh igual a alguns dos sorteados na megasena*/
                    qtdIguais++; /* saber quantos ele acertou */
        }
        
        qtdAcertosPorJogador[i] = qtdIguais;  /* armazeno no vetor para uso futuro */
        
        /* saber a quantidade de ganhadores de cada uma das faixas */
        if(qtdIguais == 4)
            qtdQuadras++;
        else if(qtdIguais == 5)
            qtdQuinas++;
        else if(qtdIguais == 6)
            qtdSenas++;

        qtdIguais = 0; /* reseto para ler do proximo apostador */
    }

    imprimirGanhos(n, qtdAcertosPorJogador, qtdQuadras, qtdQuinas, qtdSenas, m);
}

void lerMatrizesBinarias(int m, int numerosApostados [][MAX_NUMEROS_POSSIVEIS]) {
    int valor, qtdApostados = 0;
    for(int k=0; k<m; k++) { /* ler as m matrizes de aposta */
        for(int i=0; i<6; i++) { /* cada matriz tem 6 linhas*/
            for(int j=0; j<10; j++) { /* e 10 colunas */
                scanf("%d", &valor); /* sera 0 ou 1*/
                valor *= i*10 + j + 1; /* continua 0 se eu li um zero. Sera o valor decimal apostado caso tenha um 1 */

                if(valor != 0) {
                    numerosApostados[k][qtdApostados] = valor;  /* salvo apenas os numeros que o jogador apostou */
                    qtdApostados++; /* para controlar a posicao do vetor numerosApostados[k] a inserir */
                }
            }
        }
        qtdApostados = 0; /* reseto pois vou ler as apostas de outro jogador */
    }
}

void imprimirGanhos(double valorTotal, int qtdAcertosPorJogador[], int qtdQuadras, int qtdQuinas, int qtdSenas, int m) { 
    for(int i=0; i<m; i++) {
        if(qtdAcertosPorJogador[i] == 4)
            printf("%.2f\n", (valorTotal * PERCENTUAL_QUADRA / 100) / qtdQuadras); /* valor recebido por ganhadores da quadra*/
        else if(qtdAcertosPorJogador[i] == 5)
            printf("%.2f\n", (valorTotal * PERCENTUAL_QUINA / 100) / qtdQuinas); /* valor recebido por ganhadores da quina*/
        else if(qtdAcertosPorJogador[i] == 6)
            printf("%.2f\n", (valorTotal * PERCENTUAL_SENA / 100) / qtdSenas); /* valor recebido por ganhadores da sena*/
        else
            printf("%.2f\n", 0.0); /* valor recebido por quem acertou menos de 4 => R$0,00*/
    }
}