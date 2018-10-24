#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define infinite 2147483647

void Merge(int A[], int p, int q, int r) {
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
    }
  }
}

void Merge_Sort(int A[], int p, int r) {
  if (p < r) {
    int q = floor((p+r)/2);
    Merge_Sort(A,p,q);
    Merge_Sort(A,q+1,r);
    Merge(A,p,q,r);
  }
}

int BB(int A[], int i, int j, int n) {
  int m, result = -1;
  while(i <= j){
    m =(i+j) >> 1;
    if (A[m]==n) {
      result = m;
      break;
    } else {
      if(n>A[m]) {
        i=m+1;
      } else {
        j=m-1;
      }
    }
  }
  //Modificacion para retornar el valor inverso.
  if(result == -1) {
    result = (-1)*i-1;
  }
  return result;
}

int main () {
  int size;
  printf("Write the size of the string: ");
  scanf("%d", &size);
  char text[size];
  int Q[size];
  printf("Write the string: ");
  scanf("%s", text);
  for(int i = 0; i < size; i++) {
    if(BB(Q,0,i,int(text[i])) < 0) {
      Q[i] = int(text[i]);
      printf("%s ", text[i]);
      Merge_Sort(Q,0,i);
    } else {
      printf("First recurrency: %s\n", text[i]);
      break;
    }
  }
    return 0;
}