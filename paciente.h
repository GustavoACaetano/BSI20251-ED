
#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente Paciente;
typedef struct pacientesDynVec PacientesDynVec;

PacientesDynVec* pdv_create();

PacientesDynVec* pdv_create_from_file(const char *filename);

void pdv_insert(PacientesDynVec *pdv, Paciente p);

int pdv_size(const PacientesDynVec *pdv);

int pdv_capacity(const PacientesDynVec *pdv);

Paciente pdv_get(const PacientesDynVec *pdv, int i);

void pdv_free(PacientesDynVec *pdv);

void print_pacientes(const PacientesDynVec *pdv);

int prefix_cmp(const char *target, const char *src);

void pesquisar_nome(const PacientesDynVec *pdv);

void pesquisar_cpf(const PacientesDynVec *pdv);

void consultar_pacientes(const PacientesDynVec *pdv);

#endif
