#ifndef Arvore_Binaria_de_Busca_h
#define Arvore_Binaria_de_Busca_h
#include "Utils.h"

typedef struct No {
    void *info;
    struct No *esq, *dir;
} No;

typedef No * p_no;

/* Cria uma nova Arvore Binaria de Busca e a retorna. */
p_no criar_abb();

/* Destroi a Arvore Binaria de Busca recebida como parametro,
destruindo cada info dos Nos com fdestroi. */
p_no destruir_abb(p_no raiz, void (*fdestroi)(void *));

/* Retorna o menor valor na ABB (o mais a esquerda). */
p_no minimo_absoluto(p_no raiz);

/* Retorna o maior valor na ABB (o mais a direita). */
p_no maximo_absoluto(p_no raiz);

/* Busca x na ABB usando fcompara para comparar x com os infos. */
p_no buscar_na_abb(p_no raiz, void *x, int (*fcompara)(void *, void *));

/* Insere x na ABB, usando fcopia para armazenar uma copia independente de x e
fcompara para comparar x com os infos. */
p_no inserir_na_abb(p_no raiz, void *x, void *(fcopia)(void *), int (*fcompara)(void *, void *));

/* Remove x da ABB, usando fcompara para comparar x com os infos e fdestroi para
corretamente liberar o info do No que contem x da memoria. fcopia eh utilizada para
copiar corretamente o info de um No para a raiz, caso x esteja na raiz. */
p_no remover_da_abb(p_no raiz, void *x, void *(*fcopia)(void *), int (*fcompara)(void *, void *), void (*fdestroi)(void *));

/* Retorna o maior valor da ABB menor que x, usando fcompara para as comparacoes. */
p_no maximo_menor_que(p_no raiz, void *x, int (*fcompara)(void *, void *));

/* Junta todos os Nos da ABB em um so, usando fjunta para corretamente unir cada info dos Nos.
fdestroi eh usada para liberar todos os outros Nos, exceto a raiz (o unico que restara). */
p_no juntar_todos(p_no raiz, void *(*fjunta)(void *, void *), void (*fdestroi)(void *));

/* Imprime a ABB, usando fimprime para saber como devidamente imprimir as infos da ABB. */
void imprimir_abb(p_no raiz, void (*fimprime)(void *));

#endif