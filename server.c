#include "server.h"

// Get MIME type based on file extension
const char* get_mime_type(const char* filename) {
    if (strstr(filename, ".html")) return "text/html";
    if (strstr(filename, ".css")) return "text/css";
    if (strstr(filename, ".js")) return "application/javascript";
    if (strstr(filename, ".png")) return "image/png";
    if (strstr(filename, ".jpg") || strstr(filename, ".jpeg")) return "image/jpeg";
    return "text/plain";
}

// Initialize Winsock
int initialize_winsock() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }
    printf("[OK] Winsock initialized successfully.\n");
    return 0;
}

// Create and bind server socket
SOCKET create_socket() {
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        return INVALID_SOCKET;
    }

    if (listen(server_socket, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        return INVALID_SOCKET;
    }

    printf("[OK] Server listening on http://localhost:%d\n", PORT);
    return server_socket;
}

// Handle client requests
void handle_client(SOCKET client_socket, struct sockaddr_in client_addr) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) return;
    buffer[bytes_received] = '\0';

    char method[8], path[1024];
    sscanf(buffer, "%s %s", method, path);

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    printf("\n[Client %s] Request: %s %s\n", client_ip, method, path);

    char response[BUFFER_SIZE * 2];

    // 🌍 Redirect routes
    if (strcmp(path, "/google") == 0) {
        snprintf(response, sizeof(response),
            "HTTP/1.1 302 Found\r\n"
            "Location: https://www.google.com\r\n\r\n");
        send(client_socket, response, strlen(response), 0);
    }
    else if (strcmp(path, "/youtube") == 0) {
        snprintf(response, sizeof(response),
            "HTTP/1.1 302 Found\r\n"
            "Location: https://www.youtube.com\r\n\r\n");
        send(client_socket, response, strlen(response), 0);
    }
    else if (strcmp(path, "/github") == 0) {
        snprintf(response, sizeof(response),
            "HTTP/1.1 302 Found\r\n"
            "Location: https://github.com\r\n\r\n");
        send(client_socket, response, strlen(response), 0);
    }
    else if (strcmp(path, "/wikipedia") == 0) {
        snprintf(response, sizeof(response),
            "HTTP/1.1 302 Found\r\n"
            "Location: https://www.wikipedia.org\r\n\r\n");
        send(client_socket, response, strlen(response), 0);
    }
    // 🧠 Dynamic routes
    else if (strcmp(path, "/hello") == 0) {
        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
            "<h1>Hello!</h1><p>This is a dynamic response from your C Web Server.</p>");
        send(client_socket, response, strlen(response), 0);
    }
    else if (strcmp(path, "/time") == 0) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char time_str[100];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
            "<h1>Server Time</h1><p>%s</p>", time_str);
        send(client_socket, response, strlen(response), 0);
    }
    else if (strcmp(path, "/status") == 0) {
        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n\r\n"
            "{\"status\": \"running\", \"port\": %d, \"server\": \"Mini C Web Server\"}", PORT);
        send(client_socket, response, strlen(response), 0);
    }
    // 📄 Static file serving
    else {
        char filename[1024];
        if (strcmp(path, "/") == 0)
            strcpy(filename, "index.html");
        else
            strcpy(filename, path + 1);

        FILE *file = fopen(filename, "rb");
        if (file) {
            char file_content[BUFFER_SIZE];
            size_t bytes_read = fread(file_content, 1, sizeof(file_content), file);
            fclose(file);

            snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n\r\n",
                get_mime_type(filename));

            send(client_socket, response, strlen(response), 0);
            send(client_socket, file_content, bytes_read, 0);
            printf("[OK] Served file: %s\n", filename);
        } else {
            snprintf(response, sizeof(response),
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n\r\n"
                "<h1>404 Not Found</h1><p>Path '%s' not found.</p>", path);
            send(client_socket, response, strlen(response), 0);
            printf("[404] File not found: %s\n", filename);
        }
    }

    closesocket(client_socket);
}

// Cleanup
void cleanup(SOCKET server_socket) {
    closesocket(server_socket);
    WSACleanup();
    printf("[OK] Server shutdown complete.\n");
}

// Main
int main() {
    printf("=== Mini Web Server Starting ===\n");

    if (initialize_winsock() != 0) return 1;

    SOCKET server_socket = create_socket();
    if (server_socket == INVALID_SOCKET) return 1;

    while (1) {
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket == INVALID_SOCKET) continue;

        handle_client(client_socket, client_addr);
    }

    cleanup(server_socket);
    return 0;
}
