#include <stdlib.h>
#include "calculist.h"

NumeroGrande criar_numero_grande(NumeroGrande numeroGrande) {
    return NULL;
}

/* Aloca memória para um novo Nó dessa lista, ou seja, 
para um novo dígito do número passado como parâmetro, 
e retorna o ponteiro para esse novo nó. Aborta o programa 
se não há memória suficiente para tal alocação. */
NumeroGrande novoNo(NumeroGrande numeroGrande) {
    numeroGrande = malloc(sizeof(No));
    if(numeroGrande == NULL)
        exit(7);
    return numeroGrande;
}

void destruir_numero_grande(NumeroGrande numeroGrande) {
    if(numeroGrande) {
        destruir_numero_grande(numeroGrande->prox);
        free(numeroGrande);
    }
}

NumeroGrande inserir_no_inicio(NumeroGrande numeroGrande, int digito) {
    NumeroGrande novo = NULL;
    novo = novoNo(novo);
    novo->digito = digito;
    novo->prox = numeroGrande;
    return novo;
}

/* Insere um dígito no final do NumeroGrande, into é, à esquerda. */
NumeroGrande inserir_no_fim(NumeroGrande numeroGrande, int digito) {
    NumeroGrande atual, novo = NULL;
    novo = novoNo(novo);
    novo->digito = digito;
    novo->prox = NULL;

    if(numeroGrande == NULL)
        return novo;

    for(atual = numeroGrande; atual->prox != NULL; atual = atual->prox);
    atual->prox = novo;

    return numeroGrande;
}

NumeroGrande inverter(NumeroGrande numeroGrande) {
    NumeroGrande atual = numeroGrande;
    NumeroGrande proximo, anterior;
    proximo = anterior = NULL;
    
    while(atual) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    numeroGrande = anterior;
    return numeroGrande;
}

NumeroGrande copiar(NumeroGrande numeroGrande) {
    NumeroGrande copia = NULL;
    if(numeroGrande) { // != NULL
        copia = novoNo(copia);
        copia->digito = numeroGrande->digito;
        copia->prox = copiar(numeroGrande->prox);
    }

    return copia;
}

/* Remove todos os zeros à esquerda de um NumeroGrande. */
NumeroGrande remover_zeros_esquerda(NumeroGrande numeroGrande) {
    NumeroGrande atual, parada;
    for(atual = numeroGrande; atual != NULL && atual->prox != NULL && atual->prox->digito != 0; atual = atual->prox);

    while(atual) {
        parada = atual;
        atual = atual->prox;

        while(atual && atual->digito == 0)
            atual = atual->prox;

        if(atual == NULL) {// entao, a partir de parada, todos sao zeros (à esquerda)
            destruir_numero_grande(parada->prox);
            parada->prox = NULL;
            return numeroGrande;
        }

        // se atual nao é NULL, entao tinha um numero != 0 à esquerda --> continuar ate chegar no fim do numero
    }

    return numeroGrande;
}

int comparar_rec(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2, int deuDif) {
    if(numeroGrande1 == NULL && numeroGrande2 == NULL) // mesma qtd de unidades
        return 0;
    
    if(numeroGrande1 == NULL)
        return -1;

    if(numeroGrande2 == NULL)
        return 1;

    if(numeroGrande1->prox == NULL && numeroGrande2->prox == NULL) { // mesma qtd de digitos
        if(numeroGrande1->digito != numeroGrande2->digito)
            return numeroGrande1->digito - numeroGrande2->digito;
        return deuDif;
    }

    if(numeroGrande1->digito != numeroGrande2->digito)
        deuDif = numeroGrande1->digito - numeroGrande2->digito; // se em algum digito um é maior que o outro

    return comparar_rec(numeroGrande1->prox, numeroGrande2->prox, deuDif);
}

int comparar(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2) {
    numeroGrande1 = remover_zeros_esquerda(numeroGrande1);
    numeroGrande2 = remover_zeros_esquerda(numeroGrande2);
    return comparar_rec(numeroGrande1, numeroGrande2, 0);
} 

NumeroGrande somar_rec(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2, int vaiUm) {
    NumeroGrande resposta = NULL;
    unsigned int soma, digito1, digito2;

    if(numeroGrande1 == NULL && numeroGrande2 == NULL && vaiUm == 0)
        return resposta;

    digito1 = numeroGrande1 == NULL ? 0 : numeroGrande1->digito;
    digito2 = numeroGrande2 == NULL ? 0 : numeroGrande2->digito;
    
    soma = digito1 + digito2 + vaiUm;
    vaiUm = soma / 10;

    resposta = novoNo(resposta);
    resposta->digito = soma - (vaiUm * 10);
    resposta->prox = somar_rec(numeroGrande1 ? numeroGrande1->prox : NULL, numeroGrande2 ? numeroGrande2->prox : NULL, vaiUm);

    return resposta;
}

NumeroGrande subtrair_rec(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2, int tiraUm) {
    NumeroGrande resposta = NULL;
    int subtracao;
    unsigned int digito1, digito2;

    if(numeroGrande1 == NULL) {
        return resposta; // pq sei q numeroGrande1 eh o maior
    }

    digito1 = numeroGrande1->digito;
    digito2 = numeroGrande2 == NULL ? 0 : numeroGrande2->digito; // se o num 2 for null continuo subtraindo como se tivesse zeros à esquerda

    subtracao = digito1 - tiraUm - digito2;
    tiraUm = subtracao < 0 ? 1 : 0;

    resposta = novoNo(resposta);
    resposta->digito = subtracao < 0 ? subtracao + 10 : subtracao;
    resposta->prox = subtrair_rec(numeroGrande1->prox, numeroGrande2 ? numeroGrande2->prox : NULL, tiraUm);

    return resposta;
} 

/* Multiplica um NumeroGrande por um escalar (0 - 9) e retorna o resultado. */
NumeroGrande multiplicar_unidade(NumeroGrande numeroGrande, int unidade, int vaiQtd) {
    NumeroGrande resposta = NULL;
    unsigned int multiplicacao, digito1;

    if(numeroGrande == NULL && vaiQtd == 0)
        return resposta;

    digito1 = numeroGrande == NULL ? 0 : numeroGrande->digito;

    multiplicacao = digito1 * unidade + vaiQtd;
    vaiQtd = multiplicacao / 10;

    resposta = novoNo(resposta);
    resposta->digito = multiplicacao - (vaiQtd * 10);
    resposta->prox = multiplicar_unidade(numeroGrande ? numeroGrande->prox : NULL, unidade, vaiQtd);

    return resposta;
}

/* Procura o quociente da divisão inteira entre dois NumeroGrande. O quociente é um a menos
do que o escalar (0 - 9) que, multiplicado pelo numeroGrande2 (divisor), é maior que o
numeroGrande1 (dividendo). Ou seja, se 3 * numeroGrande2 > numeroGrande1, então 
numeroGrande1 / numeroGrande2 = 3 - 1 = 2. */
int achar_quociente(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2) {
    NumeroGrande multiplicacao;
    int i;

    if(numeroGrande1 == NULL || numeroGrande2 == NULL)
        return 0;

    for(i=0; i<10; i++) {
        multiplicacao = multiplicar_unidade(numeroGrande2, i, 0);
        if(comparar(numeroGrande1, multiplicacao) < 0) { // dividendo < quociente * divisor
            destruir_numero_grande(multiplicacao);
            break; // achei um quociente
        }

        destruir_numero_grande(multiplicacao);
        multiplicacao = NULL;
    }

    return i - 1;
}

NumeroGrande dividir_rec(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2, NumeroGrande parte) {
    NumeroGrande resposta = NULL, res, multiplicacao;

    if(numeroGrande1 == NULL || numeroGrande2 == NULL) {
        destruir_numero_grande(parte);
        return resposta;
    }

    parte = inserir_no_fim(parte, numeroGrande1->digito);

    parte = inverter(parte); // pois para fazer as operacoes deve estar invertido
    parte = remover_zeros_esquerda(parte);
    int q = achar_quociente(parte, numeroGrande2);

    multiplicacao = multiplicar_unidade(numeroGrande2, q, 0);
    res = subtrair(parte, multiplicacao);
    destruir_numero_grande(parte);
    destruir_numero_grande(multiplicacao);

    parte = inverter(res);

    resposta = dividir_rec(numeroGrande1->prox, numeroGrande2, parte);
    resposta = inserir_no_fim(resposta, q);
    return resposta;
}

NumeroGrande somar(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2) {
    NumeroGrande soma = somar_rec(numeroGrande1, numeroGrande2, 0);
    soma = remover_zeros_esquerda(soma);
    return soma;
}

NumeroGrande subtrair(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2) {
    int cmp = comparar(numeroGrande1, numeroGrande2);
    NumeroGrande subtracao;

    subtracao = cmp >= 0 ? subtrair_rec(numeroGrande1, numeroGrande2, 0) : subtrair_rec(numeroGrande2, numeroGrande1, 0);
    subtracao = remover_zeros_esquerda(subtracao);
    return subtracao;
}

NumeroGrande multiplicar(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2) {
    NumeroGrande resposta, respostaAnt, mult;
    resposta = respostaAnt = mult = NULL;
    int qtdZeros = 0;

    while(numeroGrande2) {
        if(numeroGrande2->digito == 0)
            mult = inserir_no_inicio(mult, 0); // pq multiplicar por zero dá sempre zero
        else
            mult = numeroGrande2->digito == 1 ? copiar(numeroGrande1) : multiplicar_unidade(numeroGrande1, numeroGrande2->digito, 0); //multiplicar por 1 unidade de numero2

        for(int i=0; i<qtdZeros; i++)
            mult = inserir_no_inicio(mult, 0); //inserir zeros à direita
    
        resposta = somar(respostaAnt, mult); //somar resultados
        destruir_numero_grande(respostaAnt);
        destruir_numero_grande(mult);
        mult = NULL;
        respostaAnt = resposta;
        numeroGrande2 = numeroGrande2->prox;
        qtdZeros++;
    }

    return resposta;
}

NumeroGrande dividir(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2) {
    NumeroGrande resposta, atual, guarda, parte = NULL;
    numeroGrande1 = inverter(numeroGrande1);
    guarda = numeroGrande1;

    atual = numeroGrande2;
    while(atual && atual->prox && numeroGrande1 && numeroGrande1->prox) {
        parte = inserir_no_fim(parte, numeroGrande1->digito);
        atual = atual->prox;
        numeroGrande1 = numeroGrande1->prox;
    }

    resposta = dividir_rec(numeroGrande1, numeroGrande2, parte);
    resposta = remover_zeros_esquerda(resposta);
    numeroGrande1 = inverter(guarda);
    return resposta;
}