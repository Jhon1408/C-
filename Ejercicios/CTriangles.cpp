#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Busqueda binaria por modo While.
//Modificacion para lograr que no gaste mas tiempo.
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
  if(result == -1) {
    result = (-1)*i-1;
  }
  return result;
}

//Calcular la cantidad de triangulos.
int triangles(int p, int d[]) {
  int r = 0;
  int max = d[p-1];
  if (max % 3 == 0) {
    int l = max/3;

    // Definir los "Lados" del triangulo //
    int inicio1 = BB(d, 0, p-1, l);
    int fin1 = BB(d, 0, p-1, l*2);

    if (inicio1 > 0) inicio1 += 1;
    else inicio1 = abs(inicio1) - 1;
    if (fin1 < 0) fin1 = abs(fin1) - 2;

    int inicio2 = fin1 + 1;
    int fin2 = abs(BB(d, 0, p-1, l*3));
    //------------------------------------//

    //Preguntar si en los puntos esta el valor que central que buscamos.
    for (int i=0; i<inicio1; i++){
      if((BB(d, inicio1, fin1, d[i]+l) > 0) && (BB(d, inicio2, fin2, d[i]+(l*2)) > 0)) {
        r++;
      }
    }
  }
  return r;
}

int main() {
  int p, d[100001], temp;
  while(scanf("%d", &p) != EOF) {
    for (int i = 0; i < p; i++) {
      scanf("%d", &temp);
      if(i == 0) {
        d[i] = temp;
      } else {
        d[i] = d[i-1] + temp;
      }
    }
    printf("%d\n", triangles(p, d));
  }
  return 0;
}
