#include <stdio.h>

void audit_entropy() {
    int avail;
    FILE *fp = fopen("/proc/sys/kernel/random/entropy_avail", "r");
    if (fp) {
        fscanf(fp, "%d", &avail);
        fclose(fp);
        printf("\n[KYNTO-SEC] Entropy Level: %d bits\n", avail);
    }
    fflush(stdout);
}
