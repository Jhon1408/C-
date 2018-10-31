#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

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
  /*if(result == -1) {
    result = (-1)*i-1;
  }*/
  return result;
}

int main(){
  int op;
  int i = 0, j, n;
  printf("Enter the size of the array.\n");
  cin >> j;
  int A[j];

  printf("Select Mode.\n1) Select values.\n2) Auto Complete.\n");
  cin >> op;
  switch (op) {
    case 1:
      printf("Enter the values of each position.\n");
      for (int k = 0; k < j; k++) {
        cin >> A[k];
      }
      break;
    case 2:
      printf("Filling the Array... plis weit.\n");
      for (int k = 0; k < j; k++) {
        A[k] = k;
      }
      break;
    default:
      printf("This case doesn't exist.\n");
      break;
  }
  printf("Enter the value to search.\n");
  scanf("%d", &n);
  int pos = BB(A,i,j,n);
  if(pos == -1) {
    printf("The number %d isn't in the array.\n", n);
  } else {
    printf("The number %d is in the position %d.\n",n ,pos+1);
  }

  return 0;
}
