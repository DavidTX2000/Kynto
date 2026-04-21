#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>

void sys_ram() {
    struct sysinfo si;
    sysinfo(&si);
    printf("[Kynto SYS] RAM Usage: %ld MB / %ld MB\n", (si.totalram - si.freeram) / 1024 / 1024, si.totalram / 1024 / 1024);
}

void sys_uptime() {
    struct sysinfo si;
    sysinfo(&si);
    printf("[Kynto SYS] Uptime: %ld hours\n", si.uptime / 3600);
}

void sys_storage() {
    printf("[Kynto SYS] Partition Status: OK\n");
    system("df -h /data | grep /data");
}

void sys_kernel() {
    system("printf '[Kynto SYS] Kernel: '; uname -r");
}

void sys_load() {
    // Lendo direto do sistema para evitar erro de declaração
    FILE *f = fopen("/proc/loadavg", "r");
    if (f) {
        float l1;
        fscanf(f, "%f", &l1);
        fclose(f);
        printf("[Kynto SYS] CPU Load (1min): %.2f\n", l1);
    }
}
