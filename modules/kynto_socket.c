#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void socket_scan(char* ports) {
    printf("[Kynto SOCKET] Rapid Scan on ports: %s\n", ports);
    char cmd[256];
    sprintf(cmd, "for port in $(echo %s | tr ',' ' '); do (echo >/dev/tcp/127.0.0.1/$port) >/dev/null 2>&1 && echo \"[+] Port $port: OPEN\" || echo \"[-] Port $port: CLOSED\"; done", ports);
    system(cmd);
}

void socket_listen(char* port) {
    printf("[Kynto SOCKET] Opening listener on port %s...\n", port);
    printf("[Kynto SOCKET] Status: LISTENING (Press Ctrl+C to stop)\n");
    // Simulação de socket bind para o print
}
