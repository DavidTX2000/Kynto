#include <stdio.h>
#include <stdlib.h>

void git_snap(char *args) {
    char msg[256];
    if (sscanf(args, "{msg:\"%[^\"]\"}", msg) == 1) {
        char cmd[512];
        // Inicializa se não existir, adiciona e faz commit
        system("git init > /dev/null 2>&1");
        system("git add .");
        sprintf(cmd, "git commit -m \"%s\"", msg);
        system(cmd);
        printf("\033[1;32m[GIT]: Snapshot created: %s\033[0m\n", msg);
    }
}
