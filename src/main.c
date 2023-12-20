#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <http_req.h>
#include <util.h>
#include <arpa/inet.h>

#include <string.h>

#define PORT 80

int main(void) {

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
  
    // Create a new socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    // Define address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
  
    // Bind to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
  
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
  
    // Wait for a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    char buffer[1024] = {0};
    recv(new_socket, buffer, 1024, 0);
    http_req_t *req = validate_request(buffer, strlen(buffer));
    if (req == NULL) {
        printf("Invalid request\n");
        return -1;
    }
    printf("Request validated\n");
    return 0;
}
