typedef struct No {
    unsigned int digito;
    struct No *prox;
} No;

/* Esse TAD é uma lista ligada que representa um número grande 
de maneira inversa. Ou seja, se quisermos armazenar 1234567, 
ele será representado como 7->6->5->4->3->2->1. */
typedef No* NumeroGrande;

/* Inicializa um NumeroGrande. */
NumeroGrande criar_numero_grande(NumeroGrande numeroGrande);

/* Destroi, liberando da memória, um NumeroGrande. */
void destruir_numero_grande(NumeroGrande numeroGrande);

/* Insere um dígito no ínicio do NumeroGrande, into é, à direita. */
NumeroGrande inserir_no_inicio(NumeroGrande numeroGrande, int info);

/* Inverte o NumeroGrande (de 7->6->5->4->3->2->1 para 1->2->3->4->5->6->7). */
NumeroGrande inverter(NumeroGrande numeroGrande);

/* Copia todos os dígitos de um NumeroGrande para outro e retorna essa cópia. */
NumeroGrande copiar(NumeroGrande numeroGrande);

/* Retorna 0 se numeroGrande1 é igual ao numerogrande2, < 0 se o segundo 
   é maior e > 0 se o primeiro é maior. */
int comparar(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2);

/* Soma dois números grandes. */
NumeroGrande somar(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2);

/* Subtrai dois números grandes. */
NumeroGrande subtrair(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2);

/* Multiplica dois números grandes. */
NumeroGrande multiplicar(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2);

/* Divide dois números grandes (divisão inteira). */
NumeroGrande dividir(NumeroGrande numeroGrande1, NumeroGrande numeroGrande2);
