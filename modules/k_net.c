#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Esta é a função que o seu ckynto.c chama via dlsym
void proxy_server(const char* args) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Criando o socket descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("[NET_ERROR]: Falha ao criar socket\n");
        return;
    }

    // Configuração para liberar a porta rapidamente após fechar
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Vinculando à porta 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("[NET_ERROR]: Erro no Bind. A porta 8080 pode estar ocupada.\n");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 3) < 0) {
        printf("[NET_ERROR]: Erro no Listen\n");
        return;
    }

    printf("\n[SYSTEM]: Kynto Proxy ATIVO em http://localhost:8080\n");
    printf("[SYSTEM]: Aguardando conexões... (Ctrl+C para encerrar)\n");

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket >= 0) {
            printf("[NET]: Conexão recebida!\n");
            
            // Resposta HTTP básica para o navegador não dar erro
            char *msg = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nKynto Engine Proxy: Connection Successful!";
            send(new_socket, msg, strlen(msg), 0);
            
            close(new_socket);
        }
    }
}
