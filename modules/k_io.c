#include <stdio.h>
#include <stdlib.h>

// O nome da função deve ser o que o Kernel procura
void input(const char* args) {
    // Lógica simplificada para o Kernel
    printf("Enter value: ");
    char buffer[256];
    scanf("%s", buffer);
}
