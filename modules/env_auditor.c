#include <stdio.h>
#include <stdlib.h>

void audit_environment() {
    char *path = getenv("PATH");
    printf("\n[KYNTO-SYS] Environment Security Audit:\n");
    printf("PATH: %s\n", path ? path : "NOT_FOUND");
    fflush(stdout);
}
