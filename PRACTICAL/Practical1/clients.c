#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    char msg[1024];
    char buffer[1024] = {0};

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Set server IP and port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);

    // Server IP (same computer)
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 3. Connect to server
    connect(sock, (struct sockaddr *)&serv_addr,
            sizeof(serv_addr));

    printf("Connected to server!\n");

    // 4. Two-way chat loop
    while (1) {
        printf("You: ");

        fgets(msg, sizeof(msg), stdin);

        send(sock, msg, strlen(msg), 0);

        if (strncmp(msg, "exit", 4) == 0)
            break;

        memset(buffer, 0, sizeof(buffer));

        read(sock, buffer, sizeof(buffer));

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        printf("Server: %s", buffer);
    }

    // 5. Close socket
    close(sock);

    return 0;
}
