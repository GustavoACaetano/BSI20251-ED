#ifndef BDPACIENTE_H
#define BDPACIENTE_H
#include "paciente.h"

typedef struct pacienteNode PacienteNode;

typedef struct bdPaciente BDPaciente;

BDPaciente *pL_create();

PacienteNode *pN_create(Paciente *p);

int pL_insert(BDPaciente *pL, Paciente *p);

BDPaciente *pL_create_from_file(const char *filename);

void print_pacientes(BDPaciente *pL);

void consultar_pacientes(const BDPaciente *pL);

void pL_free(BDPaciente *pL);

void salvar_pacientes(const BDPaciente *pL, const char *filename);

void gerenciar_atualizar_paciente(BDPaciente *pL);

void gerenciar_remover_paciente(BDPaciente *pL);

void gerenciar_insercao_paciente(BDPaciente *pL);

int remover_paciente_id(BDPaciente *pL, int id);

#endif
