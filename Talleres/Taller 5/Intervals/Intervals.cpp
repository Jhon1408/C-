#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define RED 1
#define BLACK 0
#define NIL 2147483647

//-----------------------------------------------------------------------------//
struct nodeTree {
  int key;
  int color;
  int freq;
  struct nodeTree *Left;
  struct nodeTree *Right;
  struct nodeTree *p;
};
//-----------------------------------------------------------------------------//
struct nodeTree *AssignNIL() {
  struct nodeTree *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  z->key = NIL;
  z->color = BLACK;
  z->p = NULL;
  z->Left = NULL;
  z->Right = NULL;
  return z;
}
//-----------------------------------------------------------------------------//
void RBInorderTreeWalk(struct nodeTree *x) {
  if(x->key != NIL) {
    RBInorderTreeWalk(x->Left);
    if(x->color == RED)
      printf("[%d|R] ", x->key);
    else
      printf("[%d|B] ", x->key);
    RBInorderTreeWalk(x->Right);
  }
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeSearch(struct nodeTree *x, int k) {
  if ((x->key == NIL) || (k == x->key)) {
    return x;
  }
  if(k < x->key) {
    return RBTreeSearch(x->Left,k);
  } else {
    return RBTreeSearch(x->Right,k);
  }
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeLeftRotate(struct nodeTree *T, struct nodeTree *x) {
  struct nodeTree *y;
  y = x->Right;
  x->Right = y->Left;
  if(y->Left->key != NIL) {
    y->Left->p = x;
  }
  y->p = x->p;
  if(x->p->key == NIL) {
    T = y;
  } else {
    if(x == x->p->Left) {
      x->p->Left = y;
    } else {
      x->p->Right = y;
    }
  }
  y->Left = x;
  x->p = y;
  return T;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeRightRotate(struct nodeTree *T, struct nodeTree *x) {
  struct nodeTree *y;
  y = x->Left;
  x->Left = y->Right;
  if(y->Right->key != NIL) {
    y->Right->p = x;
  }
  y->p = x->p;
  if(x->p->key == NIL) {
    T = y;
  } else {
    if(x == x->p->Right) {
      x->p->Right = y;
    } else {
      x->p->Left = y;
    }
  }
  y->Right = x;
  x->p = y;
  return T;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeMinimum(struct nodeTree *x) {
  while (x->Left->key != NIL) {
    x = x->Left;
  }
  return x;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeMaximum(struct nodeTree *x) {
  while (x->Right->key != NIL) {
    x = x->Right;
  }
  return x;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeSuccessor(struct nodeTree *x) {
  if (x->Right->key != NIL) {
    return RBTreeMinimum(x->Right);
  }
  struct nodeTree *y;
  y = x->p;
  while ((y->key != NIL) && (x == y->Right)) {
    x = y;
    y = y->p;
  }
  return y;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreePredecessor(struct nodeTree *x) {
  if (x->Left->key != NIL) {
    return RBTreeMaximum(x->Left);
  }
  struct nodeTree *y;
  y = x->p;
  while ((y->key != NIL) && (x == y->Left)) {
    x = y;
    y = y->p;
  }
  return y;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeInsertFIXUP(struct nodeTree *T, struct nodeTree *z) {
  struct nodeTree *y;
  while(z->p->color == RED) {
    if(z->p == z->p->p->Left) {
      y = z->p->p->Right;
      if(y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if(z == z->p->Right) {
          z = z->p;
          T = RBTreeLeftRotate(T, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        T = RBTreeRightRotate(T, z->p->p);
      }
    } else {
      y = z->p->p->Left;
      if(y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if(z == z->p->Left) {
          z = z->p;
          T = RBTreeRightRotate(T, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        T = RBTreeLeftRotate(T, z->p->p);
      }
    }
  }
  T->color = BLACK;
  return T;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeInsert(struct nodeTree *T, int element) {
	struct nodeTree *x, *y, *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  z->key = element;
  z->color = RED;
  z->Left = AssignNIL();
  z->Left->p = z;
  z->Right = AssignNIL();
  z->Right->p = z;
  z->freq = 1;
  if(T->key != NIL) {
    y = T->p;
  } else {
    y = T;
  }
	x = T;
	while(x->key != NIL) {
		y = x;
		if(z->key < x->key) {
			x = x->Left;
    } else {
			x = x->Right;
    }
	}
	z->p = y;
	if(y->key == NIL) {
		T = z;
	} else {
    free(x);
		if(z->key < y->key) {
			y->Left = z;
		} else {
			y->Right = z;
		}
	}
	return RBTreeInsertFIXUP(T, z);
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBDeleteFIXUP(struct nodeTree *T, struct nodeTree *x) {
  struct nodeTree *w;
  while ((x != T) && (x->color == BLACK)) {
    if (x == x->p->Left) {
      w = x->p->Right;
      if (w->color == RED) {
        w->color = BLACK;
        x->p->color = RED;
        T = RBTreeLeftRotate(T, x->p);
        w = x->p->Right;
      }
      if ((w->Left->color == BLACK) && (w->Right->color == BLACK)) {
        w->color = RED;
        x = x->p;
      } else {
        if (w->Right->color == BLACK) {
          w->Left->color = BLACK;
          w->color = RED;
          T = RBTreeRightRotate(T, w);
          w = x->p->Right;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->Right->color = BLACK;
        T = RBTreeLeftRotate(T, x->p);
        x = T;
      }
    } else {
      w = x->p->Left;
      if (w->color == RED) {
        w->color = BLACK;
        x->p->color = RED;
        T = RBTreeRightRotate(T, x->p);
        w = x->p->Left;
      }
      if ((w->Left->color == BLACK) && (w->Right->color == BLACK)) {
        w->color = RED;
        x = x->p;
      } else {
        if (w->Left->color == BLACK) {
          w->Right->color = BLACK;
          w->color = RED;
          T = RBTreeLeftRotate(T, w);
          w = x->p->Left;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->Left->color = BLACK;
        T = RBTreeRightRotate(T, x->p);
        x = T;
      }
    }
  }
  x->color = BLACK;
  return T;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeDelete(struct nodeTree *T, struct nodeTree *z) {
	struct nodeTree *x, *y;
	if((z->Left->key == NIL) || (z->Right->key == NIL)) {
		y = z;
	} else {
		y = RBTreeSuccessor(z);
  }
	if(y->Left->key != NIL) {
		x = y->Left;
	} else {
		x = y->Right;
  }
	x->p = y->p;
	if(y->p->key == NIL) {
		T = x;
	} else {
		if(y == y->p->Left) {
			y->p->Left = x;
		} else {
			y->p->Right = x;
    }
	}

	if(y != z) {
		z->key = y->key;
    z->freq = y->freq;
  }

	if(y->color == BLACK) {
		T = RBDeleteFIXUP(T, x);
  }

	if(y->Left->p == y) {
		free(y->Left);
  }

	if(y->Right->p == y) {
		free(y->Right);
  }
	free(y);
	return T;
}

struct nodeTree *DeleteAllTree(struct nodeTree *T) {
  while(T->key != NIL) {
    T = RBTreeDelete(T, T);
  }
  return T;
}
//-----------------------------------------------------------------------------//
int main() {
  int tests, size, query, temp, operation;
  struct nodeTree *T, *z, *pred, *succ;
  scanf("%d", &tests);
  for(int i = 1; i <= tests; i++) {
    T = AssignNIL();
    scanf("%d", &size);
    for(int j = 1; j <= size; j++) {
      scanf("%d", &temp);
      z = RBTreeSearch(T, temp);
      if(z->key == NIL) {
        T = RBTreeInsert(T, temp);
      } else {
        z->freq = z->freq + 1;
      }
    }
    scanf("%d", &query);
    for(int k = 1; k <= query; k++) {
      scanf("%d %d", &operation, &temp);
      switch(operation) {
        case 1:
          z = RBTreeSearch(T, temp);
          if (z->key != NIL) {
            pred = RBTreePredecessor(z);
            succ = RBTreeSuccessor(z);
            if (pred->key == NIL) {
              if (succ->key == NIL)
                printf("-1 100001\n");
              else
                printf("-1 %d\n", succ->key);
            } else {
              if (succ->key == NIL)
                printf("%d 100001\n", pred->key);
              else
                printf("%d %d\n", pred->key, succ->key);
            }
          } else {
            T = RBTreeInsert(T, temp);
            z = RBTreeSearch(T, temp);
            pred = RBTreePredecessor(z);
            succ = RBTreeSuccessor(z);
            if (pred->key == NIL) {
              if (succ->key == NIL)
                printf("-1 100001\n");
              else
                printf("-1 %d\n", succ->key);
            } else {
              if (succ->key == NIL)
                printf("%d 100001\n", pred->key);
              else
                printf("%d %d\n", pred->key, succ->key);
            }
            T = RBTreeDelete(T, z);
          }
          break;
        case 2:
          z = RBTreeSearch(T, temp);
          if(z->key != NIL) {
            z->freq = z->freq + 1;
          } else {
            T = RBTreeInsert(T, temp);
          }
          break;
        case 3:
          z = RBTreeSearch(T, temp);
          if(z->key != NIL) {
            if(z->freq > 1)
              z->freq = (z->freq - 1);
          } else {
            T = RBTreeDelete(T, z);
          }
          break;
        default:
          break;
      }
    }
    T = DeleteAllTree(T);
  }
  return 0;
}