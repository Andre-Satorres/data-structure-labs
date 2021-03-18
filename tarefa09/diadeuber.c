#include "Uber.h"

#define CUSTO_ALUGUEL 57.00
#define KM_POR_LITRO 10
#define CUSTO_POR_LITRO_GASOLINA 4.104

#define TAXA_UBER 0.25
#define TAXA_CANCELAMENTO_REAIS 7
#define PAGAMENTO_POR_KM 1.40

#define MAX_ACOES 500
#define MAX_NOME 16

#define ACEITAR_CORRIDA 'A'
#define CANCELAR_CORRIDA 'C'
#define FINALIZAR_CORRIDA 'F'
#define TERMINAR 'T'


p_passageiro ler_passageiro() {
    char nome[MAX_NOME];
    double estrelas;
    int posicao_x, posicao_y, destino_x, destino_y;

    scanf("%s %lf %d %d %d %d", nome, &estrelas, &posicao_x, &posicao_y, &destino_x, &destino_y);
    return criar_passageiro(nome, estrelas, posicao_x, posicao_y, destino_x, destino_y);
}

Motorista_Uber criar_motorista_uber_default() {
    return criar_motorista_uber(CUSTO_ALUGUEL, KM_POR_LITRO, CUSTO_POR_LITRO_GASOLINA, TAXA_UBER, TAXA_CANCELAMENTO_REAIS, PAGAMENTO_POR_KM, MAX_ACOES);
}

int main() {
    Motorista_Uber motorista_uber = criar_motorista_uber_default();
    p_passageiro passageiro;
    char acao, nome[MAX_NOME];

    for(;;) {
        scanf(" %c", &acao);
        
        switch (acao) {
            case ACEITAR_CORRIDA:
                passageiro = ler_passageiro();
                aceitar_solicitacao(motorista_uber, passageiro);
                free(passageiro);
                break;
            case CANCELAR_CORRIDA:
                scanf("%s", nome);
                cancelar_corrida(motorista_uber, nome);
                break;
            case FINALIZAR_CORRIDA:
                finalizar_corrida_atual(motorista_uber);
                break;
            case TERMINAR:
                printf("\n");
                motorista_uber = terminar_jornada(motorista_uber);
                return 0;
            default:
                break;
        }
    }
}