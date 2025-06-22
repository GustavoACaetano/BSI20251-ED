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
#endif
