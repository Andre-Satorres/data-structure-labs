#include "professor_carlos.h"
#include <stdio.h>
#define MAX_S 5

Aluno le_aluno() {
    Aluno a;
    scanf("%s %s %d %d %d", a.nome, a.sobrenome, &a.nascimento.dia, &a.nascimento.mes, &a.nascimento.ano); // le as infos do aluno
    return a; //retorna o aluno criado
}

void realizar_operacao(Turma t[], int qtd_turmas, int operacao) {
    if(operacao < 3 || operacao > 5) {
        int j;
        scanf("%d", &j); // saber a turma
        if(operacao == 1) 
            printf("%s\n", procura_novo_na_turma(t, qtd_turmas, j).nome);
        else if(operacao == 2) 
            printf("%s\n", procura_velho_na_turma(t, qtd_turmas, j).sobrenome);
        else if(operacao == 6)
            printf("%d\n", add_aluno(t, le_aluno(), j));
        else if(operacao == 7)
            printf("%d\n", remove_aluno(t, j));
    } 
    else if(operacao == 3)
        printf("%s\n", procura_velho_todas_turmas(t, qtd_turmas).nome);
    else if(operacao == 4)
        printf("%s\n", procura_novo_todas_turmas(t, qtd_turmas).sobrenome);
    else if(operacao == 5) {
        char s[5];
        scanf("%s", s);
        printf("%d\n", conta_substrings(t, qtd_turmas, s));
    }
}

void le_turmas(int n, int k, Turma turmas[]) {
    int m;

    for(int i=0; i<n; i++) {
        turmas[i].qtd = 0;  /* inicializando o valor */
        scanf("%d", &m);
        for(int j=0; j<m; j++)
            add_aluno(turmas, le_aluno(), i); // vai adicionando os alunos iniciais
    }
}

int main() {
    int n, k, operacao;  /* n = qtd_turmas, k = qtd_operacoes */
    Turma turmas[50];
    
    scanf("%d %d", &n, &k); /* le a qtd de turmas e a qtd de operacoes */
    le_turmas(n, k, turmas);
    
    for(int i=0; i<k; i++) {
        scanf("%d", &operacao);
        realizar_operacao(turmas, n, operacao); //realiza as k operacoes
    }
}