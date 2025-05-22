
#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente Paciente;
typedef struct pacienteList PacientesList;

PacientesList* pl_create();

PacientesList* pl_create_from_file(const char *filename);

static void reallocate(PacientesList *pl);

void pl_insert(PacientesList *pl, Paciente p);

int pl_size(PacientesList *pl);

int pl_capacity(PacientesList *pl);

Paciente pl_get(PacientesList *pl, int i);

void pl_free(PacientesList *pl);

void print_pacientes(PacientesList *pl);

int prefix_cmp(const char *target, const char *src);

void pesquisar_nome(PacientesList *pl);

void consultar_pacientes(PacientesList *pl);

#endif
