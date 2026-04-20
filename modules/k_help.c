#include <stdio.h>

void help_list(char *args) {
    printf("\033[1;33m--- KYNTO COMMAND DIRECTORY ---\033[0m\n");
    printf("Core: module, print, help.list\n");
    printf("HW:   hw.battery, hw.thermal, hw.vibrate\n");
    printf("Sys:  sys.mem, sys.ps, sys.shell, sys.uptime\n");
    printf("Net:  net.local_ip, net.ping, net.download\n");
    printf("Time: time.now, time.sleep\n");
    printf("\033[1;33m-------------------------------\033[0m\n");
}
