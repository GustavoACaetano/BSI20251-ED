#include "paciente.h"
#include "pacienteList.h"
#include "prefix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct pacienteNode {
    Paciente *paciente;
    PacienteNode *next;
};

struct pacienteList {
    int count;
    PacienteNode *first;
    PacienteNode *last;
};

// Funcao para criar uma lista encadeada de pacientes
PacienteList *pL_create() {
    PacienteList *pL = (PacienteList *) malloc(sizeof(PacienteList));
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
    pN->next = NULL;
    return pN;
}

// Funcao para inserir um node na lista
void pL_insert(PacienteList *pL, Paciente *p) {
    PacienteNode *pN = pN_create(p);

    if (pL->last == NULL) {
        pL->first = pN;
    } else {
        pL->last->next = pN;
    }
    pL->count++;
    pL->last = pN;
}

// Funcao para criar uma lista de pacientes a partir de um arquivo
PacienteList *pL_create_from_file(const char *filename) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    PacienteList *pL = pL_create();
    char linha[200];
    int i = 0;
    while (fgets(linha, 200, f) != NULL) {
        Paciente *p = (Paciente *) malloc(sizeof(Paciente));
        if (p == NULL) {
            printf("Erro ao alocar memória\n");
            return NULL;
        }
        sscanf(linha, "%d,%[^,],%[^,],%d,%s", &p->id, p->cpf, p->nome, &p->idade, p->data_nascimento);
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

// Funcao local para imprimir um paciente especifico
static void print_paciente(const Paciente *p) {
    printf("%d\t%s\t%s\t%d\t%s\n", p->id, p->cpf, p->nome, p->idade, p->data_nascimento);
}

// Funcao para imprimir a lista inteira
void print_pacientes(PacienteList *pL) {
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
void pL_free(PacienteList *pL) {
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
static void pesquisar_campo(const PacienteList *pL, char *valor_buscar, int campo) {
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
                prefixo = prefix_cmp(paciente->nome, valor_buscar);
                break;
            case 2:
                prefixo = prefix_cmp(paciente->cpf, valor_buscar);
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
static void pesquisar_nome(const PacienteList *pL) {
    char nome[100];
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    pesquisar_campo(pL, nome, 1);
}

// Funcao para pesquisar especificamente pelo cpf
static void pesquisar_cpf(const PacienteList *pL) {
    char cpf[14];
    printf("Digite o cpf do paciente com pontos e hífen no formato correto (xxx.xxx.xxx-xx): ");
    scanf("%s", cpf);
    pesquisar_campo(pL, cpf, 2);
}

// Funcao para o loop de busca
void consultar_pacientes(const PacienteList *pL) {
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

// Funcao local para imprimir o menu de consulta
static void print_menu_remover() {
    printf("\nExecute uma consulta para encontrar o registro que deseja excluir.\n");
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Encontrei o registro e desejo excluir\n");
    printf("4 - Retornar ao menu principal\n");
}

// Funcao para imprimir paciente por ID
static void print_paciente_id(const PacienteList *pL, int id) {
    int encontrado = 0;

    PacienteNode *pN = pL->first;
    if (pN == NULL) {
        printf("Nenhum registro salvo!");
        return;
    }

    while (!encontrado && pN != NULL) {
        if (pN->paciente->id == id) {
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

void remover_paciente_id(PacienteList *pL, int id) {
    int encontrado = 0;

    PacienteNode *pN = pL->first;
    if (pN == NULL) {
        printf("Nenhum registro salvo!");
        return;
    }

    PacienteNode *prev = NULL;

    while (!encontrado && pN != NULL) {
        if (pN->paciente->id == id) {
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
void remover_paciente(PacienteList *pL) {
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
void gerenciar_remover_paciente(PacienteList *pL) {
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
        print_menu_remover();
        scanf(" %c", &menu);
    }
}

// Funcao para salvar a lista no 'banco'
void salvar_pacientes(const PacienteList *pL, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    PacienteNode *pN = pL->first;
    while (pN != NULL) {
        Paciente *p = pN->paciente;
        fprintf(f, "%d,%s,%s,%d,%s\n", p->id, p->cpf, p->nome, p->idade, p->data_nascimento);
        pN = pN->next;
    }

    fclose(f);
    return;
}