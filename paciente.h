
#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente Paciente;
typedef struct pacientesDynVec PacientesDynVec;

// Cria um vetor dinamico de pacientes
PacientesDynVec* pdv_create();

// Cria um vetor dinamico de pacientes a partir de um arquivo
PacientesDynVec* pdv_create_from_file(const char *filename);

// Insere um paciente no vetor
void pdv_insert(PacientesDynVec *pdv, Paciente p);

// Retorna o tamanho do vetor
int pdv_size(const PacientesDynVec *pdv);

// Retorna a capacidade do vetor
int pdv_capacity(const PacientesDynVec *pdv);

// Retorna um paciente com base no indice
Paciente pdv_get(const PacientesDynVec *pdv, int i);

// Libera a memoria do vetor
void pdv_free(PacientesDynVec *pdv);

// Imprime os pacientes do vetor
void print_pacientes(const PacientesDynVec *pdv);

// Pesquisa pacientes pelo nome
void pesquisar_nome(const PacientesDynVec *pdv);

// Pesquisa pacientes pelo cpf
void pesquisar_cpf(const PacientesDynVec *pdv);

// Chama a busca de consulta de pacientes
void consultar_pacientes(const PacientesDynVec *pdv);

#endif
