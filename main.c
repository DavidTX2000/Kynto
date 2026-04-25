#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <ctype.h>

void *loaded_handles[100];
int mod_count = 0;

typedef struct {
    char cmd[64];
    char target_func[64];
} Map;

Map registry[500];
int reg_count = 0;

void scan_source(const char* so_path) {
    char c_path[256];
    strcpy(c_path, so_path);
    char *ext = strrchr(c_path, '.');
    if (ext) strcpy(ext, ".c");

    FILE *f = fopen(c_path, "r");
    if (!f) return;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if ((strstr(line, "void ") || strstr(line, "int ")) && strchr(line, '(')) {
            char temp[256];
            strcpy(temp, line);
            char *token = strtok(temp, " \t(");
            token = strtok(NULL, " \t("); 
            if (token) {
                char *fname = token;
                if (reg_count < 500) {
                    strcpy(registry[reg_count].cmd, fname);
                    strcpy(registry[reg_count].target_func, fname);
                    reg_count++;
                    
                    if (strstr(fname, "dashboard")) {
                        strcpy(registry[reg_count].cmd, "ultra");
                        strcpy(registry[reg_count].target_func, fname);
                        reg_count++;
                        strcpy(registry[reg_count].cmd, "hw");
                        strcpy(registry[reg_count].target_func, fname);
                        reg_count++;
                    }
                    if (strstr(fname, "ui_window") || strstr(fname, "ui_color")) {
                        strcpy(registry[reg_count].cmd, "ui");
                        strcpy(registry[reg_count].target_func, fname);
                        reg_count++;
                    }
                }
            }
        }
    }
    fclose(f);
}

void load_module(char* line) {
    char *start = strchr(line, '{');
    char *end = strrchr(line, '}');
    if (start && end) {
        start++; *end = '\0';
        void *h = dlopen(start, RTLD_NOW | RTLD_GLOBAL);
        if (h) {
            loaded_handles[mod_count++] = h;
            scan_source(start);
        }
    }
}

void execute_module_direct(char* mod_path, char* function) {
    void *handle = dlopen(mod_path, RTLD_LAZY);
    if (!handle) return;
    void (*func)() = dlsym(handle, function);
    if (func) {
        func();
        fflush(stdout);
    }
    dlclose(handle);
}

void parse_and_execute(char* line, int line_num) {
    while(isspace((unsigned char)*line)) line++;
    if (*line == '\0' || *line == '#') return;

    if (strncmp(line, "print", 5) == 0) {
        char *msg = strchr(line, '{');
        if (msg) {
            msg++;
            char *end = strrchr(line, '}');
            if(end) { *end = '\0'; printf("%s\n", msg); }
        }
        return;
    }

    if (strncmp(line, "notify", 6) == 0) {
        char *msg = strchr(line, '{');
        if (msg) {
            msg++;
            char *end = strrchr(line, '}');
            if(end) {
                *end = '\0';
                char command[1024];
                snprintf(command, sizeof(command), "termux-notification --title 'Kynto Engine' --content '%s'", msg);
                system(command);
            }
        }
        return;
    }

    if (strstr(line, "hw{action: \"dashboard\"") != NULL) {
        execute_module_direct("./modules/kynto_overkill.so", "print_overkill_dashboard");
        return;
    }

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
        char *end_cmd = cmd + strlen(cmd) - 1;
        while(end_cmd >= cmd && isspace((unsigned char)*end_cmd)) { *end_cmd = '\0'; end_cmd--; }
    }

    if (strcmp(cmd, "module") == 0 || strcmp(cmd, "loop") == 0) return;

    int found = 0;
    for (int i = 0; i < mod_count; i++) {
        for (int j = 0; j < reg_count; j++) {
            if (strcmp(cmd, registry[j].cmd) == 0) {
                void (*f)(char*) = dlsym(loaded_handles[i], registry[j].target_func);
                if (f) {
                    f(arg);
                    fflush(stdout);
                    found = 1;
                    break;
                }
            }
        }
        if (found) break;

        void (*f)(char*) = dlsym(loaded_handles[i], cmd);
        if (f) {
            f(arg);
            fflush(stdout);
            found = 1;
            break;
        }
    }

    if (!found) {
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
        char *ln_ptr = line;
        while(isspace((unsigned char)*ln_ptr)) ln_ptr++;
        if (strncmp(ln_ptr, "module", 6) == 0) load_module(ln_ptr);
        else parse_and_execute(line, line_num);
    }
    fclose(file);
    return 0;
}
