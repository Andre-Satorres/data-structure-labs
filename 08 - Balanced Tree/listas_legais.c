#include "Lista_Legal.h"

enum Opcoes { INSERCAO, QTD_COPIAS, QUANTOS_REMOVER };

Lista_Legal inserir_numeros_iniciais(Lista_Legal l, int qtd) {
    unsigned long long num;

    for(int i=0; i<qtd; i++) {
        if(scanf("%llu", &num))
            l = inserir_numero_legal(l, num);
    }

    return l;
}

Lista_Legal realizar_operacao(Lista_Legal l, int operacao) {
    unsigned long long num;

    switch (operacao) {
        case INSERCAO:
            if(scanf("%llu", &num))
                l = inserir_numero_legal(l, num);
            break;
        case QTD_COPIAS:
            if(scanf("%llu", &num))
                printf("%llu\n", quantidade_ocorrencias(l, num));
            break;
        case QUANTOS_REMOVER:
            printf("%d\n", quantos_remover_para_ser_legal(l));
        default:
            break;
    }

    return l;
}

int main() {
    int n, k, operacao;

    if(scanf("%d %d", &n, &k)) {
        Lista_Legal l = criar_lista_legal();
        l = inserir_numeros_iniciais(l, n);

        for(int i=0; i<k; i++) {
            if(scanf("%d", &operacao))
                l = realizar_operacao(l, --operacao); // --, porque, no enum, vai ser { 0, 1, 2 }
        }

        l = destruir_lista_legal(l);
    }

    return 0;
}