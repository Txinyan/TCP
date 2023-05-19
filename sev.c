#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock == -1) {
    fprintf(stderr, "Could not create socket\n");
    return 1;
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(1234);
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(sock, (struct sockaddr *)&server_address,
              sizeof(server_address)) < 0) {
    fprintf(stderr, "Connect failed\n");
    return 1;
  }

  char message[] = "Hello, server!";
  if (send(sock, message, strlen(message), 0) < 0) {
    fprintf(stderr, "Send failed\n");
    return 1;
  }

  char server_reply[2000];
  while(1)
  {
  if (recv(sock, server_reply, 2000, 0) < 0) {
    fprintf(stderr, "recv failed\n");
  }

  printf("Server reply: %s\n", server_reply);
  }

  // close(sock);

  return 0;
}
