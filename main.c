#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

void execute_module(char* mod_path, char* function) {
    void *handle = dlopen(mod_path, RTLD_LAZY);
    if (!handle) return;
    void (*func)() = dlsym(handle, function);
    if (func) func();
    dlclose(handle);
}

void parse_and_execute(char* line) {
    if (strncmp(line, "print", 5) == 0) {
        char *msg = strchr(line, '{') + 1;
        char *end = strchr(msg, '}');
        if(end) *end = '\0';
        printf("%s\n", msg);
    }
    else if (strncmp(line, "notify", 6) == 0) {
        char *msg = strchr(line, '{') + 1;
        char *end = strchr(msg, '}');
        if(end) {
            *end = '\0';
            char command[512];
            snprintf(command, sizeof(command), "termux-notification --title 'Kynto Engine' --content '%s'", msg);
            system(command);
        }
    }
    else if (strncmp(line, "hw{action: \"dashboard\"", 22) == 0) {
        execute_module("./modules/kynto_overkill.so", "print_overkill_dashboard");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;
    char line[256];
    printf("\033[38;5;214m--- KYNTO ENGINE: DYNAMIC CORE ---\033[0m\n");
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && line[0] != '\n' && strncmp(line, "module", 6) != 0) {
            parse_and_execute(line);
        }
    }
    fclose(file);
    return 0;
}
