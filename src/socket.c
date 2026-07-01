// includes
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int client_sock;
int sock;
char IP[16];

void host_init() {
  // Create socket, binding, reuse if using, listen to clients
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
    exit(1);
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
    exit(1);
  }
  printf("binded to port 8080\n");

  if (listen(sock, 5) < 0) {
    perror("listen");
    exit(1);
  }
  printf("waiting for someone to join\n");
  struct sockaddr_in client;
  socklen_t clen = sizeof(client);
  client_sock = accept(sock, (struct sockaddr *)&client, &clen);
  if (client_sock < 0) {
    perror("client_socket");
    exit(1);
  }
  printf("Joined\n");
}

void join_init() {
  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
    exit(1);
  }

  // Server address
  join:
  printf("Enter the host's ip:\n");
  char buf[64];
  if (fgets(buf, sizeof(buf), stdin) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    strncpy(IP, buf, sizeof(IP) - 1);
    IP[sizeof(IP) - 1] = '\0';
  } else {
    printf("Failed to read input.\n");
    goto join;
  }
  struct sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_port = htons(8080);
  if (inet_pton(AF_INET, IP, &serv.sin_addr) <= 0) {
    printf("invalid ip address \n"); 
    goto join;
  }

  // Connect
  if (connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
    perror("sock");
    exit(1);
  }
}

void send_recieve_data() {}
