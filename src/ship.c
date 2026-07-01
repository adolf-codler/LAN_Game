#include "../includes/ship.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void rendering(char arr[14][14]) {
  printf("  ");
  for (int i = 0; i < 14; i++) {
    printf("%2d ", i);
  }
  printf("\n");
  for (int i = 0; i < 14; i++) {
    printf("%2d ", i);
    for (int j = 0; j < 14; j++) {
      printf("%c  ", arr[i][j]);
    }
    printf("\n");
  }
}

void place(char arr[14][14]) {
  // variables and misc.
  char *ships_name[6] = {"WarShip(6)", "BattleShip(5)", "Submarine(4)", "Ship(3)", "Boat(2)", "Boat(2)"};
  int ships_size[6] = {6, 5, 4, 3, 2, 2};
  char *error="";
  for (int i = 0; i < 6; i++) {
    printf("\033[1;1H\033[2J"); 
    if(error[0]!='\0') printf("%s \n",error);
    error = "";
    rendering(arr);
    printf("Type X, Y co-ordinates and orientation of %s: \n",ships_name[i]);

    // getting placement
    char place_coords[128];
if (fgets(place_coords, sizeof(place_coords), stdin) == NULL) {
    perror("fgets");
}
    int a, b;
    char orientation;
    if (sscanf(place_coords, "%d %d %c", &a, &b, &orientation) != 3) {
      error = "Invalid format. Use: X Y Orientation (e.g., 5 5 h).";
      i--;
      continue;
    }

    // validating inputs
    if (a < 0 || a >= 14 || b < 0 || b >= 14 ) {
      error = "Invalid co-ordinates. Try again.";
      i--; // repeat this ship
      continue;
    }
    if(orientation!='v' && orientation!='h'){
      error = "Invalid orientation. Try again.";
      i--;
      continue;
    }

    // checking boundaries
    if (orientation == 'v' && (ships_size[i] + b - 1) > 13) {
      error = "Ship is out of boundaries. Try again.";
      i--;
      continue;
    }
    if (orientation == 'h' && (ships_size[i] + a - 1) > 13) {
      error = "Ship is out of boundaries. Try again.";
      i--;
      continue;
    }

    // placing
    if (orientation == 'v') {
      int j;
      for (j = b; j < (ships_size[i] + b); j++) {
        // checking overlap
        if (arr[j][a] == 'O') {
          error = "A ship is already there. Try again.";
          i--;
          break;
        }
      }
      if (j < (ships_size[i] + b)) {
        continue;
      }
      for (j = b; j < (ships_size[i] + b); j++) arr[j][a] = 'O';

    } else{
      int j;
      for (j = a; j < (ships_size[i] + a); j++) {
        if (arr[b][j] == 'O') {
          error = "A ship is already there. Try again.";
          i--;
          break;
        }
      }
      if (j < (ships_size[i] + a)) {
        continue;
      }
      for (j = a; j < (ships_size[i] + a); j++) arr[b][j] = 'O';
    } 
  }
}

void attack(char arr_ref[14][14], char arr_opp[14][14], int *turn) {
  while(*turn){
    printf("\033[1;1H\033[2J"); 
    rendering(arr_ref);
    char attack_coords[10];
    printf("Type X and Y co-ordinates of the attack with a space in between: \n");
    fgets(attack_coords, sizeof(attack_coords), stdin);
    int a, b;
    if(sscanf(attack_coords, "%d %d", &a, &b)!=2){
      printf("Give Correct Input \n");
      continue;
    }

    if (a < 0 || a >= 14 || b < 0 || b >= 14){
      printf("Invalid coordinates. Try again.\n"); 
      continue;
    }
    if(arr_opp[b][a] == 'x' ||arr_opp[b][a] == '+'){
      printf("Already attacked. Choose a different location \n");
      continue;
    }
    if (arr_opp[b][a] == 'O') {
      printf("Its a HIT!\n");
      arr_ref[b][a] = '+';
      arr_opp[b][a] = '+';
      
      int win = 1;
      for (int r = 0; r < 14; r++) {
        for (int c = 0; c < 14; c++) {
          if (arr_opp[r][c] == 'O') {
            win = 0;
            break;
          }
        }
        if (!win) break;
      }
      if (win) {
        *turn = 2;
        break;
      }
      sleep(1);
    } else {
      printf("Its a MISS!\n");
      arr_ref[b][a] = 'x';
      arr_opp[b][a] = 'x';
      *turn = 0;
      sleep(1);
    }
  }
}
