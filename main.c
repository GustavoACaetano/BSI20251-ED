#include <stdio.h>
#include <stdlib.h>
#include "paciente.h"

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

int main() {
    char *arquivo = "bd_paciente.csv";
    PacientesList *pacientes = pl_create_from_file(arquivo);
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
                print_pacientes(pacientes);
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