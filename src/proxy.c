#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

// Estrutura para passar dados para a thread
typedef struct {
    int port;
} proxy_config;

// Função que roda em segundo plano
void *run_server(void *var) {
    proxy_config *config = (proxy_config *)var;
    int port = config->port;
    
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) return NULL;
    listen(server_fd, 5);

    printf("\033[1;32m[PROXY_THREAD]: Server backgrounded on port %d.\033[0m\n", port);
    
    // O servidor ficaria aqui aceitando conexões...
    // Para este exemplo, ele apenas mantém o socket aberto
    while(1) { sleep(10); } 

    return NULL;
}

void proxy_server(char *args) {
    int port = 8080;
    sscanf(args, "{%d}", &port);

    pthread_t thread_id;
    proxy_config *config = malloc(sizeof(proxy_config));
    config->port = port;

    // Cria a thread separada
    if(pthread_create(&thread_id, NULL, run_server, (void*)config) != 0) {
        printf("[ERROR]: Failed to launch background thread.\n");
    } else {
        pthread_detach(thread_id); // Libera recursos automaticamente ao fechar
        printf("\033[1;34m[KERNEL]: Proxy task handed over to Thread %lu.\033[0m\n", thread_id);
    }
}
