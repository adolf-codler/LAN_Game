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
printf("ENTERED place()\n");
  // variables and misc.
  char *ships_name[6] = {"WarShip(6)", "BattleShip(5)", "Submarine(4)", "Ship(3)", "Boat(2)", "Boat(2)"};
  int ships_size[6] = {6, 5, 4, 3, 2, 2};
  printf("Type X, Y co-ordinates and orientation for all the ships with a space in between: \n");
  char *error="";
  for (int i = 0; i < 6; i++) {
printf("loop i = %d\n", i);
    if(error[0]!='\0') printf("%s \n",error);
    error = "";
    rendering(arr);

    // getting placement
    char place_coords[128];
if (fgets(place_coords, sizeof(place_coords), stdin) == NULL) {
    perror("fgets");
    printf("EOF = %d, ERR = %d\n", feof(stdin), ferror(stdin));
    exit(1);
}

printf("Got: '%s'\n", place_coords);
    int a, b;
    char orientation;
int n = sscanf(place_coords, "%d %d %c", &a, &b, &orientation);
printf("n=%d a=%d b=%d orientation=%c\n", n, a, b, orientation);

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

void attack(char arr_ref[14][14], char* coords) {
  int a, b;
  sscanf(coords, "%d %d", &a, &b);

  if (a < 0 || a >= 14 || b < 0 || b >= 14) {
    printf("Invalid coordinates. Try again.\n");
    return;
  }
  if (b+a == 'O') {
    printf("Its a HIT!\n");
    arr_ref[b][a] = '+';
  } else {
    printf("Its as MISS!\n");
    arr_ref[b][a] = 'x';
  }
}
