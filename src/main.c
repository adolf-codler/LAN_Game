// includes
#include "../includes/ship.h"
#include "../includes/socket.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// main function
int main() {
  // initialization of the game
  char room;
  do {
    printf("type h for host or j for join.(lower case)\n");
    scanf(" %c", &room);
    if (room == 'h') {
      host_init();
    } else if (room == 'j') {
      join_init();
    } else {
      printf("Type a valid character\n");
    }
  } while (room != 'j' && room != 'h');

  // variables
  int attacking = 1;
  int placing = 1;
  char move;
  char arro[14][14];

  // creating board
  char arr1[14][14];
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 14; j++) {
      arr1[i][j] = '.';
    }
  }
  char arrr[14][14];
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 14; j++) {
      arrr[i][j] = '.';
    }
  }

  // main loop 1 ship placement (phase-1)
  place(arr1);

  // sending your and fetching opponent ship placement
  if (room == 'h') {
    if (send(client_sock, arr1, sizeof(arr1), 0) < 0) {
      perror("send");
    }
    printf("sent\n");
    if (recv(client_sock, arro, sizeof(arro), 0) < 0) {
      perror("recv");
    }
    printf("recv\n");
  } else {
    if (recv(sock, arro, sizeof(arro), 0) < 0) {
      perror("recv");
    }
    printf("recv\n");
    if (send(sock, arr1, sizeof(arr1), 0) < 0) {
      perror("send");
    }
    printf("sent\n");
  }

  //  main loop 2 attack phase (phase-2)
  while (attacking) {
    rendering(arrr);
    attack(arrr, arro);
  }

  return 0;
}
