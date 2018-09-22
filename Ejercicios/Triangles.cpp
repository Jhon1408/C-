#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
  unsigned long long n, x, g;
  while(scanf("%llu", &n) && (n!=0)) {
    x = ((sqrt(1+(8*(double)n)))-1)/2;
    g = (x*(x+1))/2;
    if (g == n) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
  return 0;
}
