#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// Funcao para identificar se a string eh um prefixo
int prefix_cmp(const char *target, const char *src) {
    // Validacao das strings
    if (target == NULL || src == NULL) {
        return 0;
    }
    if (strlen(target) < strlen(src)) {
        return 0;
    }

    // Verificacao do prefixo
    int i = 0;
    while (src[i] != '\0') {
        if (target[i] != src[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}


// Funcao para mascara de cpf
char *cpf_mask(const char *cpf) {
    // Se a quantidade for maior que 11, retorna invalido
    if (strlen(cpf) > 11) {
        return NULL;
    } else {
        // Com menos de 11 caracteres, a situacao deve ser a consulta por cpf
        // entao, o tratamento precisa servir para esse caso tambem
        char *masked = malloc(15);
        if (!masked) {
            return NULL;
        }

        //          012 345 678 9 10
        // Entrada: 146 456 123 4 4

        //        012  3 456 7  89 10 11 12 13
        // Saida: 146  . 456 .  12  3  -  4  4
        int i = 0;
        int y = 0; // marcar o final pra colocar o caracter de fim
        for (i = 0; i < strlen(cpf); i++) {
            if (i < 3) {
                masked[i] = cpf[i];
                y = i;
            }
            if (i == 3) {
                masked[i] = '.';
                masked[i+1] = cpf[i];
                y = i+1;
            }
            if (i > 3 && i < 6) {
                masked[i+1] = cpf[i];
                y = i+1;
            }
            if (i == 6) {
                masked[i+1] = '.';
                masked[i+2] = cpf[i];
                y = i+2;
            }
            if (i > 6 && i < 9) {
                masked[i+2] = cpf[i];
                y = i+2;
            }
            if (i == 9) {
                masked[i+2] = '-';
                masked[i+3] = cpf[i];
                y = i+3;
            }
            if (i > 9) {
                masked[i+3] = cpf[i];
                y = i+3;
            }
        }
        masked[y+1] = '\0';
        return masked;
    }
}