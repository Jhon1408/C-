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
