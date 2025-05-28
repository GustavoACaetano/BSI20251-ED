# Trabalho 1 de Estrutura de Dados
## Sistema de Gerenciamento de Dados de Pacientes – Parte I
### Integrantes: <br>
[Gustavo Alves Caetano](https://github.com/GustavoACaetano)<br>
[João Pedro Zamborlini Barcellos](https://github.com/joaopbarcellos) <br>

### Execução do projeto
Pré-requisito: <br>
Ter instalado o gcc-11

1 - Clone o repositório:
```bash
git clone https://github.com/GustavoACaetano/trabalho1-ed.git
```
<br>

OU <br><br>
Baixe o arquivo zip: 
![image](https://github.com/user-attachments/assets/6fbea150-6eab-4a52-9e62-9bcbe1c790df)
<br><br>
2 - Execute o comando
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
    char data_nascimento[10];
};
```

A estrutura do vetor dinâmico de pacientes está definida desta forma:
```c
struct pacientesDynVec
{
    Paciente *pacientes;
    int tamanho;
    int capacidade;
};
```

### Decisões de implementação
#### 1 - Vetor dinâmico <br>
A escolha para utilizar vetor dinâmico teve o objetivo de facilitar a leitura dos dados do arquivo. <br> 
Utilizando vetor dinâmico, a leitura do arquivo pode ser feita de forma direta, <br> 
sem precisar da leitura inicial para descobrir a quantidade de linhas.

