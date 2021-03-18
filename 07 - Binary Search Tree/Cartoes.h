#include "Arvore_Binaria_de_Busca.h"

typedef struct Cartao {
    unsigned int numero;
    char *texto;
} Cartao;

typedef Cartao * p_cartao;

/* Cria um novo Cartao a partir do numero e texto passados como parametro. */
p_cartao criar_cartao(unsigned int numero, char *texto);

/* Compara dois Cartoes levando em consideracao somente seus numeros. */
int comparar_cartao_por_numero(p_cartao cartao1, p_cartao cartao2);

/* Recebe um Cartao como parametro e cria outro exatamente igual, devolvendo-o. */
p_cartao copiar_cartao(p_cartao cartao);

/* Destroi, liberando da memoria, o Cartao recebido como parametro. */
void destruir_cartao(p_cartao cartao);

/* Devolve um novo Cartao que eh a juncao dos outros dois passados como parametro. */
p_cartao juntar_cartoes(p_cartao c1, p_cartao c2);

/* Imprime o Cartao recebido por parametro na tela. */
void imprimir_cartao(p_cartao cartao);

/* Imprime o texto do Cartao recebido por parametro. */
void imprimir_texto(p_cartao cartao);