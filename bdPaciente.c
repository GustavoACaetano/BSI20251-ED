#include "paciente.h"
#include "bdPaciente.h"
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Definicao das estruturas
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


// -------------------- Funcoes basicas de lista --------------------------
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
        return NULL;
    }

    pN->paciente = p;
    pN->prev = NULL;
    pN->next = NULL;
    return pN;
}


// Funcao para inserir um node na lista
int pL_insert(BDPaciente *pL, Paciente *p) {
    PacienteNode *pN = pN_create(p);
    if (pN == NULL) return 0;

    if (pL->last == NULL) {
        pL->first = pN;
    } else {
        pN->prev = pL->last;
        pL->last->next = pN;
    }
    pL->count++;
    pL->last = pN;
    return 1;
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


// Funcao para salvar a lista no 'banco'
void salvar_pacientes(const BDPaciente *pL, const char *filename) {
    FILE *f = fopen(filename, "w"); // Essa abertura reescreve o arquivo do 0
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    // Passamos por todos os nós escrevendo no arquivo
    // Se o primeiro já for nulo, o arquivo ficará vazio
    PacienteNode *pN = pL->first;
    while (pN != NULL) {
        Paciente *p = pN->paciente;
        write_paciente(f, p);
        pN = pN->next;
    }

    fclose(f);
    return;
}


// --------------------- Funcoes de consulta ------------------------------------
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
    char cpf_entrada[14];
    printf("Digite o cpf do paciente: ");
    scanf("%s", cpf_entrada);
    char *cpf = cpf_mask(cpf_entrada);
    printf("\n\n%s\n\n", cpf);
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


// ------------ Funcoes de remocao ----------------------------------
// Funcao local para imprimir o menu de remocao
static void print_menu_remover() {
    printf("\nExecute uma consulta para encontrar o registro que deseja excluir.\n");
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Encontrei o registro e desejo excluir\n");
    printf("4 - Retornar ao menu principal\n");
}


int remover_paciente_id(BDPaciente *pL, int id) {
    int encontrado = 0;

    // Se o primeiro registro estiver vazio, a lista nao tem registros
    PacienteNode *pN = pL->first;
    if (pN == NULL) {
        printf("Nenhum registro salvo!");
        return 0;
    }

    // Passa por todos os nós, até encontrar o ID ou chegar ao final da lista
    PacienteNode *prev = NULL;
    while (!encontrado && pN != NULL) {
        // Remove o registro quando encontra o ID
        if (id_cmp(pN->paciente, id)) {
            encontrado = 1;
            if (prev == NULL) {
                pL->first = pN->next;
            } else {
                prev->next = pN->next;
            }

            // Libera a memoria
            free(pN->paciente);
            free(pN);
            return 1;
        }
        prev = pN;
        pN = pN->next;
    }

    if (!encontrado) {
        printf("Nenhum paciente encontrado com ID %d", id);
    }
    return 0;
}


// Funcao para remover um paciente
void remover_paciente(BDPaciente *pL) {
    int id = 0;
    printf("\nDigite o ID do registro a ser removido: ");
    scanf("%d", &id);
    
    char confirmacao;
    // Espera por uma resposta valida
    while (confirmacao != 'S' && confirmacao != 'N') {
        printf("\nTem certeza que deseja excluir o registro abaixo? (S/N)\n");
        print_paciente_id(pL, id);
        printf("\n Digite (S/N): ");
        scanf(" %c", &confirmacao);
        
        // Se houver a confirmacao, remove o paciente
        if (confirmacao == 'S') {
            int sucesso = remover_paciente_id(pL, id);
            if (sucesso) printf("\nO registro foi excluído com sucesso.");
        } else if (confirmacao == 'N') {
            printf("\nRemoção cancelada.");
        } else {
            printf("\nComando desconhecido.\n");
        }
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
                break;
        }
        // Algum erro que está aparecendo várias vezes
        print_menu_remover();
        scanf(" %c", &menu);
    }
}


// ---------------------- Funcoes de insercao ------------------------
int gerar_id(BDPaciente *pL) {
    // Geracao do ID a partir do ultimo paciente salvo
    return get_id(pL->last->paciente) + 1;
}
 

void gerenciar_insercao_paciente(BDPaciente *pL) {
    // Entrada dos dados do paciente
    printf("Para inserir um novo registro: \n");
    printf("Digite o CPF (apenas dígitos): ");
    char cpf_entrada[15];
    scanf(" %s", cpf_entrada);
    char *cpf = cpf_mask(cpf_entrada);

    printf("Digite o nome do paciente: ");
    char nome[100];
    scanf(" %99[^\n]", nome); // Leitura dessa forma para suportar espacos, ex: "Gustavo Caetano"

    printf("Digite a idade do paciente: ");
    int idade;
    scanf("%d", &idade);

    printf("Digite a data de cadastro (YYYY-MM-DD): ");
    char data_cadastro[11];
    scanf(" %s", data_cadastro);

    int id = gerar_id(pL);

    char confirmacao;
    Paciente *p = create_paciente(id, cpf, nome, idade, data_cadastro);
    if (p == NULL) return;

    // Espera por uma resposta valida
    while (confirmacao != 'S' && confirmacao != 'N') {
        // Entrada do dado de resposta
        printf("Confirmar a inserção do registro abaixo? (S/N)\n");
        print_header();
        print_paciente(p);
        printf("\n Digite (S/N): ");
        scanf(" %c", &confirmacao);

        // Se houver a confirmacao, adiciona o paciente na lista
        if (confirmacao == 'S') {
            int sucesso = pL_insert(pL,p);
            if (sucesso) printf("\nO registro foi inserido com sucesso.");
        } else if (confirmacao == 'N') { 
            // Se houver o cancelamento, libera a memoria
            printf("\nInserção cancelada.");
            free(p);
        } else {
            printf("\nComando desconhecido.\n");
        }
    }
}


// ------------------------ Funcoes de atualizacao ------------------------
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

