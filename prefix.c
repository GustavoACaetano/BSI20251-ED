#include <string.h>

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