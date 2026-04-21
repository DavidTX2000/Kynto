#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void os_mkdir(char *args) {
    if (mkdir(args, 0777) == 0) printf("[OS]: Directory '%s' created.\n", args);
    else perror("[OS_ERR]");
}

void os_remove(char *args) {
    if (remove(args) == 0) printf("[OS]: '%s' deleted.\n", args);
    else perror("[OS_ERR]");
}

void os_getcwd(char *args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) printf("[OS]: %s\n", cwd);
}
