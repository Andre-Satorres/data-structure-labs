#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Utils.h"
#include "ListaLigada.h"

typedef struct HashTable {
    pNo *valores;
    int tamanho;
    int (*fhash)(Any, int);
} HashTable;

typedef HashTable * pHashTable;

/* Cria e retorna uma nova HashTable de tamanho 'tamanho' que usará 'fhash' para hashear os dados. */
pHashTable criarHashTable(int tamanho, int (*fhash)(Any, int));

/* Libera a HashTable recebida da memoria. */
void destruirHashTable(pHashTable hashTable, void (*fdestroi)(Any));

/* Insere no HashTable a chave 'chave' e o valor 'valor', usando fcopia para inserir uma copia do dado. */
void inserirNoHashTable(pHashTable hashTable, Any chave, Any valor, Any (*fcopia)(Any));

/* Verifica se a chave 'chave' de valor 'valor' esta no HashTable, usando fcompara para comparar os dados. */
int estaNoHashTable(pHashTable hashTable, Any chave, Any valor, int (*fcompara)(Any, Any));

#endif