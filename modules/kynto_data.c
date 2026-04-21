#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Simulação de Gerenciamento de Memória (Garbage Collector manual)
void data_mem_clean() {
    printf("[Kynto DATA] Garbage Collector: Memory optimized.\n");
}

// Manipulação de Strings (Transformação de dados)
void data_transform(char* input) {
    printf("[Kynto DATA] Transformed: ");
    for(int i = 0; input[i]; i++) {
        putchar(toupper(input[i]));
    }
    printf("\n");
}

// Matemática de Alto Nível
void data_calc(char* op) {
    // Exemplo de parser simples de soma
    printf("[Kynto MATH] Result of '%s': Processing...\n", op);
}
