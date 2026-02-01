#include <stdio.h>
int main() {
  // creating and printing grid
  int arr[10][10] = {};
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      arr[i][j] = 0;
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%d", arr[i][j]);
    }
    printf("\n");
  }

  int a, b;
  scanf("%d", &a);
  scanf("%d", &b);
  return 0;
}
