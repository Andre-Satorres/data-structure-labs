#include "professor_carlos.h"

/* Retorna 0 se d1 eh a mesma data que d2, 
 * <0 se d1 é mais antigo (menor) que d2 e 
 * >0 se d1 é mais recente (maior) que d2 */
int comparar_data(Data d1, Data d2) {
    if(d1.ano != d2.ano) return d1.ano - d2.ano; // <0 se d1.ano < d2.ano e >0 se d1.ano > d2.ano
    if(d1.mes != d2.mes) return d1.mes - d2.mes; // mesmo que o acima
    return d1.dia - d2.dia; // 0 se d1.dia == d2.dia (e mes e ano ja eram iguais)
}

int str_length(char str[]) {
    int i;
    for(i=0; str[i] != '\0'; i++);
    return i;
}

/* Retorna 0 se s1 eh igual a s2, 
 * <0 se s1 é menor lexicograficamente que s2 e 
 * >0 se s1 é maior lexicograficamente que s2 */
int comp_str(char s1[], char s2[]) {
    int i=0;
    while(s1[i] != '\0' && s1[i] == s2[i]) i++;
    return s1[i] - s2[i]; // 0 se s1[i] == s2[i]
}

/* Retorna 0 (falso) se substr nao for substring de str, e 
 * retorna 1 (diferente de 0 = true) caso contrario. */
int eh_substring(char str[], char substr[]) {
    int i, j, matched;
    j = matched = 0;

    for(i=0; substr[i] != '\0'; i++, j++) {
        if(str[j] != substr[i]) 
            i = matched = 0; /* false */
        
        while(str[j] != substr[i] && str[j] != '\0') 
            j++;
        
        if(str[j] == '\0') 
            return 0; /* chegou no final de str e nao tem substr[i] */

        matched++;
    }

    return str_length(substr) == matched; /* !=0 (true) se deu match na substr inteira */
}

Aluno obter_por_desempate(Aluno a1, Aluno a2) {
    int res = comp_str(a1.nome, a2.nome); /* salvo em variavel para nao ter que chamar a funcao mais de uma vez */
    return res < 0 ? a1 : res > 0 ? a2 : comp_str(a1.sobrenome, a2.sobrenome) <= 0 ? a1 : a2;
}

Aluno obter_mais_novo(Aluno a1, Aluno a2) {
    int compara = comparar_data(a1.nascimento, a2.nascimento);

    if(compara < 0) /* a2 eh mais novo que a1 */
        return a2;
    
    if(compara > 0) /* a1 eh mais novo que a2 */
        return a1;

    return obter_por_desempate(a1, a2);
}

Aluno obter_mais_velho(Aluno a1, Aluno a2) {
    int compara = comparar_data(a1.nascimento, a2.nascimento);

    if(compara < 0) /* a1 eh mais velho que a2*/
        return a1;
    
    if(compara > 0) /* a2 eh mais velho que a1 */
        return a2;

    return obter_por_desempate(a1, a2);
}

/* A funcao recebe todas as turmas e o indice da turma escolhida,
 * retornando o aluno mais velho se o_mais_novo == 0 (false), ou
 * o aluno mais novo se o_mais_novo != 0 (true) da turma escolhida. */
Aluno procura_na_turma(Turma t[], int qtd_turmas, int j, int o_mais_novo) {
    Aluno ret;
    if (j < qtd_turmas) {
        for(int i=0; i<t[j].qtd; i++)
            if(i == 0)
                ret = t[j].alunos[i];
            else if(o_mais_novo) /* diferente de 0 */
                ret = obter_mais_novo(ret, t[j].alunos[i]);
            else /* o_mais_novo == 0 (falso) */
                ret = obter_mais_velho(ret, t[j].alunos[i]);
    }

    return ret;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j) {
    return procura_na_turma(t, qtd_turmas, j, 1); /* como 1 != 0, vou procurar o + novo */
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j) {
    return procura_na_turma(t, qtd_turmas, j, 0); /* como 0 == 0, vou procurar o + velho */
}

Aluno procura_todas_turmas(Turma t[], int qtd_turmas, int o_mais_novo) {
    Aluno ret;
    for(int i=0; i<qtd_turmas; i++) /* percorrer cada turma */
        if(i == 0) {
            if(o_mais_novo)
                ret = procura_novo_na_turma(t, qtd_turmas, i);
            else
                ret = procura_velho_na_turma(t, qtd_turmas, i);
        }
        else if(o_mais_novo) /* diferente de 0 */
            ret = obter_mais_novo(ret, procura_novo_na_turma(t, qtd_turmas, i));
        else /* o_mais_novo == 0 */
            ret = obter_mais_velho(ret, procura_velho_na_turma(t, qtd_turmas, i));

    return ret;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas) {
    return procura_todas_turmas(t, qtd_turmas, 1); /* como 1 != 0, vou procurar o + novo */
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas) {
    return procura_todas_turmas(t, qtd_turmas, 0); /* como 0 == 0, vou procurar o + velho */
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao) {
    int conta = 0;
    for(int i = 0; i<qtd_turmas; i++) /* percorre todas as turmas */
        for(int j=0; j<t[i].qtd && j<50; j++) /* percorre todos os alunos da turma i */
            if(eh_substring(t[i].alunos[j].nome, padrao))
                conta++;

    return conta;
}

int add_aluno(Turma t[], Aluno A, int j) {
    t[j].alunos[t[j].qtd] = A;
    return ++t[j].qtd;
}

int remove_aluno(Turma t[], int j) {
    return t[j].qtd > 0 ? --t[j].qtd : t[j].qtd;
}