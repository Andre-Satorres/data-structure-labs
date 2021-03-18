#include "Saco_de_Cartoes.h"

void le_numero_texto(unsigned int *numero_cartao, char *texto) {
    scanf("%u \"%[^\"]\"", numero_cartao, texto);
}

void le_qtd_autoridades(unsigned int * numero_autoridade) {
    scanf("%u", numero_autoridade);
}

int main() {
    Saco saco_de_cartoes;
    unsigned int qtd_cartoes, qtd_autoridades;

    while(scanf("%u %u", &qtd_cartoes, &qtd_autoridades) != EOF) {
        saco_de_cartoes = criar_saco();
        saco_de_cartoes = preencher_saco(saco_de_cartoes, qtd_cartoes, le_numero_texto); // coloca os cartoes na ABB
        saco_de_cartoes = trocar_com_autoridades(saco_de_cartoes, qtd_autoridades, le_qtd_autoridades); // faz as trocas de triades de cartoes com autoridades
        saco_de_cartoes = preparar_mensagem(saco_de_cartoes); // junta o resto dos cartoes

        mostrar_mensagem(saco_de_cartoes); // imprime a mensagem contida no ultimo cartao restante da arvore
        printf("\n");

        saco_de_cartoes = destruir_saco(saco_de_cartoes);
    }

    return 0;
}