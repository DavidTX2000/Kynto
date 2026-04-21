#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef void (*cmd_func)(const char *, const char *);
typedef const char** (*list_func)();

typedef struct {
    char cmd_name[32];
    void *handle;
    cmd_func execute;
} CommandMap;

CommandMap registry[512];
int reg_count = 0;

void load_module(char *path) {
    void *h = dlopen(path, RTLD_LAZY);
    if (!h) return;
    list_func list = (list_func)dlsym(h, "get_commands");
    cmd_func exec = (cmd_func)dlsym(h, "execute");
    if (!list || !exec) return;
    const char **cmds = list();
    for (int i = 0; cmds[i] != NULL; i++) {
        strncpy(registry[reg_count].cmd_name, cmds[i], 31);
        registry[reg_count].handle = h;
        registry[reg_count].execute = exec;
        reg_count++;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Kynto Engine v4.0.0\nUsage: kynto <script.ky>\n");
        return 0;
    }
    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0 || line[0] == '/') continue;
        if (strncmp(line, "module ", 7) == 0) {
            char *p = strchr(line, '{') + 1;
            char *e = strchr(p, '}');
            if (e) *e = '\0';
            load_module(p);
        } else {
            char *c = strtok(line, "{");
            char *a = strtok(NULL, "}");
            if (c) {
                for (int i = 0; i < reg_count; i++) {
                    if (strcmp(c, registry[i].cmd_name) == 0) {
                        registry[i].execute(c, a ? a : "");
                        break;
                    }
                }
            }
        }
    }
    fclose(f);
    return 0;
}
