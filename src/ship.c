#include "../includes/ship.h"
#include <stdio.h>

void rendering(char arr[14][14]) {
  // printf("\033[1;1H\033[2J");//clears the terminal screen
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
  char *arrc[7] = {"WarShip(6)", "BattleShip(5)", "Ship(3)", "Ship(3)",
                   "Ship(3)",    "Boat(2)",       "Boat(2)"};
  int arri[7] = {6, 5, 3, 3, 3, 2, 2};
  for (int i = 0; i < 2; i++) {
    rendering(arr);

    // getting placement
    int a, b;
    char ori;
    printf("starting cordinates of %s (closer to origin)\n", arrc[i]);
    printf("X cordinates :");
    scanf("%d", &a);
    printf("Y cordinates :");
    scanf("%d", &b);
    if (a < 0 || a >= 14 || b < 0 || b >= 14) {
      printf("Invalid coordinate. Try again.\n");
      i--; // repeat this ship
      continue;
    }
    printf("Orientation of the %s ('h' for horizontal or 'v' for vertical) :\n",
           arrc[i]);
    scanf(" %c", &ori);

    // checking boundaries
    if ((arri[i] + a - 1) > 13 || (arri[i] + b - 1) > 13) {
      printf("Ship is out of boundaries. Try again.\n");
      i--;
      continue;
    }

    // placing
    if (ori == 'v') {
      for (int j = b; j < (arri[i] + b); j++) {
        // checking overlap
        if (arr[j][a] == 'O') {
          printf("A ship is already there. Try again. \n");
          i--;
          break;
        }
        arr[j][a] = 'O';
      }

    } else if (ori == 'h') {
      for (int j = a; j < (arri[i] + a); j++) {
        if (arr[b][j] == 'O') {
          printf("A ship is already there. Try again. \n");
          i--;
          break;
        }
        arr[b][j] = 'O';
      }

    } else {
      printf("Invalid orientation. Try again.\n");
      i--;
      continue;
    }
  }
}

void attack(char arr_ref[14][14], char arr_opp[14][14]) {
  int a, b;
  printf("X cordinates of attack:");
  scanf("%d", &a);
  printf("Y cordinates of attack:");
  scanf("%d", &b);
  if (a < 0 || a >= 14 || b < 0 || b >= 14) {
    printf("Invalid coordinates. Try again.\n");
    return;
  }
  if (arr_opp[b][a] == 'O') {
    printf("Its a HIT!\n");
    arr_ref[b][a] = '+';
  } else {
    printf("Its as MISS!\n");
    arr_ref[b][a] = 'x';
  }
}
