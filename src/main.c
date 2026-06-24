// includes
#include "../includes/ship.h"
#include "../includes/socket.h"
#include <arpa/inet.h>	// used for conversions
#include <fcntl.h>	// files, non blocking I/O
#include <netinet/in.h>	// address and protocol structures
#include <stdio.h>	// files, input and output
#include <stdlib.h>	// utility
#include <string.h>	// working with strings
#include <sys/socket.h>	// working with socket
#include <termios.h>	// terminal control
#include <time.h>	// self explanatory
#include <unistd.h>	//file, i/o, sleeping, pipes

// main function
int main() {
  // initialization of the connection 
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

  // creating your board and board for reference on which you attack
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
    if (send(client_sock, arr1, sizeof(arr1), 0) < 0) perror("send"); 
    if (recv(client_sock, arro, sizeof(arro), 0) < 0) perror("recv");
  } else {
    if (recv(sock, arro, sizeof(arro), 0) < 0) perror("recv");
    if (send(sock, arr1, sizeof(arr1), 0) < 0) perror("send");
  }

  //  main loop 2 attack phase (phase-2)
  while (attacking) {
    rendering(arrr);
    attack(arrr, arro);
  }

  return 0;
}
