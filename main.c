#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <ctype.h>

void *loaded_handles[100];
int mod_count = 0;

// Função para carregar os módulos do script
void load_module(char* line) {
    char *start = strchr(line, '{');
    char *end = strrchr(line, '}');
    if (start && end) {
        start++; *end = '\0';
        void *h = dlopen(start, RTLD_LAZY);
        if (h) loaded_handles[mod_count++] = h;
    }
}

// Função de execução direta que você pediu
void execute_module_direct(char* mod_path, char* function) {
    void *handle = dlopen(mod_path, RTLD_LAZY);
    if (!handle) return;
    void (*func)() = dlsym(handle, function);
    if (func) func();
    dlclose(handle);
}

void parse_and_execute(char* line, int line_num) {
    while(isspace((unsigned char)*line)) line++;
    if (*line == '\0' || *line == '#') return;

    // 1. SUPORTE NATIVO: PRINT
    if (strncmp(line, "print", 5) == 0) {
        char *msg = strchr(line, '{') + 1;
        char *end = strrchr(line, '}');
        if(end) { *end = '\0'; printf("%s\n", msg); }
        return;
    }

    // 2. SUPORTE NATIVO: NOTIFY
    if (strncmp(line, "notify", 6) == 0) {
        char *msg = strchr(line, '{') + 1;
        char *end = strrchr(line, '}');
        if(end) {
            *end = '\0';
            char command[1024];
            snprintf(command, sizeof(command), "termux-notification --title 'Kynto Engine' --content '%s'", msg);
            system(command);
        }
        return;
    }

    // 3. HW DASHBOARD (Lógica específica que você pediu)
    if (strstr(line, "hw{action: \"dashboard\"") != NULL) {
        execute_module_direct("./modules/kynto_overkill.so", "print_overkill_dashboard");
        return;
    }

    // 4. EXTRAÇÃO DE COMANDO PARA BUSCA DINÂMICA
    char cmd[128] = {0};
    char arg[512] = {0};
    char *brace = strchr(line, '{');
    if (brace) {
        strncpy(cmd, line, brace - line);
        char *end_cmd = cmd + strlen(cmd) - 1;
        while(end_cmd >= cmd && isspace((unsigned char)*end_cmd)) { *end_cmd = '\0'; end_cmd--; }
        char *end_brace = strrchr(brace, '}');
        if (end_brace) strncpy(arg, brace + 1, end_brace - brace - 1);
    } else {
        strcpy(cmd, line);
    }

    // 5. TRADUÇÃO E BUSCA NOS MÓDULOS
    int found = 0;
    for (int i = 0; i < mod_count; i++) {
        // Tenta o nome exato
        void (*f)(char*) = dlsym(loaded_handles[i], cmd);
        
        // Mapeamento automático para evitar "Unknown command"
        if (!f && strcmp(cmd, "ui") == 0) f = dlsym(loaded_handles[i], "ui_window");
        if (!f && strcmp(cmd, "hw") == 0) f = dlsym(loaded_handles[i], "hw_battery");
        if (!f && strcmp(cmd, "ultra") == 0) {
            f = dlsym(loaded_handles[i], "print_overkill_dashboard");
            if (!f) f = dlsym(loaded_handles[i], "ultra_sysinfo");
        }

        if (f) {
            f(arg);
            found = 1;
            break;
        }
    }

    if (!found && strcmp(cmd, "loop") != 0) {
        printf("\033[1;31mError on line %d: Unknown command '%s'\033[0m\n", line_num, cmd);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;
    char line[1024];
    int line_num = 0;
    printf("\033[38;5;214m--- KYNTO ENGINE: DYNAMIC CORE ---\033[0m\n");
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        line[strcspn(line, "\n\r")] = 0;
        if (strncmp(line, "module", 6) == 0) {
            load_module(line);
        } else {
            parse_and_execute(line, line_num);
        }
    }
    fclose(file);
    return 0;
}
