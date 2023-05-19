#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <pthread.h>

using namespace std;

void *connection_handler(void *);

int main(int argc, char *argv[]) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        cerr << "Could not create socket" << endl;
        return 1;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1234);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        cerr << "Bind failed" << endl;
        return 1;
    }

    listen(server_socket, 3);

    int c, *new_socket;
    sockaddr_in client_address;
    c = sizeof(sockaddr_in);

    while (1) {
        new_socket = new int;
        *new_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&c);

        if (*new_socket < 0) {
            cerr << "Accept failed" << endl;
            return 1;
        }

        pthread_t new_thread;
        if (pthread_create(&new_thread, NULL, connection_handler, (void *)new_socket) < 0) {
            cerr << "Could not create thread" << endl;
            return 1;
        }

        cout << "New client connected" << endl;
    }

    close(server_socket);

    return 0;
}

void *connection_handler(void *socket_desc) {
    int client_socket = *(int *)socket_desc;
    char client_message[2000];
while(1){
    if (recv(client_socket, client_message, 2000, 0) < 0) {
        cerr << "recv failed" << endl;
    }

    cout << "Client message: " << client_message << endl;
}
    char message[] = "Hello, client!";
    if (send(client_socket, message, strlen(message), 0) < 0) {
        cerr << "Send failed" << endl;
    }

    close(client_socket);

    delete socket_desc;
    pthread_exit(NULL);
}
