#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simula toque no ecrã (Coordenadas X, Y)
void input_tap(char *args) {
    int x, y;
    if (sscanf(args, "{x:%d#y:%d}", &x, &y) == 2) {
        char cmd[128];
        sprintf(cmd, "input tap %d %d", x, y);
        system(cmd);
        printf("\033[1;32m[INPUT]: Tapped at [%d, %d]\033[0m\n", x, y);
    }
}

// Digita texto automaticamente
void input_text(char *args) {
    char str[256];
    if (sscanf(args, "{str:\"%[^\"]\"}", str) == 1) {
        char cmd[512];
        sprintf(cmd, "input text \"%s\"", str);
        system(cmd);
        printf("\033[1;32m[INPUT]: Injected text sequence.\033[0m\n");
    }
}
