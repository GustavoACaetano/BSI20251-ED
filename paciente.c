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

struct pacientesDynVec
{
    Paciente *pacientes;
    int tamanho;
    int capacidade;
};

// Funcao para criar um vetor dinamico de pacientes
PacientesDynVec *pdv_create() {
    PacientesDynVec *pdv = (PacientesDynVec *) malloc(sizeof(PacientesDynVec));
    if (pdv == NULL) {
        printf("Erro ao alocar memória\n");
        return 0;
    }

    pdv->tamanho = 0;
    pdv->capacidade = 4;
    pdv->pacientes = (Paciente *)malloc(pdv->capacidade * sizeof(Paciente));
    if (pdv->pacientes == NULL) {
        printf("Erro ao alocar memória\n");
        free(pdv);
        return 0;
    }
    return pdv;
}


// Funcao para criar um vetor dinamico de pacientes a partir de um arquivo
PacientesDynVec *pdv_create_from_file(const char *filename) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    PacientesDynVec *pdv = pdv_create();
    char linha[200];
    int i = 0;
    while (fgets(linha, 200, f) != NULL) {
        Paciente p;
        sscanf(linha, "%d,%[^,],%[^,],%d,%s", &p.id, p.cpf, p.nome, &p.idade, p.data_nascimento);
        pdv_insert(pdv, p);
        i++;
    }
    fclose(f);
    return pdv;
}


// Funcao local para realocar memoria
static void reallocate(PacientesDynVec *pdv) {
    pdv->capacidade *= 2;
    pdv->pacientes = (Paciente *)realloc(pdv->pacientes, pdv->capacidade * sizeof(Paciente));
    if (pdv->pacientes == NULL) {
        printf("Erro ao alocar memória\n");
        free(pdv);
        return;
    }
}

// Funcao para inserir um paciente 
void pdv_insert(PacientesDynVec *pdv, Paciente p) {
    if (pdv->tamanho == pdv->capacidade)
        reallocate(pdv);

    pdv->pacientes[pdv->tamanho++] = p;
}

// Funcao para retornar o tamanho do vetor
int pdv_size(const PacientesDynVec *pdv) { return pdv->tamanho; }

// Funcao para retornar a capacidade do vetor
int pdv_capacity(const PacientesDynVec *pdv) { return pdv->capacidade; }

// Funcao para retornar um paciente especifico a partir do indice
Paciente pdv_get(const PacientesDynVec *pdv, int i) {
    assert(i >= 0 && i < pdv->tamanho);
    return pdv->pacientes[i];
}

// Funcao para liberar a memoria do vetor dinamico
void pdv_free(PacientesDynVec *pdv) {
    free(pdv->pacientes);
    free(pdv);
}

// Funcao para imprimir todos os pacientes de um vetor
void print_pacientes(const PacientesDynVec *pdv) {
    printf("ID\tCPF\t\tNome\t\tIdade\tData de Nascimento\n");
    // Passa por tds os pacientes imprimindo
    for (int i = 0; i < pdv_size(pdv); i++) {
        Paciente paciente = pdv_get(pdv, i);
        printf("%d\t%s\t%s\t%d\t%s\n", paciente.id, paciente.cpf, paciente.nome, paciente.idade, paciente.data_nascimento);
    }
    printf("================================================\n");
}

// Funcao local para identificar se a string eh um prefixo
static int prefix_cmp(const char *target, const char *src) {
    // Validacao das strings
    if (target == NULL || src == NULL) {
        return 0;
    }
    if (strlen(target) < strlen(src)) {
        return 0;
    }

    // Verificacao do prefixo
    int i = 0;
    while (src[i] != '\0') {
        if (target[i] != src[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

// Funcao local para imprimir um header das informacoes do paciente
static void print_header() {
    printf("\nID\tCPF\t\t\t\tNome\tIdade\tData_Cadastro\n");
}

// Funcao local para imprimir um paciente especifico
static void print_paciente(const Paciente p) {
    printf("%d\t%s\t%s\t%d\t%s\n", p.id, p.cpf, p.nome, p.idade, p.data_nascimento);
}

// Funcao generica para pesquisar pacientes
void pesquisar_campo(const PacientesDynVec *pdv, char *valor_buscar, int campo) {
    int encontrado = 0;

    // Repeticao por todo o tamanho do vetor dinamico
    for (int i = 0; i < pdv_size(pdv); i++) {
        // Para cada paciente do vetor sera feita a verificacao
        // com base no campo passado
        // 1 = nome, 2 = cpf (mesmos valores do menu)
        Paciente paciente = pdv_get(pdv, i);
        int prefixo = 0;
        switch (campo) {
            case 1:
                prefixo = prefix_cmp(paciente.nome, valor_buscar);
                break;
            case 2:
                prefixo = prefix_cmp(paciente.cpf, valor_buscar);
                break;
            default:
                printf("Campo de busca inválido!");
                return;
        }

        // Sendo prefixo, deve-se imprimir as informacoes do paciente
        if (prefixo) {
            // O header so sera impresso no primeiro registro desse momento de busca
            if (!encontrado) {
                encontrado = 1;
                print_header();
            }
            print_paciente(paciente);
        }
    }
    if (!encontrado)
        printf("Nenhum paciente encontrado\n");
}

// Funcao para pesquisar especificamente pelo nome
void pesquisar_nome(const PacientesDynVec *pdv) {
    char nome[100];
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    pesquisar_campo(pdv, nome, 1);
}

// Funcao para pesquisar especificamente pelo cpf
void pesquisar_cpf(const PacientesDynVec *pdv) {
    char cpf[14];
    printf("Digite o cpf do paciente com pontos e hífen no formato correto (xxx.xxx.xxx-xx): ");
    scanf("%s", cpf);
    pesquisar_campo(pdv, cpf, 2);
}

// Funcao local para imprimir o menu de consulta
static void print_menu_consulta() {
    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
}

// Funcao para o loop de busca
void consultar_pacientes(const PacientesDynVec *pdv) {
    print_menu_consulta();
    char menu;
    scanf(" %c", &menu);
    while (menu != '3') {
        switch (menu) {
            case '1':
                pesquisar_nome(pdv);
                break;
            case '2':
                pesquisar_cpf(pdv);
                break;
            case '3':
                break;
            default:
                printf("Opção inválida!\n");
        }
        print_menu_consulta();
        scanf(" %c", &menu);
    }
}