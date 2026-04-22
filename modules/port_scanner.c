#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void run_local_port_scanner() {
    printf("\n[KYNTO-NET] Scanning Localhost Ports...\n");
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == 0) 
        printf("Port 8080: OPEN\n");
    close(sock);
    fflush(stdout);
}
