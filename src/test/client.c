// includes
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // Create socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  // Server address
  struct sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

  // Connect
  if (connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
    perror("sock");
  }

  // Send
  int buff[4][4] = {{1, 6, 7, 3}, {5, 1, 4, 6}, {9, 4, 1, 7}, {5, 6, 1, 0}};
  if (send(sock, buff, sizeof(buff), 0) < 0) {
    perror("send");
  }
  printf("sent");
  // Close
  close(sock);
  return 0;
}
