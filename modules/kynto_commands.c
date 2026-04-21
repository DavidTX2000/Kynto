#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* --- Kynto Engine: Native Core Modules --- */

void hardware_get(char* param) {
    if (strcmp(param, "battery") == 0) {
        FILE *f = fopen("/sys/class/power_supply/battery/capacity", "r");
        if (f) {
            int cap;
            fscanf(f, "%d", &cap);
            fclose(f);
            printf("[Kynto HW] Battery: %d%%\n", cap);
        }
    } else if (strcmp(param, "temp") == 0) {
        FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
        if (f) {
            int temp;
            fscanf(f, "%d", &temp);
            fclose(f);
            printf("[Kynto HW] Temp: %.1f°C\n", temp / 1000.0);
        }
    }
}

void network_ping(char* host) {
    printf("[Kynto NET] Latency test to: %s\n", host);
    char cmd[100];
    sprintf(cmd, "ping -c 1 -W 1 %s > /dev/null && echo '[Kynto NET] Status: ONLINE' || echo '[Kynto NET] Status: OFFLINE'", host);
    system(cmd);
}

void process_list() {
    printf("[Kynto OS] Top priority processes:\n");
    system("ps -e | head -n 5");
}

void security_user() {
    char *user = getlogin();
    printf("[Kynto SEC] Session Owner: %s\n", user ? user : "termux_auth");
}

/* Função principal de execução de comandos (Exemplo simplificado) */
void execute_kynto(char* cmd, char* arg) {
    if (strcmp(cmd, "hardware") == 0) hardware_get(arg);
    if (strcmp(cmd, "network") == 0) network_ping(arg);
    if (strcmp(cmd, "process") == 0) process_list();
    if (strcmp(cmd, "user") == 0) security_user();
}
