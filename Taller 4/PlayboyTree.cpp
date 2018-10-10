//Cambio pendejo para probar algo
//pues si wey no mames
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

struct nodeTree {
  unsigned long long key;
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

struct nodeTree *TreeSearch(struct nodeTree *x, unsigned long long k) {
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

struct nodeTree *TreeInsert(struct nodeTree *T, unsigned long long k) {
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
  unsigned long long ladys, chimp, cases;
  struct nodeTree *T;
  T = NULL;
  scanf("%llu", &ladys);
  for (int i = 1; i <= ladys; i++) {
    scanf("%llu", &chimp);
    T = TreeInsert(T, chimp);
  }
  scanf("%llu", &cases);
  for (int i = 1; i <= cases; i++) {
    unsigned long long small = 0, tall = 0, height;
    struct nodeTree *temp, *search;
    temp = NULL;
    search = NULL;
    scanf("%llu", &height);
    temp = TreeMinimum(T);
    while (temp != NULL && temp->key < height) {
      small = temp->key;
      temp = TreeSuccessor(temp);
    }
    temp = TreeMaximum(T);
    while (temp != NULL && temp->key > height) {
      tall = temp->key;
      temp = TreePredeccessor(temp);
    }
    if (small > 0)
      printf("%llu ", small);
    else
      printf("X ");

    if (tall > 0)
      printf("%llu\n", tall);
    else
      printf("X\n");
  }
  return 0;
}
