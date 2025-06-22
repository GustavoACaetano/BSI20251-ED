#include "paciente.h"
#include "prefix.h"
#include <stdio.h>
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

// // Funcao local para imprimir um paciente especifico
void print_paciente(const Paciente *p) {
    printf("%d\t%s\t%s\t%d\t%s\n", p->id, p->cpf, p->nome, p->idade, p->data_nascimento);
}

Paciente *insert_paciente(const char *linha) {
    Paciente *p = (Paciente *) malloc(sizeof(Paciente));
    if (p == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }
    sscanf(linha, "%d,%[^,],%[^,],%d,%s", &p->id, p->cpf, p->nome, &p->idade, p->data_nascimento);
    return p;
}

void write_paciente(FILE *f, const Paciente *p) {
    fprintf(f, "%d,%s,%s,%d,%s\n", p->id, p->cpf, p->nome, p->idade, p->data_nascimento);
}

int id_cmp(const Paciente *p, const int id) {
    return p->id == id;
}

char *get_nome(Paciente *p) {
    return p->nome;
}

char *get_cpf(Paciente *p) {
    return p->cpf;
}

// // Funcao generica para pesquisar pacientes
// void pesquisar_campo(const PacientesDynVec *pdv, char *valor_buscar, int campo) {
//     int encontrado = 0;

//     // Repeticao por todo o tamanho do vetor dinamico
//     for (int i = 0; i < pdv_size(pdv); i++) {
//         // Para cada paciente do vetor sera feita a verificacao
//         // com base no campo passado
//         // 1 = nome, 2 = cpf (mesmos valores do menu)
//         Paciente paciente = pdv_get(pdv, i);
//         int prefixo = 0;
//         switch (campo) {
//             case 1:
//                 prefixo = prefix_cmp(paciente.nome, valor_buscar);
//                 break;
//             case 2:
//                 prefixo = prefix_cmp(paciente.cpf, valor_buscar);
//                 break;
//             default:
//                 printf("Campo de busca inválido!");
//                 return;
//         }

//         // Sendo prefixo, deve-se imprimir as informacoes do paciente
//         if (prefixo) {
//             // O header so sera impresso no primeiro registro desse momento de busca
//             if (!encontrado) {
//                 encontrado = 1;
//                 print_header();
//             }
//             print_paciente(paciente);
//         }
//     }
//     if (!encontrado)
//         printf("Nenhum paciente encontrado\n");
// }

// // Funcao para pesquisar especificamente pelo nome
// void pesquisar_nome(const PacientesDynVec *pdv) {
//     char nome[100];
//     printf("Digite o nome do paciente: ");
//     scanf("%s", nome);
//     pesquisar_campo(pdv, nome, 1);
// }

// // Funcao para pesquisar especificamente pelo cpf
// void pesquisar_cpf(const PacientesDynVec *pdv) {
//     char cpf[14];
//     printf("Digite o cpf do paciente com pontos e hífen no formato correto (xxx.xxx.xxx-xx): ");
//     scanf("%s", cpf);
//     pesquisar_campo(pdv, cpf, 2);
// }

// // Funcao local para imprimir o menu de consulta
// static void print_menu_consulta() {
//     printf("\nEscolha o modo de consulta:\n");
//     printf("1 - Por nome\n");
//     printf("2 - Por CPF\n");
//     printf("3 - Retornar ao menu principal\n");
// }

// Funcao para o loop de busca
// void consultar_pacientes(const PacientesDynVec *pdv) {
//     print_menu_consulta();
//     char menu;
//     scanf(" %c", &menu);
//     while (menu != '3') {
//         switch (menu) {
//             case '1':
//                 pesquisar_nome(pdv);
//                 break;
//             case '2':
//                 pesquisar_cpf(pdv);
//                 break;
//             case '3':
//                 break;
//             default:
//                 printf("Opção inválida!\n");
//         }
//         print_menu_consulta();
//         scanf(" %c", &menu);
//     }
// }