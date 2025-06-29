#include "paciente.h"
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct paciente
{
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[10];
};

// Funcao para imprimir um paciente especifico
void print_paciente(const Paciente *p) {
    printf("%d\t%s\t%s\t%d\t%s\n", p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
}

Paciente *insert_paciente(const char *linha) {
    Paciente *p = (Paciente *) malloc(sizeof(Paciente));
    if (p == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }
    sscanf(linha, "%d,%[^,],%[^,],%d,%s", &p->id, p->cpf, p->nome, &p->idade, p->data_cadastro);
    return p;
}

void write_paciente(FILE *f, const Paciente *p) {
    fprintf(f, "%d,%s,%s,%d,%s\n", p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
}

int id_cmp(const Paciente *p, const int id) {
    return p->id == id;
}

int get_id(Paciente *p) {
    return p->id;
}

char *get_nome(Paciente *p) {
    return p->nome;
}

char *get_cpf(Paciente *p) {
    return p->cpf;
}

void set_nome(Paciente *p, const char *nome) {
    strcpy(p->nome, nome);
}

void set_cpf(Paciente *p, const char *cpf) {
    assert(strlen(cpf) < sizeof(p->cpf));
    strcpy(p->cpf, cpf);
}

void set_idade(Paciente *p, int idade) {
    if (idade < 0) {
        printf("Idade inválida.\n");
        return;
    }
    p->idade = idade;
}

void set_data_cadastro(Paciente *p, const char *data_cadastro) {
    assert(strlen(data_cadastro) < sizeof(p->data_cadastro));

    char inverted_data[11];
    snprintf(inverted_data, sizeof(inverted_data), "%.4s-%.2s-%.2s", data_cadastro + 6, data_cadastro + 3, data_cadastro);

    strcpy(p->data_cadastro, inverted_data);
}


Paciente *create_paciente(int id, const char *cpf, const char *nome, int idade, const char *data_cadastro) {
    Paciente *p = (Paciente *) malloc(sizeof(Paciente));
    if (p == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    p->id = id;
    set_cpf(p, cpf);
    set_nome(p, nome);
    p->idade = idade;
    strcpy(p->data_cadastro, data_cadastro);

    return p;
}
