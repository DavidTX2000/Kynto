#include <stdio.h>
#include <stdlib.h>

void k_input(const char* prompt, char* output_var) {
    printf("%s", prompt);
    scanf("%s", output_var);
}

