#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

// Função mestra para carregar e executar qualquer módulo .so
void execute_module(char* mod_path, char* function, char* arg) {
    void *handle = dlopen(mod_path, RTLD_LAZY);
    if (!handle) {
        return;
    }

    void (*func)(char*) = dlsym(handle, function);
    if (func) {
        func(arg);
    }
    dlclose(handle);
}

// O "Cérebro" do Kynto: Interpreta as linhas do script .ky
void parse_and_execute(char* line) {
    // Comando PRINT
    if (strncmp(line, "print", 5) == 0) {
        char *msg = strchr(line, '{') + 1;
        char *end = strchr(msg, '}');
        if(end) *end = '\0';
        printf("%s\n", msg);
    } 
    // Comandos de UI (Cores e Notificações)
    else if (strncmp(line, "ui{action: \"notify:", 19) == 0) {
        char *msg = strchr(line, ':') + 1;
        char *end = strchr(msg, '\"');
        if(end) *end = '\0';
        execute_module("./modules/kynto_ui.so", "ui_notify", msg);
    }
    else if (strncmp(line, "ui{color:", 9) == 0) {
        char *color = strchr(line, '\"') + 1;
        char *end = strrchr(line, '\"');
        if(end) *end = '\0';
        execute_module("./modules/kynto_ui.so", "ui_color", color);
    }
    // Comandos de HARDWARE
    else if (strncmp(line, "hw{action: \"dashboard\"", 22) == 0) {
        execute_module("./modules/kynto_hw_pro.so", "hw_dashboard", "");
    }
    // Comandos ULTRA (Stress e SysInfo)
    else if (strncmp(line, "ultra{action: \"sysinfo\"", 23) == 0) {
        execute_module("./modules/kynto_ultra.so", "ultra_sysinfo", "");
    }
    else if (strncmp(line, "ultra{action: \"stress\"", 22) == 0) {
        execute_module("./modules/kynto_ultra.so", "ultra_stress", "");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\033[1;31mUsage: ./kynto <script.ky>\033[0m\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Could not open script %s\n", argv[1]);
        return 1;
    }

    char lines[100][256];
    int total_lines = 0;
    int loop_count = 1;

    printf("\033[1;36m--- KYNTO ENGINE: DYNAMIC CORE (BASH-KILLER) ---\033[0m\n");

    // Lendo o script para a memória
    while (total_lines < 100 && fgets(lines[total_lines], 256, file)) {
        // Detecta comando de loop no script
        if (strncmp(lines[total_lines], "loop", 4) == 0) {
            char *start = strchr(lines[total_lines], '{') + 1;
            char *end = strchr(start, '}');
            if(end) *end = '\0';
            loop_count = atoi(start);
            continue; 
        }
        // Ignora comentários e linhas vazias
        if (lines[total_lines][0] != '#' && lines[total_lines][0] != '\n' && strncmp(lines[total_lines], "module", 6) != 0) {
            total_lines++;
        }
    }
    fclose(file);

    // Execução controlada pelo programador
    for(int i = 1; i <= loop_count; i++) {
        if (loop_count > 1) printf("\n\033[1;33m[Loop Iteration %d/%d]\033[0m\n", i, loop_count);
        for(int j = 0; j < total_lines; j++) {
            parse_and_execute(lines[j]);
        }
    }

    printf("\n\033[1;32m--- GLOBAL EXECUTION SUCCESS ---\033[0m\n");
    return 0;
}
