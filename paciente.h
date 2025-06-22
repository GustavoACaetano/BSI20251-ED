#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_nascimento[10];
} Paciente;

#endif
