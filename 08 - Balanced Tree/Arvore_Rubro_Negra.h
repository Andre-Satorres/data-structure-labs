#ifndef Arvore_Rubro_Negra_h
#define Arvore_Rubro_Negra_h
#include "Utils.h"

enum Cor { VERMELHO, PRETO };

typedef struct No {
    Any info;
    enum Cor cor;
    struct No *esq, *dir;
} No;

typedef No * p_no;

/* Retorna 0 (falso) se x não tem cor vermelha e != 0 (verdadeiro) caso contrário. */
int eh_vermelho(p_no x);

/* Retorna 0 (falso) se x não tem cor preta e != 0 (verdadeiro) caso contrário. */
int eh_preto(p_no x);

/* Cria uma nova Arvore Binaria de Busca e a retorna. */
p_no criar_abb();

/* Destroi a Arvore Binaria de Busca recebida como parametro, destruindo cada info dos Nos com fdestroi. */
p_no destruir_abb(p_no raiz, void (*fdestroi)(Any));

/* Retorna o menor valor na ABB (o mais a esquerda). */
p_no minimo_absoluto(p_no raiz);

/* Retorna o maior valor na ABB (o mais a direita). */
p_no maximo_absoluto(p_no raiz);

/* Busca x na ABB usando fcompara para comparar x com os infos. */
p_no buscar_na_abb(p_no raiz, Any x, int (*fcompara)(Any, Any));

/* Insere x na ABB, usando fcopia para armazenar uma copia independente de x e fcompara para comparar x com os infos. 
* Se x ja esta na ABB, fatualiza atualiza o info da arvore com o novo x. */
p_no inserir_na_abb(p_no raiz, Any x, Any (fcopia)(Any), int (*fcompara)(Any, Any), void (*fatualiza)(Any, Any));

/* Remove x da ABB, usando fcompara para comparar x com os infos e fdestroi para corretamente liberar o info 
* do No que contem x da memoria. fcopia eh utilizada para copiar corretamente o info de um No para a raiz, caso x esteja na raiz. */
p_no remover_da_abb(p_no raiz, Any x, Any (*fcopia)(Any), int (*fcompara)(Any, Any), void (*fdestroi)(Any));

/* Retorna o maior valor da ABB menor que x, usando fcompara para as comparacoes. */
p_no maximo_menor_que(p_no raiz, Any x, int (*fcompara)(Any, Any));

/* Junta todos os Nos da ABB em um so, usando fjunta para corretamente unir cada info dos Nos.
fdestroi eh usada para liberar todos os outros Nos, exceto a raiz (o unico que restara). */
p_no juntar_todos(p_no raiz, Any (*fjunta)(Any, Any), void (*fdestroi)(Any));

/* Imprime a ABB, usando fimprime para saber como devidamente imprimir as infos da ABB. */
void imprimir_abb(p_no raiz, void (*fimprime)(Any));

#endif