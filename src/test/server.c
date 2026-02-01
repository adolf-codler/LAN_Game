// includes
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // Create socket, binding, reuse if using, listen to clients
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
  }
  printf("socket created\n");

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_port = htons(8080);
  serv.sin_addr.s_addr = INADDR_ANY;
  if (bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
    perror("bind");
  }
  printf("binded to port 8080\n");

  if (listen(sock, 5) < 0) {
    perror("listen");
  }
  printf("listening...\n");

  // Accept
  struct sockaddr_in client;
  socklen_t clen = sizeof(client);
  int client_sock = accept(sock, (struct sockaddr *)&client, &clen);
  if (client_sock < 0) {
    perror("client_socket");
  }

  // recieve
  int buf[4][4];
  printf("recieved :");
  if (recv(client_sock, buf, sizeof(buf), 0) < 0) {
    perror("recieve");
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d, ", buf[i][j]);
    }
    printf("\n");
  }

  // Close
  close(client_sock);
  close(sock);
  printf("\nsocket closed\n");

  return 0;
}
