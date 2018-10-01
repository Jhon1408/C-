#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
  unsigned long long n, x, g;
  while(scanf("%llu", &n) && (n!=0)) {
    x = ((sqrt(1+(8*(double)n)))-1)/2;
    g = (x*(x+1))/2;
    if (g == n) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}
