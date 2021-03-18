#include "StringUtils.h"

String criarString(int tamanho) {
    return novoPonteiro(sizeof(char) * tamanho);
}

String reallocaString(String s, size_t novoTamanho) {
    return reallocaPonteiro(s, novoTamanho);
}

String copiarString(String s) {
    if(s == NULL)
        return NULL;

    String ret = novoPonteiro(sizeof(char) * (strlen(s) + 1));
    ret = strcpy(ret, s);
    return ret;
}

int estaVazia(String s) {
    return s != NULL && strlen(s) > 0;
}

int compararString(String s1, String s2) {
    return strcmp(s1, s2);
}

int stringHashCode(String str, int max) {
    if(str == NULL)
        return 0;

    int hash = 0;
    for (int i = 0; i < strlen(str); i++)
        hash = (hash * 256 + str[i]) % max;
    return hash;
}