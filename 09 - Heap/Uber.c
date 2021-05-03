#include "Uber.h"
#include <string.h>

int comparar_por_estrelas_generico(Any p1, Any p2) {
    return comparar_por_estrelas(p1, p2);
}

Any copiar_passageiro_generico(Any p) {
    return copiar_passageiro(p);
}

int comparar_passageiro_com_campo_nome_generico(Any p, Any nome) {
    return comparar_passageiro_com_campo_nome(p, nome);
}

void imprimir_passageiro_generico(Any p) {
    imprimir_passageiro(p);
}

int esta_com_passageiro(Motorista_Uber motorista_uber) {
    return motorista_uber->passageiro_atual != NULL;
}

Motorista_Uber criar_motorista_uber(double aluguel, double km_por_litro, double custo_gasolina, double taxa_uber, 
                                    double taxa_cancelamento, double pagamento_por_km, int max_corridas) {
    Motorista_Uber motorista_uber = novo_ponteiro(sizeof(UberX));
    motorista_uber->aluguel = aluguel;
    motorista_uber->km_por_litro = km_por_litro;
    motorista_uber->custo_gasolina = custo_gasolina;
    motorista_uber->taxa_uber = taxa_uber;
    motorista_uber->taxa_cancelamento = taxa_cancelamento;
    motorista_uber->pagamento_por_km = pagamento_por_km;
    
    motorista_uber->km_rodado_viagem = motorista_uber->km_rodado_buscar_passageiro = motorista_uber->cancelamentos = 0;
    motorista_uber->posicao = nova_coordenada(0, 0);
    motorista_uber->passageiro_atual = NULL;

    motorista_uber->corridas = criar_heap(max_corridas, sizeof(Passageiro), comparar_por_estrelas_generico);
    return motorista_uber;
}

Motorista_Uber destruir_motorista_uber(Motorista_Uber motorista_uber) {
    if(motorista_uber == NULL)
        return NULL;

    destruir_heap(motorista_uber->corridas, free);

    if(esta_com_passageiro(motorista_uber))
        free(motorista_uber->passageiro_atual);

    free(motorista_uber);
    return NULL;
}

void buscar_proximo_passageiro(Motorista_Uber motorista_uber) {
    if(motorista_uber->corridas->n > 0 && !esta_com_passageiro(motorista_uber)) {
        p_passageiro passageiro = extrair_maximo(motorista_uber->corridas);
        motorista_uber->km_rodado_buscar_passageiro += distancia(motorista_uber->posicao, passageiro->posicao);
        motorista_uber->posicao = passageiro->posicao;
        motorista_uber->passageiro_atual = passageiro;
    }
}

void aceitar_solicitacao(Motorista_Uber motorista_uber, p_passageiro passageiro) {
    if(motorista_uber == NULL || passageiro == NULL)
        return;

    adicionar_no_heap(motorista_uber->corridas, passageiro, copiar_passageiro_generico);
    buscar_proximo_passageiro(motorista_uber);
    printf("Cliente %s foi adicionado(a)\n", passageiro->nome);
}

void finalizar_corrida_atual(Motorista_Uber motorista_uber) {
    if(motorista_uber == NULL)
        return;

    p_passageiro passageiro;
    
    if(esta_com_passageiro(motorista_uber))
        passageiro = motorista_uber->passageiro_atual;
    else
        passageiro = extrair_maximo(motorista_uber->corridas);

    if(passageiro == NULL)
        return;

    motorista_uber->km_rodado_viagem += distancia(motorista_uber->posicao, passageiro->destino);
    motorista_uber->posicao = passageiro->destino;

    printf("A corrida de %s foi finalizada\n", passageiro->nome);

    if(esta_com_passageiro(motorista_uber)) {
        free(motorista_uber->passageiro_atual);
        motorista_uber->passageiro_atual = NULL;
        buscar_proximo_passageiro(motorista_uber);
    }
}

void cancelar_corrida(Motorista_Uber motorista_uber, char *nome) {
    int pos = buscar_posicao_por_campo(motorista_uber->corridas, nome, comparar_passageiro_com_campo_nome_generico);
    if(pos < 0) {
        printf("Este cliente não existe!\n");
        return;
    }

    if(comparar_por_estrelas(motorista_uber->passageiro_atual, motorista_uber->corridas->v[pos]) == 0) {
        free(motorista_uber->passageiro_atual);
        motorista_uber->passageiro_atual = NULL;
    }

    remover_do_heap(motorista_uber->corridas, pos, free);
    motorista_uber->cancelamentos++;
    printf("%s cancelou a corrida\n", nome);
}

int total_km_rodado(Motorista_Uber motorista_uber) {
    return motorista_uber->km_rodado_buscar_passageiro + motorista_uber->km_rodado_viagem;
}

double calcular_rendimento_bruto(Motorista_Uber motorista_uber) {
    return motorista_uber->pagamento_por_km * motorista_uber->km_rodado_viagem + (7 * motorista_uber->cancelamentos);
}

double calcular_despesas(Motorista_Uber motorista_uber) {
    double total_litros = total_km_rodado(motorista_uber) / motorista_uber->km_por_litro;
    double total_gasolina = motorista_uber->custo_gasolina * total_litros;
    return total_gasolina + motorista_uber->aluguel;
}

double calcular_rendimento_liquido(Motorista_Uber motorista_uber) {
    double rendimento_bruto = calcular_rendimento_bruto(motorista_uber);
    return rendimento_bruto - rendimento_bruto/4 - calcular_despesas(motorista_uber);
}

Motorista_Uber terminar_jornada(Motorista_Uber motorista_uber) {
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", total_km_rodado(motorista_uber));
    printf("Rendimento bruto: %.2lf\n", calcular_rendimento_bruto(motorista_uber));
    printf("Despesas: %.2lf\n", calcular_despesas(motorista_uber));
    printf("Rendimento liquido: %.2lf\n", calcular_rendimento_liquido(motorista_uber));

    return destruir_motorista_uber(motorista_uber);
}

void imprimir_motorista_uber(Motorista_Uber motorista_uber) {
    printf("Motorista_Uber{aluguel=%.2lf, km_por_litro=%.2lf, custo_gasolina=%.2lf, taxa_uber=%.2lf, taxa_cancelamento=%.2lf, ", 
    motorista_uber->aluguel, motorista_uber->km_por_litro, motorista_uber->custo_gasolina, motorista_uber->taxa_uber, motorista_uber->taxa_cancelamento);

    printf("pagamento_por_km=%.2lf, km_rodado_buscar_passageiro=%d, km_rodado_viagem=%d, cancelamentos=%d, posicao=", 
    motorista_uber->pagamento_por_km, motorista_uber->km_rodado_buscar_passageiro, motorista_uber->km_rodado_viagem, motorista_uber->cancelamentos);

    imprimir_coordenada(motorista_uber->posicao);
    printf(", corridas=");
    imprimir_heap(motorista_uber->corridas, imprimir_passageiro_generico);
    printf("}");
}