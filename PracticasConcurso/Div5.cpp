#include <stdlib.h>
#include <stdio.h>

int main() {
  int n;
  int value;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &value);
    if (value % 5 == 0) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}
