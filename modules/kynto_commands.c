#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *cmds[] = {"print", "echo", "set", "notify", NULL};

const char** get_commands() {
    return cmds;
}

void execute(const char *cmd, const char *arg) {
    if (strcmp(cmd, "print") == 0 || strcmp(cmd, "echo") == 0) {
        printf("%s\n", arg);
    } else if (strcmp(cmd, "set") == 0) {
        printf("[Var Set]: %s\n", arg);
    } else if (strcmp(cmd, "notify") == 0) {
        char sys[512];
        snprintf(sys, sizeof(sys), "termux-notification -c '%s'", arg);
        system(sys);
    }
}
