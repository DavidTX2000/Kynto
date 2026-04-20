#include <stdio.h>
#include <stdlib.h>

void notf_send(char *args) {
    char title[128], msg[512], cmd[700];
    if (sscanf(args, "%[^,],%[^\n]", title, msg) == 2) {
        sprintf(cmd, "termux-notification -t \"%s\" -c \"%s\"", title, msg);
        system(cmd);
    }
}

void tts_speak(char *args) {
    char cmd[600];
    sprintf(cmd, "termux-tts-speak \"%s\"", args);
    system(cmd);
}

void cam_photo(char *args) {
    char cmd[256];
    sprintf(cmd, "termux-camera-photo %s", args);
    system(cmd);
}
