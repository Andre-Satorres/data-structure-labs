#ifndef Saco_de_Cartoes_h
#define Saco_de_Cartoes_h
#include "Cartoes.h"

#define MAX_TEXTO 6

typedef p_no Saco;

/* Cria e retorna um novo Saco. */
Saco criar_saco();

/* Destroi o Saco recebido por parametro. */
Saco destruir_saco(Saco saco);

/* Preenche o Saco com qtd_cartoes Cartoes, usando fle para ler o numero e texto de cada Cartao. */
Saco preencher_saco(Saco saco, unsigned int qtd_cartoes, void (*fle)(unsigned int *, char *));

/* Insere um Cartao no Saco a partir do numero e texto passados por parametro. */
Saco inserir_no_saco(Saco saco, unsigned int numero, char *texto);

/* Faz a troca de Cartoes com as qtd_autoridades autoridades usando fle para ler o numero de cada autoridade. */
p_no trocar_com_autoridades(Saco saco_de_cartoes, unsigned int qtd_autoridades, void (*fle)(unsigned int *));

/* Faz uma troca de Cartoes com uma autoridade de numero numero_da_autoridade. */
Saco trocar_com_autoridade(Saco saco, unsigned int numero_da_autoridade);

/* Junta todos os Cartoes restantes do Saco para formar a mensagem final a ser entregue. */
Saco preparar_mensagem(Saco saco);

/* Imprime na tela a mensagem do Cartao na raiz da Arvore Binaria de Busca. */
void mostrar_mensagem(Saco saco);

/* Imprime o Saco na tela. */
void imprimir_saco(Saco saco);

#endif
