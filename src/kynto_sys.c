#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Comando para deletar arquivos de forma silenciosa
void fs_rm(char *args) {
    char path[512] = {0};
    if (sscanf(args, "{%[^}]}", path) == 1) {
        if (unlink(path) == 0) printf("\033[1;32m[FS]: File %s removed.\033[0m\n", path);
        else printf("\033[1;31m[FS_ERROR]: Access denied or file not found.\033[0m\n");
    }
}

// Comando para listar processos de forma filtrada
void sys_ps(char *args) {
    char filter[128] = {0};
    printf("\033[1;35m[SYS_MONITOR]: Active Processes\033[0m\n");
    if (sscanf(args, "{%[^}]}", filter) == 1) {
        char cmd[256];
        sprintf(cmd, "ps -e | grep \"%s\"", filter);
        system(cmd);
    } else {
        system("ps -e | head -n 10");
    }
}
