#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#define infinite 2147483647
int long inv = 0;

void Merge(long long int A[], int p, int q, int r) {
  int i, j, k;

  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1+1], R[n2+1];

  for (i = 1; i <= n1; i++)
    L[i] = A[p + i - 1];

  for (j = 1; j <= n2; j++)
    R[j] = A[q + j];

  L[n1+1] = infinite;
  R[n2+1] = infinite;
  i = 1;
  j = 1;

  for (k = p; k <= r; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
      inv = inv + n1 - i + 1;
    }
  }
}

void Merge_Sort(long long int A[], int p, int r) {
  if (p < r) {
    int q = floor((p+r)/2);
    Merge_Sort(A,p,q);
    Merge_Sort(A,q+1,r);
    Merge(A,p,q,r);
  }
}

int main() {
  int p = 1, r;
  while (scanf("%d", &r) != EOF && (r != 0)) {
    inv = 0;
    long long int A[r];
    for (int i = 1; i <= r; i++) {
        scanf("%lld", &A[i]);
    }
    Merge_Sort(A, p, r);
    printf("%ld\n",inv);
  }
  return 0;
}
