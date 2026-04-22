#include <stdio.h>
#include <string.h>

void audit_memory_maps() {
    FILE *fp = fopen("/proc/self/maps", "r");
    char line[256];
    printf("\n[KYNTO-CORE] Memory Map Audit:\n");
    while (fp && fgets(line, sizeof(line), fp)) {
        if (strstr(line, "[heap]") || strstr(line, "[stack]")) {
            printf("-> %s", line);
        }
    }
    if (fp) fclose(fp);
    fflush(stdout);
}
