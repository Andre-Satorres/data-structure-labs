#include "Passageiro.h"
#include "Utils.h"
#include <string.h>

p_passageiro criar_passageiro(char *nome, double estrelas, int posicao_x, int posicao_y, int destino_x, int destino_y) {
    p_passageiro p = novo_ponteiro(sizeof(Passageiro));

    if(strlen(nome) > 15) {
        printf("Nome inválido!");
        exit(1);
    }
    
    strcpy(p->nome, nome);
    p->estrelas = estrelas;
    p->posicao = nova_coordenada(posicao_x, posicao_y);
    p->destino = nova_coordenada(destino_x, destino_y);
    return p;
}

p_passageiro copiar_passageiro(p_passageiro p) {
    return criar_passageiro(p->nome, p->estrelas, p->posicao.x, p->posicao.y, p->destino.x, p->destino.y);
}

int comparar_por_estrelas(p_passageiro p1, p_passageiro p2) {
    if(p1 == p2)
        return 0;

    if(p1 == NULL)
        return -1;

    if(p2 == NULL)
        return 1;

    if(p1->estrelas > p2->estrelas)
        return 1;

    if(p1->estrelas < p2->estrelas)
        return -1;

    return 0;
}

int comparar_passageiro_com_campo_nome(p_passageiro p, char *nome) {
    return strcmp(p->nome, nome);
}

void imprimir_passageiro(p_passageiro p) {
    printf("Passageiro{nome=%s, estrelas=%lf, posicao=", p->nome, p->estrelas);
    imprimir_coordenada(p->posicao);
    printf(", destino=");
    imprimir_coordenada(p->destino);
    printf("}");
}