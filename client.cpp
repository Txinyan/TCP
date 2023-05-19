#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        cerr << "Could not create socket" << endl;
        return 1;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1234);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (sockaddr *)&server_address, sizeof(server_address)) < 0) {
        cerr << "Connect failed" << endl;
        return 1;
    }

    char message[] = "Hello, server!";
    if (send(sock, message, strlen(message), 0) < 0) {
        cerr << "Send failed" << endl;
        return 1;
    }

    char server_reply[2000];
    if (recv(sock, server_reply, 2000, 0) < 0) {
        cerr << "recv failed" << endl;
    }

    cout << "Server reply: " << server_reply << endl;

    // close(sock);

    return 0;
}
