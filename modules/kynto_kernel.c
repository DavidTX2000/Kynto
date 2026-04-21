#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kernel_scan(char* mode) {
    if (strcmp(mode, "thermal") == 0) {
        printf("[Kynto KERNEL] Scanning thermal zones...\n");
        system("ls /sys/class/thermal | grep thermal_zone | xargs -I {} sh -c 'printf \"{}: \"; cat /sys/class/thermal/{}/temp'");
    }
}

void kernel_io() {
    printf("[Kynto KERNEL] Disk I/O Stats (Reads/Writes):\n");
    system("cat /proc/diskstats | head -n 3");
}

void kernel_kill(char* pid) {
    printf("[Kynto KERNEL] Sending SIGKILL to PID: %s\n", pid);
    char cmd[50];
    sprintf(cmd, "kill -9 %s 2>/dev/null || echo '[!] Access Denied'", pid);
    system(cmd);
}
