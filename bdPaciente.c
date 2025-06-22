#include "paciente.h"
#include "bdPaciente.h"
#include "prefix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct pacienteNode {
    Paciente *paciente;
    PacienteNode *next;
    PacienteNode *prev;
};

struct bdPaciente {
    int count;
    PacienteNode *first;
    PacienteNode *last;
};

// Funcao para criar uma lista encadeada de pacientes
BDPaciente *pL_create() {
    BDPaciente *pL = (BDPaciente *) malloc(sizeof(BDPaciente));
    if (pL == NULL) {
        printf("Erro ao alocar memória\n");
        return 0;
    }

    pL->count = 0;
    pL->first = NULL;
    pL->last = NULL;
    return pL;
}

// Funcao para criar um node da lista
PacienteNode *pN_create(Paciente *p) {
    PacienteNode *pN = (PacienteNode *) malloc(sizeof(PacienteNode));
    if (pN == NULL) {
        printf("Erro ao alocar memória\n");
        return 0;
    }

    pN->paciente = p;
    pN->prev = NULL;
    pN->next = NULL;
    return pN;
}

// Funcao para inserir um node na lista
void pL_insert(BDPaciente *pL, Paciente *p) {
    PacienteNode *pN = pN_create(p);

    if (pL->last == NULL) {
        pL->first = pN;
    } else {
        pN->prev = pL->last;
        pL->last->next = pN;
    }
    pL->count++;
    pL->last = pN;
}

// Funcao para criar uma lista de pacientes a partir de um arquivo
BDPaciente *pL_create_from_file(const char *filename) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    BDPaciente *pL = pL_create();
    char linha[200];
    int i = 0;
    while (fgets(linha, 200, f) != NULL) {
        Paciente *p = insert_paciente(linha);
        pL_insert(pL, p);
        i++;
    }
    fclose(f);
    return pL;
}

// Funcao local para imprimir um header das informacoes do paciente
static void print_header() {
    printf("\nID\tCPF\t\tNome\t\tIdade\tData_Cadastro\n");
}

// Funcao para imprimir a lista inteira
void print_pacientes(BDPaciente *pL) {
    if (pL->first == NULL) {
        printf("Nenhum registro salvo!");
        return;
    }

    PacienteNode *pN = pL->first;
    
    print_header();
    while (pN != NULL) {
        print_paciente(pN->paciente);
        pN = pN->next;
    }
}

// Funcao para desalocar memoria
void pL_free(BDPaciente *pL) {
    if (pL == NULL) return;

    PacienteNode *pN = pL->first;
    while (pN != NULL) {
        PacienteNode *next = pN->next;
        free(pN->paciente);
        free(pN);
        pN = next;
    }
    free(pL);
}

// Funcao local para imprimir o menu de consulta
static void print_menu_consulta() {
    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
}

// Funcao generica para pesquisar pacientes
static void pesquisar_campo(const BDPaciente *pL, char *valor_buscar, int campo) {
    int encontrado = 0;

    PacienteNode *pN = pL->first;
    if (pN == NULL) {
        printf("Nenhum registro salvo!");
        return;
    }

    while (pN != NULL) {
        // Para cada paciente do vetor sera feita a verificacao
        // com base no campo passado
        // 1 = nome, 2 = cpf (mesmos valores do menu)
        Paciente *paciente = pN->paciente;
        int prefixo = 0;
        switch (campo) {
            case 1:
                prefixo = prefix_cmp(get_nome(paciente), valor_buscar);
                break;
            case 2:
                prefixo = prefix_cmp(get_cpf(paciente), valor_buscar);
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

        pN = pN->next;
    }

    if (!encontrado)
        printf("Nenhum paciente encontrado\n");
}

// Funcao para pesquisar especificamente pelo nome
static void pesquisar_nome(const BDPaciente *pL) {
    char nome[100];
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    pesquisar_campo(pL, nome, 1);
}

// Funcao para pesquisar especificamente pelo cpf
static void pesquisar_cpf(const BDPaciente *pL) {
    char cpf[14];
    printf("Digite o cpf do paciente: ");
    scanf("%s", cpf);
    pesquisar_campo(pL, cpf, 2);
}

// Funcao para o loop de busca
void consultar_pacientes(const BDPaciente *pL) {
    print_menu_consulta();
    char menu;
    scanf(" %c", &menu);
    while (menu != '3') {
        switch (menu) {
            case '1':
                pesquisar_nome(pL);
                break;
            case '2':
                pesquisar_cpf(pL);
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

// Funcao para imprimir paciente por ID
static void print_paciente_id(const BDPaciente *pL, int id) {
    int encontrado = 0;

    PacienteNode *pN = pL->first;
    if (pN == NULL) {
        printf("Nenhum registro salvo!");
        return;
    }

    while (!encontrado && pN != NULL) {
        if (id_cmp(pN->paciente, id)) {
            print_paciente(pN->paciente);
            encontrado = 1;
            return;
        }
        pN = pN->next;
    }

    if (!encontrado) {
        printf("Nenhum paciente encontrado com ID %d", id);
    }
}

static void print_menu_atualizar() {
    printf("\nExecute uma consulta para encontrar o registro que deseja atualizar.\n");
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Encontrei o registro e desejo atualizar\n");
    printf("4 - Retornar ao menu principal\n");
}

void atualizar_paciente_id(BDPaciente *pL, int id, char *cpf, char *nome, int idade, char *data_cadastro) {
    int encontrado = 0;

    PacienteNode *pN = pL->first;
    if (pN == NULL) {
        printf("Nenhum registro salvo!");
        return;
    }

    PacienteNode *prev = NULL;
    Paciente *paciente = pN->paciente;

    while (!encontrado && pN != NULL) {
        if (id_cmp(paciente, id)) {
            encontrado = 1;
            if (cpf != NULL || cpf[0] != '-') {
                set_cpf(paciente, cpf);
            }

            if (nome != NULL || nome[0] != '-') {
                set_nome(paciente, nome);
            }
            if (idade != -1) {
                set_idade(paciente, idade);
            }
            if (data_cadastro != NULL || data_cadastro[0] != '-') {
                set_data_cadastro(paciente, data_cadastro);
            }
            return;
        }
        prev = pN;
        pN = pN->next;
    }

    if (!encontrado) {
        printf("Nenhum paciente encontrado com ID %d", id);
    }
}

void atualizar_paciente(BDPaciente *pL) {
    int id = 0;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%d", &id);
    
    print_paciente_id(pL, id);
    printf("\nDigite o novo valor para os campos CPF (apenas dígitos), Nome, Idade e Data de Cadastro (para manter o valor atual de um campo, digite ’-’):\n");

    printf("CPF: ");
    char cpf[15];
    scanf("%s", cpf);
    printf("Nome: ");
    char nome[100];
    scanf(" %s", nome);
    printf("Idade: ");
    char str_idade[3];
    scanf(" %s", str_idade);
    int idade;
    if (str_idade[0] == '-') {
        idade = -1;
    } else {
        idade = atoi(str_idade);
    }
    printf("Data de Cadastro (DD/MM/AAAA): ");
    char data_cadastro[11];
    scanf(" %s", data_cadastro);

    atualizar_paciente_id(pL, id, cpf, nome, idade, data_cadastro);
}

void gerenciar_atualizar_paciente(BDPaciente *pL) {
    print_menu_atualizar();
    char menu;
    scanf(" %c", &menu);
    while (menu != '4') {
        switch (menu) {
            case '1':
                pesquisar_nome(pL);
                break;
            case '2':
                pesquisar_cpf(pL);
                break;
            case '3':
                atualizar_paciente(pL);
                return;
            case '4':
                return;
            default:
                printf("Opção inválida!\n");
        }
        print_menu_atualizar();
        scanf(" %c", &menu);
    }
}


// Funcao local para imprimir o menu de consulta
static void print_menu_remover() {
    printf("\nExecute uma consulta para encontrar o registro que deseja excluir.\n");
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Encontrei o registro e desejo excluir\n");
    printf("4 - Retornar ao menu principal\n");
}

void remover_paciente_id(BDPaciente *pL, int id) {
    int encontrado = 0;

    PacienteNode *pN = pL->first;
    if (pN == NULL) {
        printf("Nenhum registro salvo!");
        return;
    }

    PacienteNode *prev = NULL;

    while (!encontrado && pN != NULL) {
        if (id_cmp(pN->paciente, id)) {
            encontrado = 1;
            if (prev == NULL) {
                pL->first = pN->next;
            } else {
                prev->next = pN->next;
            }

            free(pN->paciente);
            free(pN);
            return;
        }
        prev = pN;
        pN = pN->next;
    }

    if (!encontrado) {
        printf("Nenhum paciente encontrado com ID %d", id);
    }
}

// Funcao para remover um paciente
void remover_paciente(BDPaciente *pL) {
    int id = 0;
    printf("\nDigite o ID do registro a ser removido: ");
    scanf("%d", &id);
    
    char confirmacao;
    printf("\nTem certeza que deseja excluir o registro abaixo? (S/N)\n");
    print_paciente_id(pL, id);
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S') {
        remover_paciente_id(pL, id);
    }
}

// Funcao para gerenciar a remocao um paciente
void gerenciar_remover_paciente(BDPaciente *pL) {
    print_menu_remover();
    char menu;
    scanf(" %c", &menu);
    while (menu != '4') {
        switch (menu) {
            case '1':
                pesquisar_nome(pL);
                break;
            case '2':
                pesquisar_cpf(pL);
                break;
            case '3':
                remover_paciente(pL);
                return;
            case '4':
                break;
            default:
                printf("Opção inválida!\n");
        }
        // Algum erro que está aparecendo várias vezes
        print_menu_remover();
        scanf(" %c", &menu);
    }
}

// Funcao para salvar a lista no 'banco'
void salvar_pacientes(const BDPaciente *pL, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    PacienteNode *pN = pL->first;
    while (pN != NULL) {
        Paciente *p = pN->paciente;
        write_paciente(f, p);
        pN = pN->next;
    }

    fclose(f);
    return;
}