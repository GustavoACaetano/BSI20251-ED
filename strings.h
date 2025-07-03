#ifndef PREFIX_H
#define PREFIX_H

// Funcao para identificar se a string eh um prefixo
int prefix_cmp(const char *target, const char *src);

// Funcao que retorna o cpf com mascara
char *cpf_mask(const char *cpf);
#endif
