#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    
    printf("Echo server starting...\n");

    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }
    printf("Socket created: %d\n", server_socket);

    // Define address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        return 1;
    }
    printf("Socket bound to port 8080\n");

    // Listen
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        return 1;
    }
    printf("Listening for connections on port 8080...\n");

    // Accept
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket < 0) {
        perror("Accept failed");
        return 1;
    }
    printf("Client connected!\n");

    return 0;
}
