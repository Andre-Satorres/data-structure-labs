#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 25
#define QTD_CATEGORIAS 5
#define SALTO 10
#define BOT 0
#define SURPREENDENTE 1
#define NORMAL 2
#define LOCAL 3
#define IRRELEVANTE 4

typedef struct termo {
    char *nome;
    double maximo, minimo, media, desvio_padrao;
} Termo;

typedef struct categoria {
    char *nome;
    int *posicao_termos;
    int qtd;
} Categoria;

void exibir_msg_erro() {
    printf("Não há memória suficiente!");
    exit(1);
}

void ler_nome_termo(Termo *termo) {
    termo->nome = malloc(MAX * sizeof(char));  // aloca os bytes na memoria
    if(termo->nome == NULL) exibir_msg_erro();  // temos que encerrar se nao tem memoria suficiente

    scanf("%s", termo->nome);  // le o nome do termo
}

void ler_valores(int m, Termo *termo, double *valores) {
    double valor;

    for(int j=0; j<m; j++) {
        scanf("%lf", &valor);

        if(j==0)
            termo->media = termo->maximo = termo->minimo = valor; //inicializando para o calculo
        else
            termo->media += valor;  // vamos colocando na media
        
        valores[j] = valor;  // armazena para calcular o desvio padrao posteriormente
        
        if(valor > termo->maximo)
            termo->maximo = valor;  // achar o maior

        if(valor < termo->minimo)
            termo->minimo = valor;  // achar o menor
    }

    termo->media /= m;  // obter a media de fato
}

void calcula_desvio_padrao(int m, Termo *termo, double *valores) {
    double somatorio = 0;
    for(int j=0; j<m; j++) 
        somatorio += pow(valores[j] - termo->media, 2); // calcular o somatorio do desvio padrao

    termo->desvio_padrao = sqrt(somatorio / m); // termino do calculo do desvio padrao
}

void ler_termo(Termo *termo, int m) {
    double *valores;
    valores = malloc(m * sizeof(double));

    if(valores == NULL) exibir_msg_erro(); // exit se nao tem memoria suficiente

    ler_nome_termo(termo);
    ler_valores(m, termo, valores);
    calcula_desvio_padrao(m, termo, valores);

    free(valores); // temos que dar free apos a alocação
}

char* obter_nome_categoria(int i) {
    if(i==BOT) return "Bot";
    if(i==SURPREENDENTE) return "Surpreendente";
    if(i==NORMAL) return "Normal";
    if(i==LOCAL) return "Local";
    return "Irrelevante";
}

int achar_indice_categoria(Termo termo) {
    if(termo.media >= 60) {
        if(termo.desvio_padrao > 15) // apenas seguindo as condicoes do enunciado
            return BOT;
        return SURPREENDENTE;
    }

    if(termo.maximo >= 80) {
        if(termo.minimo > 20)
            return NORMAL;
        return LOCAL;
    }

    return IRRELEVANTE;
}

void adiciona_na_categoria(Categoria *categorias, int posicao_termo, int indice_categoria) {
    Categoria *atual = &categorias[indice_categoria]; // para facilitar a escrita (atual ao inves de categorias[indice_categoria])

    if(atual->qtd % 10 == 0 && atual->qtd > 0) { // preciso fazer novo salto / alocar mais memoria 
        // vou usar SALTO, para nao dar realloc toda vez que for inserir um novo (poe SALTO de "gordura") e assim poupa tempo de execução
        atual->posicao_termos = realloc(atual->posicao_termos,(atual->qtd + SALTO) * sizeof(int));

        if(atual->posicao_termos == NULL) exibir_msg_erro();  // abortar o programa
    }

    atual->posicao_termos[atual->qtd] = posicao_termo; // saber qual posicao do vetor de termos pegar
    atual->qtd++;
}

void inicializa_categorias(Categoria *categorias) {
    for(int i=0; i<QTD_CATEGORIAS; i++) {
        categorias[i].nome = obter_nome_categoria(i);
        categorias[i].qtd = 0;
        categorias[i].posicao_termos = malloc(SALTO * sizeof(int));
    }
}

int ler_entrada(int n, int m, Termo *termos, Categoria *categorias) {
    Termo termo;
    int indice_categoria;

    for(int i=0; i<n; i++) {
        ler_termo(&termo, m);
        indice_categoria = achar_indice_categoria(termo);
        termos[i] = termo;
        adiciona_na_categoria(categorias, i, indice_categoria); // "adiciona" o termo lido na categoria que pertence
    }

    return n; //saber quantas linhas de saida
}

void imprimir_termos(int n, Termo *termos) {
    for(int i=0; i<n; i++)
        printf("%s %.2lf %.2lf %.2lf %.2lf\n", termos[i].nome, termos[i].maximo, termos[i].minimo, termos[i].media, termos[i].desvio_padrao);
}

void imprimir_categorias(Termo *termos, Categoria *categorias) {
    for(int i=0; i<QTD_CATEGORIAS; i++) {
        printf("%s (%d):", obter_nome_categoria(i), categorias[i].qtd);

        for(int j=0; j<categorias[i].qtd; j++)
            printf(" %s", termos[categorias[i].posicao_termos[j]].nome);

        printf("\n");
    }
}

void imprimir_saida(int n, Termo *termos, Categoria *categorias) {
    imprimir_termos(n, termos);
    printf("\nRESULTADO:\n");
    imprimir_categorias(termos, categorias);
}

void liberar_memoria(Termo *termos, Categoria *categorias, int n) {
    for(int i=0; i<n; i++) free(termos[i].nome);
    for(int i=0; i<QTD_CATEGORIAS; i++) free(categorias[i].posicao_termos); 
    // nao posso daar free no categorias->nome, pois apontam pra strings constantes/literais
    free(termos);
    free(categorias);
}

int main() {
    int n, m;
    Termo *termos;
    Categoria* categorias;

    scanf("%d %d", &n, &m);  // ler m e n

    termos = malloc(n * sizeof(Termo));
    if(termos == NULL) exibir_msg_erro();  // abortar em caso de falta de memoria

    categorias = malloc(QTD_CATEGORIAS * sizeof(Categoria));
    if(categorias == NULL) exibir_msg_erro();

    inicializa_categorias(categorias);
    ler_entrada(n, m, termos, categorias);
    imprimir_saida(n, termos, categorias);
    liberar_memoria(termos, categorias, n);
}