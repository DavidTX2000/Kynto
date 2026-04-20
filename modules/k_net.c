#include <stdio.h>
#include <stdlib.h>
void net_ping(char *args) {
    char cmd[256];
    sprintf(cmd, "ping -c 3 %s", args);
    system(cmd);
}
void net_local_ip(char *args) {
    printf("[NET_IP]: ");
    system("hostname -I | awk '{print $1}'");
}
void net_download(char *args) {
    char url[256], file[256], cmd[600];
    if (sscanf(args, "%[^,],%s", url, file) == 2) {
        sprintf(cmd, "curl -L %s -o %s", url, file);
        system(cmd);
    }
}
