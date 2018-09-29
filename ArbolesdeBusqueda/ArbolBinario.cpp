//Cambio pendejo para probar algo
//pues si wey no mames
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

struct node {
  int key;
  struct node *Left;
  struct node *Right;
  struct node *p;
};

void InorderTreeWalk(struct node *x) {
  if(x != NULL) {
    InorderTreeWalk(x->Left);
    printf("%d\n", x->key);
    InorderTreeWalk(x->Right);
  }
}

struct node *TreeSearch(struct node *x, int k) {
  if ((x == NULL) || (k == x->key)) {
    return x;
  }
  if(k < x->key) {
    return TreeSearch(x->Left,k);
  } else {
    return TreeSearch(x->Right,k);
  }
}

struct node *TreeMinimum(struct node *x) {
  while (x->Left != NULL) {
    x = x->Left;
  }
  return x;
}

struct node *TreeMaximun(struct node *x) {
  while (x->Right != NULL) {
    x = x->Right;
  }
  return x;
}

struct node *TreeSuccessor(struct node *x) {
  if (x->Right != NULL) {
    return TreeMinimum(x->Right);
  }
  struct node *y;
  y = x->p;
  while ((y != NULL) && (x == y->Right)) {
    x = y;
    y = y->p;
  }
  return y;
}
