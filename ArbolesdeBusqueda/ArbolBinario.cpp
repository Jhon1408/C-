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

int TreeMinimum(struct node *x) {
  while (x->left != NULL) {
    x = x->left;
  }
}
