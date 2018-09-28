#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define infinite 2147483647

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
  return result;
}

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

int main() {
  //Tamaño del hueco.
  int x;
  while(scanf("%d", &x) != EOF) {
    int result = 0, n;
    //Pasarlo a nanometros
    x = x * 10000000;
    //Cantidad de piezas del array.
    scanf("%d", &n);
    //Rellenar el vector
    int L[n];
    for (int temp = 0, i = 1; i <= n; i++) {
      scanf("%d", &temp);
      L[i] = temp;
    }
    int n1 = 0, n2 = 0;
    //Ordenarlo para la busqueda binaria.
    Merge_Sort(L, 1, n);
    //Busqueda de los numeros
    for (int i = 1; i < n; i++) {
      if ((BB(L,i+1,n,x-L[i]) != -1)) {
        n1 = L[i];
        n2 = x-L[i];
        result = 1;
        break;
      }
    }
    //Imprimir resultado
    if (result == 0) {
      printf("danger\n");
    } else {
      printf("%s %d %d\n", "yes", n1, n2);
    }
  }
  return 0;
}
