#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"

struct nodeTree {
  int money;
  char name[20];
  struct nodeTree *Left;
  struct nodeTree *Right;
  struct nodeTree *p;
};

void InorderTreeWalk(struct nodeTree *x) {
  if(x != NULL) {
    InorderTreeWalk(x->Left);
    printf("[%s]: %d\n", x->name, x->money);
    InorderTreeWalk(x->Right);
  }
}

struct nodeTree *TreeSearch(struct nodeTree *x, char k[]) {
  if(x != NULL) {
    if (strcmp(k,x->name) == 0) {
      return x;
    }
    TreeSearch(x->Left,k);
    TreeSearch(x->Right,k);
  } else {
    return x;
  }
}

struct nodeTree *TreeMinimum(struct nodeTree *x) {
  while (x->Left != NULL) {
    x = x->Left;
  }
  return x;
}

struct nodeTree *TreeMaximun(struct nodeTree *x) {
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

struct nodeTree *TreeInsert(struct nodeTree *T, char k[], int val) {
  struct nodeTree *x, *y, *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  strcpy(z->name, k);
  z->money = val;
  z->Left = NULL;
  z->Right = NULL;
  y = NULL;
  x = T;

  while (x != NULL) {
    y = x;
    if (z->money < x->money) {
      x = x->Left;
    } else {
      x = x->Right;
    }
  }
  z->p = y;

  if (y == NULL) {
    T = z;
  } else {
    if (z->money < y->money) {
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
    strcpy(y->name, z->name);
    z->money = z->money;
    //Campos de informacion.
  }
  free(y);
  return T;
}

int main() {
    struct nodeTree *T, *node;
    T = NULL;
    temp = NULL;
    char name[20], temp[20];
    int list, parragraphs, money, totalmoney;
    scanf("%d %d", &list, &parragraphs);
    for(int i = 1; i <= list; i++) {
      scanf("%s %d", name, money);
      T = TreeInsert(T,name,money);
    }
    for(int i = 1; i <= parragraphs; i++) {
      totalmoney = 0;
      while(scanf("%s", &temp) != '\n.') {
        node = TreeSearch(T,temp);
        if(node != NULL) {
          totalmoney = totalmoney + node->money;
        }
      }
      printf("%d\n", totalmoney);
    }
    return 0;
}
