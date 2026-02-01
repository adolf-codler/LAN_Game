#ifndef stdship // if not define
#define stdship // define
// all the declaration goes here

void rendering(char arr[14][14]);
void place(char arr[14][14]);
void attack(char arr[14][14], char arr1[14][14]);

typedef struct {
  int x;
  int y;
} cord;
typedef struct {
  cord start;
  cord end;
} ship;

#endif // ending if not define
