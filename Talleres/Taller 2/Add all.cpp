#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define infinite 2147483647;
int heapSize = 0;

int Parent(int i) {
  return (int) floor(i/2);
}
int Left(int i) {
    return (2 * i);
}
int Right(int i) {
  return ((2 * i) + 1);
}
void MinHeapify(int Q[], int i) {
  int l = Left(i);
  int r = Right(i);
  int least;

  if ((l <= heapSize) && (Q[l] < Q[i])) {
    least = l;
  } else {
    least = i;
  }

  if ((r <= heapSize) && (Q[r] < Q[least])) {
    least = r;
  }

  if (least != i) {
    int temp = Q[i];
    Q[i] = Q[least];
    Q[least] = temp;
    MinHeapify(Q, least);
  }
}

int MinPQ_Minimum(int Q[]) {
  return Q[1];
}

int MinPQ_Extract(int Q[]) {
  int min = 0;
  if(heapSize < 1) {
    printf("Error (Heap underflow!)\n");
  } else {
    min = Q[1];
    Q[1] = Q[heapSize];
    heapSize = heapSize - 1;
    MinHeapify(Q, 1);
  }
  return min;
}

void MinPQ_DecreaseKey(int Q[], int i, int key) {
  if (key > Q[i]) {
    printf("Error (New key is higher than current key)");
  } else {
    Q[i] = key;
    int temp;
    while ((i > 1) && (Q[Parent(i)] > Q[i])) {
      temp = Q[i];
      Q[i] = Q[Parent(i)];
      Q[Parent(i)] = temp;
      i = Parent(i);
    }
  }
}

void MinPQ_Insert(int Q[], int key) {
  heapSize = heapSize + 1;
  Q[heapSize] = infinite;
  MinPQ_DecreaseKey(Q, heapSize, key);
}

int main() {
  int numero;
  //Ciclo de vida del programa.
  while (scanf("%d", &numero) && numero != 0) {
    int elemento, suma = 0, n1 = 0, n2 = 0, Q[100001];
    heapSize = 0;
    //Insertamos los numeros hasta n en la cola.
    for (int i = 1; i <= numero; i++) {
      scanf("%d", &elemento);
      MinPQ_Insert(Q, elemento);
    }
    //Ciclo para cada ejemplo.
    while (heapSize >= 2) {
      //Extraemos los dos mas pequeños.
      n1 = MinPQ_Extract(Q);
      n2 = MinPQ_Extract(Q);
      //Mantenemos la suma de cada "Operacion".
      suma = suma + (n1 + n2);
      //Insertamos el numero nuevo.
      MinPQ_Insert(Q, (n1 + n2));
    }
    //Imprimimos la suma.
    printf("%d\n", suma);
  }
  return 0;
}
