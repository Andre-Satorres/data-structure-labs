#include "CorretorOrtografico.h"

int buscaRemovendoCaracter(Dicionario dicionario, String palavra) {
    String aux = copiarString(palavra);
    for(int i=0; i<strlen(aux); i++) {
        memmove(&aux[i], &aux[i + 1], strlen(aux) - i);
        
        if(estaNoDicionario(dicionario, aux)) {
            free(aux);
            return 1; // achei
        }

        strcpy(aux, palavra);
    }

    free(aux);
    return 0; // nao achei
}

int buscaTrocandoCadaCaracter(Dicionario dicionario, String palavra) {
    for(int i=0; i<strlen(palavra); i++) {
        char aux = palavra[i];
        for(int j='a'; j<='z'; j++) {
            if(aux == j)
                continue;

            palavra[i] = (char)j;
            if(estaNoDicionario(dicionario, palavra))
                return 1; // achei
        }

        palavra[i] = aux;
    }

    return 0; // nao achei
}

int buscaAdicionandoCaracter(Dicionario dicionario, String palavra) {
    String aux = criarString(strlen(palavra) + 2);
    strcpy(aux, palavra);

    int tamanhoAux = strlen(palavra) + 1;
    aux[tamanhoAux] = '\0';

    for(int i=0; i< tamanhoAux; i++) {
        memmove(&aux[i+1], &aux[i], tamanhoAux - i);

        for(int j='a'; j<='z'; j++) {
            if(aux[i] == j)
                continue;

            aux[i] = (char)j;
            if(estaNoDicionario(dicionario, aux)) {
                free(aux);
                return 1; // achei
            }
        }

        memmove(&aux[i], &aux[i+1], strlen(aux) - i);
    }

    free(aux);
    return 0; // nao achei
}

int temUmCaracterAMais(Dicionario dicionario, String palavra) {
    return buscaRemovendoCaracter(dicionario, palavra) == 1;
}

int temUmCaracterTrocado(Dicionario dicionario, String palavra) {
    return buscaTrocandoCadaCaracter(dicionario, palavra) == 1;
}

int temUmCaracterAMenos(Dicionario dicionario, String palavra) {
    return buscaAdicionandoCaracter(dicionario, palavra) == 1;
}

int obterNivelCorrecao(Dicionario dicionario, String palavra) {
    if(estaNoDicionario(dicionario, palavra))
        return VERDE;

    if(temUmCaracterAMais(dicionario, palavra) || temUmCaracterTrocado(dicionario, palavra) || temUmCaracterAMenos(dicionario, palavra))
        return AMARELO;

    return VERMELHO;
}
