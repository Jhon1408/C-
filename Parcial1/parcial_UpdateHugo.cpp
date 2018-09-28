#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define infinite 2147483647;
int heapSize = 0;

struct prioridad {
  int tllegada;
  int Prioridad;
  char nombre[20];
};

int Parent(int i) {
  return (int) floor(i/2);
}

int Left(int i) {
    return (2 * i);
}

int Right(int i) {
  return ((2 * i) + 1);
}

void MinHeapify(struct prioridad Q[], int i) {
  int l = Left(i);
  int r = Right(i);
  int least;

  if ((l <= heapSize) && (Q[l].Prioridad < Q[i].Prioridad)) {
    least = l;
  } else {
    if (((l <= heapSize) && (Q[l].Prioridad == Q[i].Prioridad))) {
      if (Q[l].tllegada < Q[i].tllegada) {
        least = l;
      } else {
        least = i;
      }
    } else {
      least = i;
    }
  }

  if ((r <= heapSize) && (Q[r].Prioridad < Q[least].Prioridad)) {
    least = r;
  }

  if (least != i) {
    struct prioridad temp = Q[i];
    Q[i] = Q[least];
    Q[least] = temp;
    MinHeapify(Q, least);
  }
}

struct prioridad MinPQ_Minimum(struct prioridad Q[]) {
  return Q[1];
}

struct prioridad MinPQ_Extract(struct prioridad Q[]) {
  struct prioridad min;
  min.Prioridad = 0;
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

void MinPQ_DecreaseKey(struct prioridad Q[], int i, struct prioridad key) {
  if (key.Prioridad > Q[i].Prioridad) {
    printf("Error (New key is higher than current key)");
  } else {
    Q[i] = key;
    struct prioridad temp;
    while ((i > 1) && (Q[Parent(i)].Prioridad > Q[i].Prioridad)) {
      temp = Q[i];
      Q[i] = Q[Parent(i)];
      Q[Parent(i)] = temp;
      i = Parent(i);
    }
  }
}

void MInPQ_Insert(struct prioridad Q[], struct prioridad key) {
  heapSize = heapSize + 1;
  struct prioridad p;
  p.Prioridad = infinite;
  Q[heapSize] = p;
  MinPQ_DecreaseKey(Q, heapSize, key);
}

int main() {
  //Declarar las variables.
  int n, t, tpaciente, priority, tdoctor;
  char nombreScan[20];
  //Declara estructuras temporales de insercion.
  struct prioridad p, q;
  //Ciclo de vida del programa.
  while (scanf("%d", &n) != EOF) {
    //array para contener las estructuras con 5 extra pos si acaso.
    struct prioridad Q[n+5];
    heapSize = 0;
    //Ciclo de escaneo de los 10 test.
    for (int i = 0; i < n; i++) {
      //escanear tipo (1 o 2).
      scanf("%d", &t);
      if (t == 1) {
        //Tipo 1.
        //Recive todos los datos del paciente.
        scanf("%d %d %s", &tpaciente, &priority, nombreScan);
        //Los guarda en la estructura.
        p.tllegada = tpaciente;
        p.Prioridad = priority;
        strcpy(p.nombre, nombreScan);
        //Los inserta en la fila.
        MInPQ_Insert(Q, p);
      }
      else {
        if(t == 2) {
          //Tipo 2.
          //Escanea el tiempo del doctor.
          scanf("%d", &tdoctor);
          //Saca de la estructura el minimo y lo guarda en un temporal.
          q = MinPQ_Extract(Q);
          int a = q.tllegada;
          int result = tdoctor - a;
          printf("%d %d %d %s\n", a, tdoctor, result, q.nombre);
        }
      }
    }
  }
  return 0;
}
