#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *cmds[] = {"print", "echo", "set", "notify", NULL};
const char** get_commands() { return cmds; }

void execute(const char *cmd, const char *arg) {
    if (strcmp(cmd, "print") == 0 || strcmp(cmd, "echo") == 0) {
        printf("%s\n", arg);
    } 
    else if (strcmp(cmd, "set") == 0) {
        int n1, n2;
        char var[32], op;
        // Tenta processar: variavel = numero operador numero (ex: x = 10 + 20)
        if (sscanf(arg, "%s = %d %c %d", var, &n1, &op, &n2) == 4) {
            if (op == '+') printf("[Var %s] Result: %d\n", var, n1 + n2);
            else if (op == '*') printf("[Var %s] Result: %d\n", var, n1 * n2);
            else if (op == '-') printf("[Var %s] Result: %d\n", var, n1 - n2);
        } else {
            printf("[Var Set]: %s\n", arg);
        }
    } 
    else if (strcmp(cmd, "notify") == 0) {
        char sys[512];
        snprintf(sys, sizeof(sys), "termux-notification -t 'Kynto Engine' -c '%s'", arg);
        system(sys);
    }
}
