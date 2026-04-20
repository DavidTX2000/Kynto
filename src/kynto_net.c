#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comando para download de arquivos (HTTP/HTTPS)
void net_get(char *args) {
    char url[512] = {0};
    if (sscanf(args, "{%[^}]}", url) == 1) {
        printf("\033[1;34m[NET_GET]: Requesting secure resource...\033[0m\n");
        char cmd[1024];
        // -L segue redirecionamentos, -O salva com o nome original
        sprintf(cmd, "curl -L -O \"%s\" --silent", url);
        int res = system(cmd);
        if (res == 0) printf("\033[1;32m[SUCCESS]: Resource synchronized.\033[0m\n");
        else printf("\033[1;31m[ERROR]: Connection failed.\033[0m\n");
    }
}

// Comando para testar latência (Ping)
void net_ping(char *args) {
    char host[256] = {0};
    if (sscanf(args, "{%[^}]}", host) == 1) {
        printf("\033[1;36m[NET_PING]: Checking host %s...\033[0m\n", host);
        char cmd[512];
        sprintf(cmd, "ping -c 3 %s", host);
        system(cmd);
    }
}
