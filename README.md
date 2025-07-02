# Trabalho 2 de Estrutura de Dados
## Sistema de Gerenciamento de Dados de Pacientes – Parte II
### Integrantes: <br>
[Gustavo Alves Caetano](https://github.com/GustavoACaetano)<br>
[João Pedro Zamborlini Barcellos](https://github.com/joaopbarcellos) <br>

### Execução do projeto
Pré-requisito: <br>
Ter instalado o gcc-11

#### 1 - Clone o repositório:
```bash
git clone https://github.com/GustavoACaetano/trabalho1-ed.git
```

#### OU <br>
#### Baixe o arquivo zip: 
![image](https://github.com/user-attachments/assets/6fbea150-6eab-4a52-9e62-9bcbe1c790df)
<br><br>
#### 2 - Execute o comando
```bash
make
```
para executar o Makefile e já iniciar o programa.

### TAD's
A estrutura paciente está definida desta forma:
```c
struct paciente
{
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[10];
};
```

Também foi criada uma estrutura de lista duplamente encadeada. <br>
A estrutura BDPaciente está definida desta forma:
```c
struct bdPaciente {
    int count;
    PacienteNode *first;
    PacienteNode *last;
};
```

A estrutura PacienteNode está definida desta forma:
```c
struct pacienteNode {
    Paciente *paciente;
    PacienteNode *next;
    PacienteNode *prev;
};
```


### Decisões de implementação
#### 1 - Lista Duplamente Encadeada <br>
A escolha feita foi a de utilizar uma lista duplamente encadeada. <br> 
Utilizando uma lista duplamente encadeada, a navegação para remoção de um elemento <br> 
foi mais fluida (no início do desenvolvimento, fizemos uma lista encadeada simples) <br> 
e permitiu um gerenciamento e controle maior para percorrer a lista.

#### 2 - Salvar no Banco de Dados Após Cada Ação <br>
A escolha do momento de salvar os dados no banco de dados foi no fim de cada ação <br>
bem sucedida. Inicialmente, o salvamento ocorria apenas ao fim do programa principal <br>
(quando se respondia 'Q' para sair), porém, para garantir que as ações bem sucedidas do <br>
usuário sejam salvas, mesmo que ocorra um erro durante a execução do programa, mudamos <br>
o momento de salvar para o fim de toda ação bem sucedida que altera a lista de pacientes.
