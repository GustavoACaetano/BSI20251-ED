#include "paciente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct paciente
{
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_nascimento[10];
};

struct pacienteList
{
    Paciente *pacientes;
    int tamanho;
    int capacidade;
};

PacientesList *pl_create() {
    PacientesList *pl = (PacientesList *) malloc(sizeof(PacientesList));
    if (pl == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }

    pl->tamanho = 0;
    pl->capacidade = 4;
    pl->pacientes = (Paciente *)malloc(pl->capacidade * sizeof(Paciente));
    if (pl->pacientes == NULL) {
        printf("Erro ao alocar memória\n");
        free(pl);
        return;
    }
    return pl;
}


PacientesList *pl_create_from_file(const char *filename) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) {
        return NULL;
        printf("Erro ao abrir o arquivo %s\n", filename);
    }
        

    PacientesList *pl = pl_create();
    char linha[200];
    int i = 0;
    while (fgets(linha, 200, f) != NULL) {
        Paciente p;
        sscanf(linha, "%d,%[^,],%[^,],%d,%s", &p.id, p.cpf, p.nome, &p.idade, p.data_nascimento);
        pl_insert(pl, p);
        // sscanf(linha, "%d,%[^,],%[^,],%d,%s", &pacientes[i].id, pacientes[i].cpf, pacientes[i].nome, &pacientes[i].idade, pacientes[i].data_nascimento);
        i++;
    }
    fclose(f);
    return pl;
}


static void reallocate(PacientesList *pl) {
    pl->capacidade *= 2;
    pl->pacientes = (Paciente *)realloc(pl->pacientes, pl->capacidade * sizeof(Paciente));
    if (pl->pacientes == NULL) {
        printf("Erro ao alocar memória\n");
        free(pl);
        return 1;
    }
}

void pl_insert(PacientesList *pl, Paciente p) {
    if (pl->tamanho == pl->capacidade)
        reallocate(pl);

    pl->pacientes[pl->tamanho++] = p;
}

int pl_size(PacientesList *pl) { return pl->tamanho; }

int pl_capacity(PacientesList *pl) { return pl->capacidade; }

Paciente pl_get(PacientesList *pl, int i) {
    assert(i >= 0 && i < pl->tamanho);
    return pl->pacientes[i];
}

void pl_free(PacientesList *pl) {
    free(pl->pacientes);
    free(pl);
}

void print_pacientes(PacientesList *pl) {
    printf("ID\tCPF\t\tNome\t\tIdade\tData de Nascimento\n");
    for (int i = 0; i < pl_size(pl); i++) {
        Paciente paciente = pl_get(pl, i);
        printf("%d\t%s\t%s\t%d\t%s\n", paciente.id, paciente.cpf, paciente.nome, paciente.idade, paciente.data_nascimento);
    }
    printf("================================================\n");
}

int prefix_cmp(const char *target, const char *src) {
    if (target == NULL || src == NULL) {
        return 0;
    }
    if (strlen(target) < strlen(src)) {
        return 0;
    }
    int i = 0;
    while (src[i] != '\0') {
        if (target[i] != src[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}


void pesquisar_nome(PacientesList *pl) {
    char nome[100];
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    int encontrado = 0;
    for (int i = 0; i < pl_size(pl); i++) {
        Paciente paciente = pl_get(pl, i);
        if (prefix_cmp(paciente.nome, nome)) {
            encontrado = 1;
            printf("%d\t%s\t%s\t%d\t%s\n", paciente.id, paciente.cpf, paciente.nome, paciente.idade, paciente.data_nascimento);
        }
    }
    if (!encontrado)
        printf("Nenhum paciente não encontrado\n");
}

void consultar_pacientes(PacientesList *pl) {
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");   
    printf("3 - Retornar ao menu principal\n");
    int menu;
    scanf("%d", &menu);
    while (menu != 3) {
        switch (menu) {
            case 1:
                pesquisar_nome(pl);
                break;
            case 2:
                printf("Função não implementada\n");
                break;
            case 3:
                break;
            default:
                printf("Opção inválida\n");
        }
        scanf("%d", &menu);
    }
}