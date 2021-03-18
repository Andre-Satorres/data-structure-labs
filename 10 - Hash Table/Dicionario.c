#include "Dicionario.h"

int stringHashCodeGenerico(Any x, int max) {
    return stringHashCode((String)x, max);
}

Any copiarStringGenerico(Any s) {
    return copiarString((String)s);
}

int compararStringGenerico(Any s1, Any s2) {
    return compararString((String)s1, (String)s2);
}

Dicionario criarDicionario(int tamanho) {
    return criarHashTable(tamanho, stringHashCodeGenerico);
}

void destruirDicionario(Dicionario dicionario) {
    if(dicionario != NULL)
        destruirHashTable(dicionario, free);
}

void guardarNoDicionario(Dicionario dicionario, String palavra) {
    if(dicionario != NULL)
        inserirNoHashTable(dicionario, palavra, palavra, copiarStringGenerico);
}

int estaNoDicionario(Dicionario dicionario, String palavra) {
    if(dicionario == NULL)
        return 0;

    return estaNoHashTable(dicionario, palavra, palavra, compararStringGenerico);
}
