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
  printf("=== PROGRAM START ===\n");
  fflush(stdout);
  // --- Phase-1 ---
  printf("\033[1;1H\033[2J");  //clears the terminal screen
  // initialization of the connection 
  char room;
  do {
    printf("type h for host or j for join.(lower case)\n");
    scanf(" %c", &room);
    if (room == 'h') host_init();
    else if (room == 'j') join_init();
    else printf("Type a valid character\n");
  } while (room != 'j' && room != 'h');

  // variables
  int turn = 0;
  int attacking = 1;
  int placing = 1;
  char move;
  char arro[14][14];

  // creating your board and board for reference on which you attack
  char your_placement[14][14];
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 14; j++) {
      your_placement[i][j] = '.';
    }
  }
  char reference[14][14];
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 14; j++) {
      reference[i][j] = '.';
    }
  }

  // --- Phase-2 ---
  printf("\033[1;1H\033[2J"); 
  // main loop 1 ship placement 
  place(your_placement);

  // sending your and fetching opponent ship placement
  if (room == 'h') {
    if (send(client_sock, your_placement, sizeof(your_placement), 0) < 0) perror("send"); 
    if (recv(client_sock, arro, sizeof(arro), 0) < 0) perror("recv");
  } else {
    if (recv(sock, arro, sizeof(arro), 0) < 0) perror("recv");
    if (send(sock, your_placement, sizeof(your_placement), 0) < 0) perror("send");
  }

  //  --- Phase-3 ---
  printf("\033[1;1H\033[2J"); 
  //  main loop 2 attack phase 
  while (attacking) {
    char *attack_coords;
    printf("Type X and Y co-ordinates of the attack with a space in between: \n");
    fgets(attack_coords, sizeof(attack_coords), stdin);
    rendering(reference);
    attack(reference, attack_coords);
  }

  return 0;
}
