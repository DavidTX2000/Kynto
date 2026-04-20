#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comando de Acessibilidade e Permissões
void get_acess(char *args) {
    if (strstr(args, "accessibility")) {
        system("am start -a android.settings.ACCESSIBILITY_SETTINGS > /dev/null 2>&1");
        printf("\033[1;32m[PERM]: Accessibility settings opened.\033[0m\n");
    }
}

// Comando de Notificação
void notf_msg(char *args) {
    char message[512] = {0};
    char *start = strstr(args, "set:\"");
    if (start) {
        start += 5;
        char *end = strchr(start, '\"');
        if (end) {
            strncpy(message, start, end - start);
            char cmd[1024];
            sprintf(cmd, "termux-notification --content \"%s\" --title \"Kynto OS\"", message);
            system(cmd);
            printf("\033[1;34m[API]: Notification sent.\033[0m\n");
        }
    }
}

// NOVO: Comando de Vibração (hw.vibrate)
void hw_vibrate(char *args) {
    int ms = 500; // Padrão 500ms
    sscanf(args, "{%d}", &ms);
    char cmd[128];
    sprintf(cmd, "termux-vibrate -d %d", ms);
    system(cmd);
    printf("\033[1;35m[HW]: Vibrating for %dms...\033[0m\n", ms);
}

// NOVO: Comando de Voz (tts.speak)
void tts_speak(char *args) {
    char text[512] = {0};
    if (sscanf(args, "{%[^}]}", text) == 1) {
        char cmd[1024];
        sprintf(cmd, "termux-tts-speak \"%s\"", text);
        system(cmd);
        printf("\033[1;33m[TTS]: Speaking: %s\033[0m\n", text);
    }
}
