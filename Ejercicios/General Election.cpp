#include <stdio.h>
#include <iostream>
using namespace std;
/*-------------- Variables primarias ---------------//
t = veces que se ejecuta.
c = candidatos.
r = regiones.
v[][] = votos en una matris n*n.
winners[] = guarda los result.
//------------ Variables secundarias ---------------//
result = suma de columnas.
max = mas votos.
winner = ganador por ronda.
//--------------------------------------------------*/
int main() {
  int t, c, r, v[101][101];
  int  winners[t];
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    scanf("%d" "%d",&c,&r);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        scanf("%d", &v[i][j]);
      }
    }
    int result, max = -1, winner = -1;
    for(int i = 0; i < c; i++) {
      result = 0;
      for(int j = 0; j < r; j++){
        result = v[j][i] + result;
      }
      if(result > max) {
        max = result;
        winner = i+1;
      }    
    }
    printf("%d\n", winner);
  }
  return 0;
}
