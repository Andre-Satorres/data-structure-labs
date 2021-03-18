#include "HashTable.h"

pHashTable criarHashTable(int tamanho, int (*fhash)(Any, int)) {
    pHashTable hashTable = novoPonteiro(sizeof(HashTable));
    hashTable->tamanho = tamanho;
    hashTable->valores = novoPonteiro(sizeof(pNo) * tamanho);
    hashTable->fhash = fhash;

    for(int i=0; i<tamanho; i++)
        hashTable->valores[i] = criarListaLigada();

    return hashTable;
}

void destruirHashTable(pHashTable hashTable, void (*fdestroi)(Any)) {
    for(int i=0; i<hashTable->tamanho; i++)
        hashTable->valores[i] = destruirListaLigada(hashTable->valores[i], fdestroi);

    free(hashTable->valores);
    free(hashTable);
}

void inserirNoHashTable(pHashTable hashTable, Any chave, Any valor, Any (*fcopia)(Any)) {
    int indiceHash = hashTable->fhash(chave, hashTable->tamanho);
    hashTable->valores[indiceHash] = inserirNaLista(hashTable->valores[indiceHash], chave, fcopia);
}

int estaNoHashTable(pHashTable hashTable, Any chave, Any valor, int (*fcompara)(Any, Any)) {
    int indiceHash = hashTable->fhash(chave, hashTable->tamanho);
    return estaNaLista(hashTable->valores[indiceHash], valor, fcompara);
}
