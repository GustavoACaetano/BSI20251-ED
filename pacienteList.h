#ifndef PACIENTELIST_H
#define PACIENTELIST_H
#include "paciente.h"

typedef struct pacienteNode PacienteNode;

typedef struct pacienteList PacienteList;

PacienteList *pL_create();

PacienteNode *pN_create(Paciente *p);

void pL_insert(PacienteList *pL, Paciente *p);

PacienteList *pL_create_from_file(const char *filename);

void print_pacientes(PacienteList *pL);

void consultar_pacientes(const PacienteList *pL);

void pL_free(PacienteList *pL);

void salvar_pacientes(const PacienteList *pL, const char *filename);

void gerenciar_remover_paciente(PacienteList *pL);

void remover_paciente_id(PacienteList *pL, int id);

#endif
