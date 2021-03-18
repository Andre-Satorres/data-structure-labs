#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "calculist.h"

void sair() {
    printf("Sem memoria suficiente. Abortando...\n");
    exit(1);
}

void printNumeroGrande(NumeroGrande numero) {
    if(numero == NULL)
        return;

    printf("%u", numero->digito);
    printNumeroGrande(numero->prox);
}

NumeroGrande lerNumeroGrande(NumeroGrande numero) {
    char digito;
    scanf("%c", &digito);

    if(digito - '0' < 0 || digito - '0' > 9)
        return numero;

    numero = inserir_no_inicio(numero, digito - '0');
        
    if(numero == NULL)
        sair();

    return lerNumeroGrande(numero);
}

int main() {
    int n;
    char operacao;
    NumeroGrande numero1, numero2, resposta;

    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        scanf(" %c ", &operacao);

        numero1 = criar_numero_grande(numero1);
        numero2 = criar_numero_grande(numero2);
        resposta= criar_numero_grande(resposta);

        numero1 = lerNumeroGrande(numero1);
        numero2 = lerNumeroGrande(numero2);

        switch (operacao) {
            case '+': //somar
                resposta = somar(numero1, numero2);
                break;
            case '-': //subtrair
                resposta = subtrair(numero1, numero2);
                break;
            case '*': //multiplicar
                resposta = multiplicar(numero1, numero2);
                break;
            case '/': //dividir
                resposta = dividir(numero1, numero2);
                break;
        }

        resposta = inverter(resposta);
        printNumeroGrande(resposta);
        printf("\n");
        
        destruir_numero_grande(numero1);
        destruir_numero_grande(numero2);
        destruir_numero_grande(resposta);
    }

    return 0;
}