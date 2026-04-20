#include <stdio.h>
#include <stdlib.h>

// Função que o seu Kernel vai chamar para capturar texto
void k_input(const char* prompt, char* output_var) {
    printf("%s", prompt);
    scanf("%s", output_var);
}

