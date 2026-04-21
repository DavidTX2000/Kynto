#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h> // Biblioteca para carregar os .so

void execute_module(char* mod_path, char* function, char* arg) {
    void *handle = dlopen(mod_path, RTLD_LAZY);
    if (!handle) {
        printf("[Kynto ERROR] Module not found: %s\n", mod_path);
        return;
    }

    // Busca a função dentro do arquivo .so
    void (*func)(char*) = dlsym(handle, function);
    if (func) {
        func(arg); // Executa a função real do módulo!
    } else {
        printf("[Kynto ERROR] Function %s not found in %s\n", function, mod_path);
    }
    dlclose(handle);
}

void parse_and_execute(char* line) {
    if (strncmp(line, "print", 5) == 0) {
        char *msg = strchr(line, '{') + 1;
        char *end = strchr(msg, '}');
        if(end) *end = '\0';
        printf("%s\n", msg);
    } 
    else if (strncmp(line, "ui{action: \"notify:", 19) == 0) {
        char *msg = strchr(line, ':') + 1;
        char *end = strchr(msg, '\"');
        if(end) *end = '\0';
        execute_module("./modules/kynto_ui.so", "ui_notify", msg);
    }
    else if (strncmp(line, "ui{color:", 9) == 0) {
        char *color = strchr(line, ':') + 1;
        char *end = strchr(color, '\"');
        if(end) *end = '\0';
        execute_module("./modules/kynto_ui.so", "ui_color", color);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *file = fopen(argv[1], "r");
    char line[256];

    printf("\033[1;36m--- KYNTO ENGINE: DYNAMIC CORE ---\033[0m\n");

    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && line[0] != '\n' && strncmp(line, "module", 6) != 0 && strncmp(line, "loop", 4) != 0) {
            parse_and_execute(line);
        }
    }
    fclose(file);
    printf("\n\033[1;32m--- EXECUTION SUCCESS ---\033[0m\n");
    return 0;
}
