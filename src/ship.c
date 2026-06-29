#include "../includes/ship.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
    int n = sscanf(place_coords, "%d %d %c", &a, &b, &orientation);

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
    if ((ships_size[i] + a - 1) > 13 || (ships_size[i] + b - 1) > 13) {
      error = "Ship is out of boundaries. Try again.";
      i--;
      continue;
    }

    // placing
    if (orientation == 'v') {
      for (int j = b; j < (ships_size[i] + b); j++) {
        // checking overlap
        if (arr[j][a] == 'O') {
          error = "A ship is already there. Try again.";
          i--;
          break;
        }
        arr[j][a] = 'O';
      }

    } else{
      for (int j = a; j < (ships_size[i] + a); j++) {
        if (arr[b][j] == 'O') {
          error = "A ship is already there. Try again.";
          i--;
          break;
        }
        arr[b][j] = 'O';
      }
    } 
  }
}

void attack(char arr_ref[14][14], int *turn) {
  while(*turn){
    printf("\033[1;1H\033[2J"); 
    rendering(arr_ref);
    char attack_coords[10];
    printf("Type X and Y co-ordinates of the attack with a space in between: \n");
    fgets(attack_coords, sizeof(attack_coords), stdin);
    int a, b;
    sscanf(attack_coords, "%d %d", &a, &b);

    if (a < 0 || a >= 14 || b < 0 || b >= 14) printf("Invalid coordinates. Try again.\n"); 
    if(arr_ref[b][a] == 'x' ||arr_ref[b][a] == '+') printf("Already attacked. Choose a different location \n");
    if (arr_ref[b][a] == 'O') {
      printf("Its a HIT!\n");
      arr_ref[b][a] = '+';
    } else {
      printf("Its as MISS!\n");
      arr_ref[b][a] = 'x';
      *turn =0;
    }
  }
}
