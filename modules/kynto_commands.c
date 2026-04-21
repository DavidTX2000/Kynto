#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *cmds[] = {"print", "echo", "set", "notify", "hardware", NULL};
const char** get_commands() { return cmds; }

void execute(const char *cmd, const char *arg) {
    if (strcmp(cmd, "print") == 0 || strcmp(cmd, "echo") == 0) {
        printf("%s\n", arg);
    }
    else if (strcmp(cmd, "set") == 0) {
        int n1, n2;
        char var[32], op;
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
    else if (strcmp(cmd, "hardware") == 0) {
        FILE *fp;
        char buffer[16];
        if (strstr(arg, "battery") != NULL) {
            fp = fopen("/sys/class/power_supply/battery/capacity", "r");
            if (fp) {
                fgets(buffer, sizeof(buffer), fp);
                buffer[strcspn(buffer, "\n")] = 0;
                printf("[Kynto HW] Battery: %s%%\n", buffer);
                fclose(fp);
            }
        } else if (strstr(arg, "temp") != NULL) {
            fp = fopen("/sys/class/power_supply/battery/temp", "r");
            if (fp) {
                fgets(buffer, sizeof(buffer), fp);
                printf("[Kynto HW] Temp: %.1f°C\n", atof(buffer) / 10.0);
                fclose(fp);
            }
        }
    }
}
