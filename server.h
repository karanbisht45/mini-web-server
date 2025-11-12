#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 8192
#define MAX_CLIENTS 10

int initialize_winsock();
SOCKET create_socket();
void cleanup(SOCKET server_socket);
void handle_client(SOCKET client_socket, struct sockaddr_in client_addr);

#endif
