#include <stdio.h>
#include <stdlib.h>

struct Paciente
{
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_nascimento[10];
};

void ler_arquivo(char *nome_arquivo, struct Paciente *pacientes) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    char linha[200];
    int i = 0;
    while (fgets(linha, 200, arquivo) != NULL) {
        sscanf(linha, "%d,%[^,],%[^,],%d,%s", &pacientes[i].id, pacientes[i].cpf, pacientes[i].nome, &pacientes[i].idade, pacientes[i].data_nascimento);
        i++;
    }
    fclose(arquivo);

}

int contar_pacientes(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return -1;
    }
    int contador = 0;
    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contador++;
    }
    fclose(arquivo); 
    return contador;
}

void print_pacientes(struct Paciente *pacientes, int *tamanho) {
    printf("ID\tCPF\t\tNome\t\tIdade\tData de Nascimento\n");
    for (int i = 0; i < *tamanho; i++) {
        printf("%d\t%s\t%s\t%d\t%s\n", pacientes[i].id, pacientes[i].cpf, pacientes[i].nome, pacientes[i].idade, pacientes[i].data_nascimento);
    }
    printf("================================================\n");
}

void print_menu() {
    printf("Menu:\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir pacientes\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair\n");
    printf("Escolha uma opção: ");
}

void procurar_por_nome(struct Paciente *pacientes) {
    // int tamanho = sizeof(pacientes) / sizeof(pacientes[0]);
    // for (int i = 0; i < tamanho; i++) {
    //     if (strcmp(pacientes[i].nome, nome) == 0) {
    //         printf("Paciente encontrado: %s\n", pacientes[i].nome);
    //         return;
    //     }
    // }
    // printf("Paciente não encontrado\n");
}

void consultar_pacientes(struct Paciente *pacientes) {
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");   
    printf("3 - Retornar ao menu principal\n");
    int menu;
    scanf("%d", &menu);
    while (menu != 3) {
        switch (menu) {
            case 1:
                printf("Função não implementada\n");
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

int main() {
    char *arquivo = "bd_paciente.csv";
    int tamanho = contar_pacientes(arquivo);
    struct Paciente *pacientes = (struct Paciente*) malloc(sizeof(struct Paciente) * tamanho);
    if (pacientes == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }
    ler_arquivo(arquivo, pacientes);
    print_menu();
    char menu;
    scanf(" %c", &menu);
    while (menu != 'Q') {
        switch (menu) {
            case '1':
                printf("\n");
                break;
            case '2':
                printf("Função não implementada\n");
                break;
            case '3':
                printf("Funlão não implementada\n");
                break;
            case '4':
                printf("Função não implementada\n");
                break;
            case '5':
                print_pacientes(pacientes, &tamanho);
                break;
            default:
                printf("Opção inválida\n");
        }
        print_menu();
        scanf(" %c", &menu);
    }
    free(pacientes);
    return 0;
}