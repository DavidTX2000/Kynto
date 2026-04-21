#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ui_notify(char* msg) {
    printf("[Kynto UI] Attempting to send high-priority notification...\n");
    
    // Verifica se o binário da API existe no sistema
    int check = system("command -v termux-notification > /dev/null 2>&1");
    
    if (check == 0) {
        char cmd[512];
        // Adicionando título, cor e prioridade máxima (--priority high)
        sprintf(cmd, "termux-notification -t 'KYNTO ENGINE' -c '%s' --led-color green --priority high --sound", msg);
        system(cmd);
        printf("[Kynto UI] Notification sent successfully.\n");
    } else {
        printf("\033[1;31m[Kynto ERROR] termux-api not found! Install it with: pkg install termux-api\033[0m\n");
    }
}

void ui_color(char* color) {
    if (strcmp(color, "red") == 0) printf("\033[1;31m");
    else if (strcmp(color, "green") == 0) printf("\033[1;32m");
    else if (strcmp(color, "reset") == 0) printf("\033[0m");
}
