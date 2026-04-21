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
    return "NULL";
}

KyntoAPI api = { k_set_var, k_get_var };

void show_help() {
    printf("\n==== KYNTO ENGINE - 100 COMMANDS MANUAL ====\n");
    printf("\n[ BASIC: 1-50 ]\n");
    printf("- set/print/module/help/clear/exit\n");
    printf("- math.add/sub/mul/div/mod/pow/sqrt/rand\n");
    printf("- str.len/upper/lower/trim/rev/split/at\n");
    printf("- var.del/list/copy/type/exists\n");
    
    printf("\n[ ADVANCED: 51-100 ]\n");
    printf("- file.read/write/append/del/exists/size/move\n");
    printf("- sys.exec/os/user/ip/cpu/ram/uptime/reboot\n");
    printf("- net.get/post/ping/download/server/port\n");
    printf("- crypt.aes.enc/dec/sha256/md5/base64\n");
    printf("\nFull documentation: https://github.com/DavidTX2000/kynto_os\n");
}

void process_instruction(char *line) {
    while(*line == ' ' || *line == '\t') line++;
    if (*line == '\0' || strncmp(line, "//", 2) == 0) return;
    if (strcmp(line, "help") == 0) { show_help(); return; }

    char cmd[64] = "", args[1024] = "";
    char *sp = strchr(line, ' ');
    if (sp) { *sp = '\0'; strcpy(cmd, line); strcpy(args, sp + 1); }
    else { strcpy(cmd, line); }

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
                    printf("%s", k_get_var(vn)); c--;
                } else printf("%c", *c);
            }
            printf("\n");
        }
    } else if (strcmp(cmd, "module") == 0) {
        char *s = strchr(args, '{'), *e = strrchr(args, '}');
        if (s && e) {
            char path[256] = {0}; memcpy(path, s + 1, e - s - 1);
            dlopen(path, RTLD_NOW | RTLD_GLOBAL);
        }
    } else {
        char func_name[128];
        sprintf(func_name, "%s", cmd);
        for(int i=0; func_name[i]; i++) if(func_name[i] == '.') func_name[i] = '_';
        void (*f)(char *, KyntoAPI *) = dlsym(RTLD_DEFAULT, func_name);
        if (f) {
            char *s = strchr(args, '{'), *e = strrchr(args, '}');
            if (s && e) { *e = '\0'; f(s + 1, &api); } else f(args, &api);
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
