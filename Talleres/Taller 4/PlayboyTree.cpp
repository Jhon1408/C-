//Cambio pendejo para probar algo
//pues si wey no mames
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

struct nodeTree {
  int key;
  struct nodeTree *Left;
  struct nodeTree *Right;
  struct nodeTree *p;
};

void InorderTreeWalk(struct nodeTree *x) {
  if(x != NULL) {
    InorderTreeWalk(x->Left);
    printf("[%d] ", x->key);
    InorderTreeWalk(x->Right);
  }
}

struct nodeTree *TreeSearch(struct nodeTree *x, int k) {
  if ((x == NULL) || (k == x->key)) {
    return x;
  }
  if(k < x->key) {
    return TreeSearch(x->Left,k);
  } else {
    return TreeSearch(x->Right,k);
  }
}

struct nodeTree *TreeMinimum(struct nodeTree *x) {
  while (x->Left != NULL) {
    x = x->Left;
  }
  return x;
}

struct nodeTree *TreeMaximum(struct nodeTree *x) {
  while (x->Right != NULL) {
    x = x->Right;
  }
  return x;
}

struct nodeTree *TreeSuccessor(struct nodeTree *x) {
  if (x->Right != NULL) {
    return TreeMinimum(x->Right);
  }
  struct nodeTree *y;
  y = x->p;
  while ((y != NULL) && (x == y->Right)) {
    x = y;
    y = y->p;
  }
  return y;
}

struct nodeTree *TreePredeccessor(struct nodeTree *x) {
  if (x->Left != NULL) {
    return TreeMinimum(x->Left);
  }
  struct nodeTree *y;
  y = x->p;
  while ((y != NULL) && (x == y->Left)) {
    x = y;
    y = y->p;
  }
  return y;
}

struct nodeTree *TreeInsert(struct nodeTree *T, int k) {
  struct nodeTree *x, *y, *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  z->key = k;
  z->Left = NULL;
  z->Right = NULL;
  y = NULL;
  x = T;

  while (x != NULL) {
    y = x;
    if (z->key < x->key) {
      x = x->Left;
    } else {
      x = x->Right;
    }
  }
  z->p = y;

  if (y == NULL) {
    T = z;
  } else {
    if (z->key < y->key) {
      y->Left = z;
    } else {
      y->Right = z;
    }
  }
  return T;
}

struct nodeTree *TreeDelete(struct nodeTree *T, struct nodeTree *z) {
  struct nodeTree *x, *y;
  if ((z->Left == NULL) || (z->Right == NULL)) {
    y = z;
  } else {
    y = TreeSuccessor(z);
  }

  if (y->Left != NULL) {
    x = y->Left;
  } else {
    x = y->Right;
  }

  if (x != NULL) {
    x->p = y->p;
  }
  if (y->p == NULL) {
    T = x;
  } else {
    if (y == y->p->Left) {
      y->p->Left = x;
    } else {
      y->p->Right = x;
    }
  }
  if (y != z) {
    z->key = y->key;
    //Campos de informacion.
  }
  free(y);
  return T;
}

int main() {
  int ladys, chimp, cases, height;
  struct nodeTree *T, *z, *succ, *pred;
  T = NULL;
  scanf("%d", &ladys);
  for (int i = 1; i <= ladys; i++) {
    scanf("%d", &chimp);
    z = TreeSearch(T, chimp);
    if(z == NULL)
        T = TreeInsert(T, chimp);
  }
  scanf("%d", &cases);
  for (int i = 1; i <= cases; i++) {
    scanf("%d", &height);
    z = TreeSearch(T, height);
    if (z != NULL) {
      pred = TreePredeccessor(z);
      succ = TreeSuccessor(z);
      if (pred == NULL) {
        if (succ == NULL)
          printf("X X\n");
        else
          printf("X %d\n", succ->key);
      } else {
        if (succ == NULL)
          printf("%d X\n", pred->key);
        else
          printf("%d %d\n", pred->key, succ->key);
      }
    } else {
      T = TreeInsert(T, height);
      z = TreeSearch(T, height);
      pred = TreePredeccessor(z);
      succ = TreeSuccessor(z);
      if (pred == NULL) {
        if (succ == NULL)
          printf("X X\n");
        else
          printf("X %d\n", succ->key);
      } else {
        if (succ == NULL)
          printf("%d X\n", pred->key);
        else
          printf("%d %d\n", pred->key, succ->key);
      }
      T = TreeDelete(T, z);
    }
  }
  return 0;
}
