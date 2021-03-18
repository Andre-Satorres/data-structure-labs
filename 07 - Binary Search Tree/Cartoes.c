#include "Cartoes.h"
#include <string.h>

p_cartao criar_cartao(unsigned int numero, char *texto) {
    p_cartao novo = novo_ponteiro(sizeof(Cartao));
    novo->numero = numero;

    if(!texto) {
        novo->texto = NULL;
        return novo;
    }

    novo->texto = novo_ponteiro(sizeof(char) * (strlen(texto) + 1));
    novo->texto = strcpy(novo->texto, texto);
    return novo;
}

int comparar_cartao_por_numero(p_cartao cartao1, p_cartao cartao2) {
    if(cartao1 == NULL && cartao2 == NULL)
        return 0;

    return cartao1 == NULL ? -1 : cartao2 == NULL ? 1 : cartao1->numero - cartao2->numero;
}

p_cartao copiar_cartao(p_cartao cartao) {
    return cartao == NULL ? NULL : criar_cartao(cartao->numero, cartao->texto);
}

void destruir_cartao(p_cartao cartao) {
    if(cartao) {
        if(cartao->texto)
            free(cartao->texto);

        free(cartao);
    }
}

p_cartao juntar_cartoes(p_cartao cartao1, p_cartao cartao2) {
    if(cartao1 == NULL && cartao2 == NULL) return NULL;

    if(cartao1 == NULL) return criar_cartao(cartao2->numero, cartao2->texto);
    if(cartao2 == NULL) return criar_cartao(cartao1->numero, cartao1->texto);

    unsigned int numero = cartao1->numero + cartao2->numero;
    
    unsigned int tamanho_texto = strlen(cartao1->texto) + strlen(cartao2->texto) + 1; // +1 para o '\0'
    char *texto = novo_ponteiro(sizeof(char) * tamanho_texto);
    texto = strcat(strcpy(texto, cartao1->texto), cartao2->texto); // junta os dois textos
    
    p_cartao novo = criar_cartao(numero, texto);
    free(texto);
    return novo;
}

void imprimir_cartao(p_cartao cartao) {
    if(cartao) {
        printf("Cartao(");
        printf("numero=%d, ", cartao->numero);
        printf("texto=%s)", cartao->texto);
    }
}

void imprimir_texto(p_cartao cartao) {
    if(cartao) 
        printf("%s", cartao->texto);
}