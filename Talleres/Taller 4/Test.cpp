#include "stdlib.h"
#include "stdio.h"
#include "math.h"

struct nodeTree {
  unsigned long long key;
  unsigned long long times = 0;
  unsigned long long value;
  struct nodeTree *Left;
  struct nodeTree *Right;
  struct nodeTree *p;
};

void InorderTreeWalk(struct nodeTree *x) {
  if(x != NULL) {
    InorderTreeWalk(x->Left);
    printf("%llu %llu\n", x->value, x->times);
    InorderTreeWalk(x->Right);
  }
}

struct nodeTree *TreeSearch(struct nodeTree *x, unsigned long long k) {
  if ((x == NULL) || (k == x->value)) {
    return x;
  }
  if(k < x->value) {
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

struct nodeTree *TreeInsert(struct nodeTree *T, unsigned long long k, unsigned long long val) {
  struct nodeTree *x, *y, *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  z->key = k;
  z->value = val;
  z->times = 1;
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
    z->times = y->times;
    z->value = y->value;
    //Campos de informacion.
  }
  free(y);
  return T;
}

int main() {
    struct nodeTree *T;
    T = NULL;
    T = TreeInsert(T, -1, 20);
    if(TreeSearch(T, 20) != NULL) {
        printf("Encontre el valor 20.\n"); 
    } else {
        printf("NO encontre el valor 20.\n");
    }
    T = TreeInsert(T, -2, 15);
    if(TreeSearch(T, 15) != NULL) {
        printf("Encontre el valor 15.\n"); 
    } else {
        printf("NO encontre el valor 15.\n");
    }
    return 0;
}
