#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ui_color(char* color) {
    if (strcmp(color, "red") == 0) printf("\033[1;31m");
    else if (strcmp(color, "green") == 0) printf("\033[1;32m");
    else if (strcmp(color, "blue") == 0) printf("\033[1;34m");
    else if (strcmp(color, "reset") == 0) printf("\033[0m");
    printf("[Kynto UI] Color set to %s\n", color);
}

void ui_dialog(char* msg) {
    printf("[Kynto UI] Displaying Dialog: %s\n", msg);
    char cmd[256];
    sprintf(cmd, "termux-dialog -t 'Kynto Engine' -i '%s' > /dev/null 2>&1", msg);
    system(cmd);
}

void ui_input(char* prompt) {
    char input[100];
    printf("[Kynto UI] %s: ", prompt);
    scanf("%s", input);
    printf("[Kynto UI] Captured: %s\n", input);
}
