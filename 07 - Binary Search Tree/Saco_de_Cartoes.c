#include "Saco_de_Cartoes.h"

int comparar_cartao_por_numero_generico(void *cartao1, void *cartao2) {
    return comparar_cartao_por_numero(cartao1, cartao2);
}

void * copiar_cartao_generico(void *cartao) {
    return copiar_cartao(cartao);
}

void destruir_cartao_generico(void *cartao) {
    destruir_cartao(cartao);
}

void * juntar_cartoes_generico(void *cartao1, void *cartao2) {
    return juntar_cartoes(cartao1, cartao2);
}

void imprimir_cartao_generico(void *cartao) {
    imprimir_cartao(cartao);
}

Saco criar_saco() {
    return NULL;
}

Saco destruir_saco(Saco saco) {
    return destruir_abb(saco, destruir_cartao_generico);
}

Saco preencher_saco(Saco saco, unsigned int qtd_cartoes, void (*fle)(unsigned int *, char *)) {
    unsigned int numero_cartao;
    char *texto = novo_ponteiro(sizeof(char) * MAX_TEXTO);

    for(unsigned int i=0; i<qtd_cartoes; i++) {
        fle(&numero_cartao, texto);
        saco = inserir_no_saco(saco, numero_cartao, texto);
    }

    free(texto);
    return saco;
}

Saco inserir_no_saco(Saco saco, unsigned int numero, char *texto) {
    p_cartao cartao = criar_cartao(numero, texto);
    saco = inserir_na_abb(saco, cartao, copiar_cartao_generico, comparar_cartao_por_numero_generico);
    destruir_cartao(cartao);
    return saco;
}

Saco remover_do_saco(Saco saco, p_cartao cartao) {
    return remover_da_abb(saco, cartao, copiar_cartao_generico, comparar_cartao_por_numero_generico, destruir_cartao_generico);
}

p_cartao juntar_triade(p_cartao cartao1, p_cartao cartao2, p_cartao cartao3) {
    p_cartao concat = juntar_cartoes(cartao1, cartao2);
    p_cartao concat2 = juntar_cartoes(concat, cartao3);
    destruir_cartao(concat);
    return concat2;
}

/* Troca os tres Cartoes recebidos por parametro por um novo Cartao que eh a juncao dos tres e insere no Saco. */
Saco trocar_triade(Saco saco, p_cartao cartao1, p_cartao cartao2, p_cartao cartao3) {
    p_cartao troca = juntar_triade(cartao3, cartao2, cartao1); // cartao3 "primeiro", pois concatenaremos do menor para o maior (e cartao3 < cartao2 < cartao1)
    
    // TEM que ser nessa ordem, pois, ao remover cartao3 (ou cartao2), podemos acabar removendo cartao1 (ou cartao2) e copiando a info para cartao3 (ou cartao2).
    saco = remover_do_saco(saco, cartao1);
    saco = remover_do_saco(saco, cartao2);
    saco = remover_do_saco(saco, cartao3);

    saco = inserir_no_saco(saco, troca->numero, troca->texto);

    destruir_cartao(troca);
    return saco;
}

/* Procura uma triade de Cartoes no Saco cuja soma dos numeros eh 'numero', e retorna os nos por referencia
usando n1, n2 e n3. */
void procurar_triade(Saco saco, unsigned int numero, p_no *n1, p_no *n2, p_no *n3) {
    p_cartao aux = criar_cartao(numero, "");

    while(!*n2) {
        *n1 = maximo_menor_que(saco, aux, comparar_cartao_por_numero_generico);

        if(*n1 == NULL) { // nao há numeros menores que 'numero' na arvore
            destruir_cartao(aux);
            return; // nao consegui formar uma soma
        }

        unsigned int numero1 = ((p_cartao)(*n1)->info)->numero;
        aux->numero = numero - numero1;

        while(!*n3) {
            if(aux->numero > numero1)
                *n2 = maximo_menor_que(saco, (*n1)->info, comparar_cartao_por_numero_generico);
            else
                *n2 = maximo_menor_que(saco, aux, comparar_cartao_por_numero_generico);

            if(*n2 == NULL) {
                aux->numero = numero1;
                break;
            }

            unsigned int numero2 = ((p_cartao)(*n2)->info)->numero;
            aux->numero = numero - numero1 - numero2;
            *n3 = buscar_na_abb(saco, aux, comparar_cartao_por_numero_generico);

            if(*n3 == NULL)
                aux->numero = ((p_cartao)(*n2)->info)->numero;
        }
    }

    destruir_cartao(aux);
}

p_no trocar_com_autoridades(Saco saco_de_cartoes, unsigned int qtd_autoridades, void (*fle)(unsigned int *)) {
    unsigned int numero_autoridade;
    for(unsigned int i=0; i<qtd_autoridades; i++) {
        fle(&numero_autoridade);
        saco_de_cartoes = trocar_com_autoridade(saco_de_cartoes, numero_autoridade);
    }

    return saco_de_cartoes;
}

Saco trocar_com_autoridade(Saco saco, unsigned int numero_da_autoridade) {
    p_no n1, n2, n3;
    n1 = n2 = n3 = NULL;

    procurar_triade(saco, numero_da_autoridade, &n1, &n2, &n3);

    if(n1 == NULL) // nao foi possivel achar
        return saco;

    // se n1 nao eh NULL, entao nenhum eh NULL (achei a triade para o numero_da_autoridade)
    return trocar_triade(saco, n1->info, n2->info, n3->info);
}

Saco preparar_mensagem(Saco saco) {
    return juntar_todos(saco, juntar_cartoes_generico, destruir_cartao_generico);
}

void mostrar_mensagem(Saco saco) {
    if(saco) {
        p_cartao cartao_final = saco->info;
        imprimir_texto(cartao_final);
    }
}

void imprimir_saco(Saco saco) {
    imprimir_abb(saco, imprimir_cartao_generico);
}