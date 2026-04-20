#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sys_shell(char *args) {
    printf("[SYS_SHELL]: Executing...\n");
    system(args);
}

void sys_ps(char *args) {
    printf("\033[1;36m[PROCESS_LIST]:\033[0m\n");
    system("ps -e | head -n 10");
}

void sys_mem(char *args) {
    printf("\033[1;32m[MEMORY_INFO]:\033[0m\n");
    system("free -h");
}

void sys_uptime(char *args) {
    printf("[UPTIME]: ");
    system("uptime -p");
}
