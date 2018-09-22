#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Funcion malloc();
La funcion malloc se utiliza para asignar a un
apuntador una localización de memoria.
La asignacion de memoria es dinamica.

Ejemplo:
char *p;
int n = 10;
p = (char *) malloc(n);

En la variable p esta almacenada una direccion que
apunta a un bloque de 10 bytes.
*/

/*
int main() {
  char *p;
  int n = 10;
  p = (char *) malloc(n);
  strcpy(p, "sencillo");
  printf("%s\n", p);
  return 0;
}*

/*
Ejemplo:
Almacenar el numero entero [821] en una localización asignada
por la funcion malloc();
*/

/*
int main() {
  int *p;
  p = (int *) malloc(sizeof(int));
  *p = 821;
  printf("%d\n", *p);
  return 0;
}
*/
//Estructuta con 4 valores disponibles.
/*
typedef struct R {
  int a;
  float b;
  double c;
  char *p;
} estructura;

int main() {
  int n = 10;
  estructura *q;
  q = (estructura *) malloc(sizeof(estructura));
  q -> a = 8;
  q -> b = 10.31;
  q -> c = 10.32;
  q -> p = (char *) malloc(n);
  strcpy(q -> p, "CADENA");
  printf("%d %.2f %.2lf %s\n", q -> a, q -> b, q -> c, q -> p);
  return 0;
}
*/

/*Funcion free();
¿Se da un buen manejo a la memoria en el siguiente ejemplo?
*p = x;
free(p); Libera el contenido de p.
*/
 /*
int main() {
  char *p, *q;
  int n = 50;
  p = (char *) malloc(n);
  strcpy(p, "Pascal");
  q = (char *) malloc(n);
  strcpy(q, "Lenguaje C");
  printf("%s %s\n", p, q);
  free(q);
  q = p;
  printf("%s %s\n", p, q);

  return 0;
}
*/

/*
p -> [P|a|s|c|a|l|\0]
q -> [L|e|n|g|u|a|j|e| |C|\0]

Queda un bloque de memoria ocupado
que no se puede volver a utilizar.
liberar el bloque de memoria con la
intruccion: free(q);
*/

/*
Concepto d lista:
Una lista es un conjunto de variables
encadenadas entre si a travez de un apuntador.
Cada variable se denomina un nodo.
Un nodo es una variable conpuesta por dos partes;
La informacion y un apuntador a la proxima variable.

[dato del nodo][apuntador al proximo nodo]

struct node {
  int key;
  struct node *next;
};

Creacion de una lista:
Ejemplo de creacion de una lista con
los elementos 1, 2 y 3.
*/

/*
struct node {
  int key;
  struct node *next;
};

int main() {
  struct node *head, *q;
  head = (struct node *) malloc(sizeof(struct node));
  head -> key = 1;
  q = (struct node *) malloc(sizeof(struct node));
  q -> key = 2;
  head -> next = q;
  q -> next = (struct node *) malloc(sizeof(struct node));
  q -> next -> key = 3;
  q -> next -> next = NULL;
  printf("%d %d %d\n", head -> key, head -> next -> key, head -> next -> next -> key);
  return 0;
}
*/

struct node {
  int key;
  struct node *next;
};

int main() {
  struct node *head, *q;
  for (int i = 1; i <= 1000; i++) {
    head = (struct node *) malloc(sizeof(struct node));
    head -> key = i;
    q = (struct node *) malloc(sizeof(struct node));
    q -> key = i+1;
    head -> next = q;
  }
  q -> next -> next = NULL;
  return 0;
}
