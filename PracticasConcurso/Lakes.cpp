#include <stdlib.h>
#include <stdio.h>

int main() {
  int Colums, Rows, sumerged, s1, s2;
  scanf("%d %d %d", &Rows, &Colums, &sumerged);
  int Rectangle[Rows][Colums];
  for (int i = 0; i < Rows; i++) {
    for (int j = 0; i < Colums; i++) {
      Rectangle[i][j] = 0;
    }
  }
  for (int i = 0; i < sumerged; i++) {
    scanf("%d %d", &s1, &s2);
    Rectangle[s1][s2] = 1;
  }
  for (int i = 0; i < Rows; i++) {
    for (int j = 0; i < Colums; i++) {
      if (Rectangle[i][j] == 1) {
        /* code */
      }
    }
  }
}
