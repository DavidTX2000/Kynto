#include <stdio.h>

void log_start() {
    FILE *f = fopen("kynto.log", "a");
    if (f) {
        fprintf(f, "[LOG] Logging started\n");
        fclose(f);
        printf("[LOG] Logging enabled (kynto.log)\n");
    } else {
        printf("[LOG] Failed to open file\n");
    }
}
