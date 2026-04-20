#include "kynto.h"
void process_instruction(char *line, int line_num) {
    char command[64], args[1024];
    if (sscanf(line, "%63s %1023[^\n]", command, args) < 1) return;
    if (strncmp(line, "//", 2) == 0) return;
    char func_name[64];
    strcpy(func_name, command);
    for(int i=0; func_name[i]; i++) if(func_name[i] == '.') func_name[i] = '_';
    void (*f)(char *) = dlsym(RTLD_DEFAULT, func_name);
    if (f) {
        f(args);
    } else if (strcmp(command, "print") == 0) {
        printf("\033[1;36m[PRINT]: %s\033[0m\n", args);
    } else if (strcmp(command, "module") == 0) {
        char mod_path[256];
        if (sscanf(args, "{%255[^}]}", mod_path) == 1) {
            void *handle = dlopen(mod_path, RTLD_NOW | RTLD_GLOBAL);
            if (!handle) printf("\033[1;31m[ERR]: %s\033[0m\n", dlerror());
            else printf("\033[1;32m[SYS]: Module %s active\033[0m\n", mod_path);
        }
    } else {
        printf("\033[1;31m[ERR]: Command '%s' unknown\033[0m\n", command);
    }
}
int main(int argc, char *argv[]) {
    if (argc < 2) { printf("Usage: kynto <script>\n"); return 1; }
    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;
    char line[1024];
    int l_num = 1;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0;
        process_instruction(line, l_num++);
    }
    fclose(f);
    return 0;
}
