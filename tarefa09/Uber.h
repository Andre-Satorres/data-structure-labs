#ifndef Uber_H
#define Uber_H
#include "Heap.h"
#include "Passageiro.h"

typedef struct UberX {
    double aluguel, km_por_litro, custo_gasolina, taxa_uber, taxa_cancelamento, pagamento_por_km;
    int km_rodado_viagem, km_rodado_buscar_passageiro, cancelamentos;
    Coordenada posicao;
    p_passageiro passageiro_atual;
    p_heap corridas;
} UberX;

typedef UberX * Motorista_Uber;

/* Cria um Motorista_Uber a partir dos dados recebidos por parâmetro. */
Motorista_Uber criar_motorista_uber(double aluguel, double km_por_litro, double custo_gasolina, double taxa_uber, 
                                    double taxa_cancelamento, double pagamento_por_km, int max_corridas);

/* Destroi o Motorista_Uber recebido por parâmetro. */
Motorista_Uber destruir_motorista_uber(Motorista_Uber motorista_uber);

/* Motorista_Uber passado por parâmetro aceita a solicitação de viagem do Passageiro. */
void aceitar_solicitacao(Motorista_Uber motorista_uber, p_passageiro passageiro);

/* Verifica se o Motorista_Uber está com um Passageiro atualmente. */
int esta_com_passageiro(Motorista_Uber motorista_uber);

/* Finaliza a corrida atual do Motorista_Uber. */
void finalizar_corrida_atual(Motorista_Uber motorista_uber);

/* Cancela a corrida do passageiro com nome 'nome'. */
void cancelar_corrida(Motorista_Uber motorista_uber, char *nome);

/* Termina a jornada diária do Motorista_Uber e imprime os dados. */
Motorista_Uber terminar_jornada(Motorista_Uber motorista_uber);

/* Imprime um Motorista_Uber na tela. */
void imprimir_motorista_uber(Motorista_Uber motorista_uber);

#endif