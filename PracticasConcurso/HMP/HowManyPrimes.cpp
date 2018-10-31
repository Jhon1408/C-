#include <stdlib.h>
#include <stdio.h>

bool isPrime(int n) {
  int i, cont = 2;
  bool value = true;
  if (n > 1) {
    for(i = 2; i < n; ++i) {
      if(n % i == 0) {
        cont++;
        break;
      }
    }
  } else {
    return false;
  }
  if (cont != 2) {
    return false;
  } else {
    return true;
  }
}

int main() {
  int A, B, n, cont;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    cont = 0;
    scanf("%d %d", &A, &B);
    for (int i = A; i <= B; i++) {
      if (isPrime(i)) {
        cont++;
      }
    }
    printf("Test Case #%d: %d\n", i, cont);
  }
  return 0;
}
