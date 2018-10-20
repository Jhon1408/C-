#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

struct nodeTree {
  int money;
  char key[20];
  struct nodeTree *Left;
  struct nodeTree *Right;
  struct nodeTree *p;
};

void InorderTreeWalk(struct nodeTree *x) {
  if(x != NULL) {
    InorderTreeWalk(x->Left);
    printf("[%s]: %d\n", x->key, x->money);
    InorderTreeWalk(x->Right);
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

struct nodeTree *TreeSearch(struct nodeTree *x, char k[]) {
  if ((x == NULL) || (strcmp(k, x->key) == 0)) {
    return x;
  }
  if(strcmp(k,x->key) < 0)  {
    return TreeSearch(x->Left,k);
  } else {
    return TreeSearch(x->Right,k);
  }
}

struct nodeTree *TreeInsert(struct nodeTree *T, char k[], int val) {
  struct nodeTree *x, *y, *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  strcpy(z->key, k);
  z->money = val;
  z->Left = NULL;
  z->Right = NULL;
  y = NULL;
  x = T;

  while (x != NULL) {
    y = x;
    if (strcmp(z->key,x->key) < 0) {
      x = x->Left;
    } else {
      x = x->Right;
    }
  }
  z->p = y;

  if (y == NULL) {
    T = z;
  } else {
    if (strcmp(z->key, y->key) < 0) {
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
    strcpy(y->key, z->key);
    z->money = z->money;
    //Campos de informacion.
  }
  free(y);
  return T;
}

int main() {
    struct nodeTree *T, *node;
    T = NULL;
    node = NULL;
    char key[20], temp[20];
    int list, parragraphs, money, totalmoney;
    scanf("%d %d", &list, &parragraphs);
    for(int i = 1; i <= list; i++) {
      scanf("%s %d", key, &money);
      T = TreeInsert(T,key,money);
    }
    for(int i = 1; i <= parragraphs; i++) {
      totalmoney = 0;
      while((scanf("%s", &temp)) && (strcmp(temp,".") != 0)) {
        node = TreeSearch(T,temp);
        if(node != NULL) {
          totalmoney = totalmoney + node->money;
        }
      }
      printf("%d\n", totalmoney);
    }
    return 0;
}
