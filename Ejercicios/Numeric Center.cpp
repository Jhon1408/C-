#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int BB(int A[], int i, int j, int n) {
  int m;
    if(i > j) {
      return -1;
    } else {
      m = floor(i + j)/2;
      if (A[m] == n) {
        return m;
      } else if (n > A[m]) {
          BB(A, m+1, j, n);
      } else {
          BB(A, i, m-1, n);
      }
    }
}

int getCenter(int n, int A[]) {
  int r = 0;
  if(n < 8) {
    return r;
  } else {

    }
}


int main() {
  int n, r, A[100001];
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    A[i] = i;
  }
  r = getCenter(n, A);
  printf("%d\n", r);
  return 0;
}
