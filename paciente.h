#ifndef PACIENTE_H
#define PACIENTE_H
#include <stdio.h>

typedef struct paciente Paciente;

void print_paciente(const Paciente *p);

Paciente *insert_paciente(const char *linha);

void write_paciente(FILE *f, const Paciente *p);

int id_cmp(const Paciente *p, const int id);

char *get_nome(Paciente *p);

char *get_cpf(Paciente *p);

void set_nome(Paciente *p, const char *nome);

void set_cpf(Paciente *p, const char *cpf);

void set_idade(Paciente *p, int idade);

void set_data_cadastro(Paciente *p, const char *data_cadastro);
#endif
