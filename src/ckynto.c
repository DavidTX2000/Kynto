#include "kynto.h"

Variable symbol_table[MAX_VARS];
int var_count = 0;

void k_set_var(const char *n, const char *v) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(symbol_table[i].name, n) == 0) {
            strcpy(symbol_table[i].value, v);
            return;
        }
    }
    if (var_count < MAX_VARS) {
        strcpy(symbol_table[var_count].name, n);
        strcpy(symbol_table[var_count].value, v);
        var_count++;
    }
}

char* k_get_var(const char *n) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(symbol_table[i].name, n) == 0) return symbol_table[i].value;
    }
    return "";
}

KyntoAPI api = { k_set_var, k_get_var };

void process_instruction(char *line) {
    while(*line == ' ' || *line == '\t') line++;
    if (*line == '\0' || strncmp(line, "//", 2) == 0) return;
    
    char cmd[64] = "", args[1024] = "";
    char *sp = strchr(line, ' ');
    if (!sp) return;
    *sp = '\0';
    strcpy(cmd, line);
    strcpy(args, sp + 1);

    if (strcmp(cmd, "set") == 0) {
        void (*f)(char *, KyntoAPI *) = dlsym(RTLD_DEFAULT, "memory_set");
        if (f) f(args, &api);
    } else if (strcmp(cmd, "print") == 0) {
        char *s = strchr(args, '{'), *e = strrchr(args, '}');
        if (s && e) {
            for (char *c = s + 1; c < e; c++) {
                if (*c == '$') {
                    char vn[64] = {0}; int k = 0; c++;
                    while (c < e && ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9'))) vn[k++] = *c++;
                    printf("%s", k_get_var(vn));
                    c--;
                } else printf("%c", *c);
            }
            printf("\n");
        }
    } else if (strcmp(cmd, "module") == 0) {
        char *s = strchr(args, '{'), *e = strrchr(args, '}');
        if (s && e) {
            char path[256] = {0};
            memcpy(path, s + 1, e - s - 1);
            dlopen(path, RTLD_NOW | RTLD_GLOBAL);
        }
    } else {
        void (*f)(char *, KyntoAPI *) = dlsym(RTLD_DEFAULT, cmd);
        if (f) {
            char *s = strchr(args, '{'), *e = strrchr(args, '}');
            if (s && e) { *e = '\0'; f(s + 1, &api); }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0;
        process_instruction(line);
    }
    fclose(f);
    return 0;
}
