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
  // --- Phase-1 ---
  printf("\033[1;1H\033[2J");  //clears the terminal screen
  // initialization of the connection 
  char room;
  do {
    char buf[4];
    printf("type h for host or j for join.(lower case)\n");
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%c", &room);
    if (room == 'h') host_init();
    else if (room == 'j') join_init();
    else printf("Type a valid character\n");
  } while (room != 'j' && room != 'h');

  // variables
  int turn;
  int attacking = 1;
  int placing = 1;
  char opponent_placement[14][14];

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
    int bytes = recv(client_sock, opponent_placement, sizeof(opponent_placement), 0);
    if (bytes <= 0) {
      printf("Failed to receive opponent's placement. Exiting.\n");
      return 1;
    }
  } else {
    int bytes = recv(sock, opponent_placement, sizeof(opponent_placement), 0);
    if (bytes <= 0) {
      printf("Failed to receive opponent's placement. Exiting.\n");
      return 1;
    }
    if (send(sock, your_placement, sizeof(your_placement), 0) < 0) perror("send");
  }

  //  --- Phase-3 ---
  printf("\033[1;1H\033[2J"); 
  //  main loop 2 attack phase 
  if (room=='h')turn=1;
  else turn=0;

  while (attacking) {
    if (turn) {
      attack(reference, opponent_placement, &turn);
      if (turn == 2) {
        printf("YOU WIN!\n");
        int next_turn = -1;
        if (room == 'h') {
          if (send(client_sock, &next_turn, sizeof(next_turn), 0) < 0) perror("send");
        } else {
          if (send(sock, &next_turn, sizeof(next_turn), 0) < 0) perror("send");
        }
        attacking = 0;
        break;
      }
      int next_turn = 1;
      if (room == 'h') {
        if (send(client_sock, &next_turn, sizeof(next_turn), 0) < 0) perror("send"); 
      } else {
        if (send(sock, &next_turn, sizeof(next_turn), 0) < 0) perror("send");
      }
    } else {
      int bytes_received;
      if (room == 'h') {
        bytes_received = recv(client_sock, &turn, sizeof(turn), 0);
      } else {
        bytes_received = recv(sock, &turn, sizeof(turn), 0);
      }
      if (bytes_received <= 0) {
        printf("Opponent disconnected. Exiting.\n");
        attacking = 0;
        break;
      }
      if (turn == -1) {
        printf("YOU LOSE!\n");
        attacking = 0;
        break;
      }
    }
  }

  return 0;
}
