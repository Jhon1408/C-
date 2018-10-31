#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define RED 1
#define BLACK 0
#define NIL "2147483647"

//-----------------------------------------------------------------------------//
struct nodeTree {
  char key[32];
  int color;
  struct nodeTree *Left;
  struct nodeTree *Right;
  struct nodeTree *p;
};
//-----------------------------------------------------------------------------//
struct nodeTree *AssignNIL() {
  struct nodeTree *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  strcpy(z->key, NIL);
  z->color = BLACK;
  z->p = NULL;
  z->Left = NULL;
  z->Right = NULL;
  return z;
}
//-----------------------------------------------------------------------------//
void RBInorderTreeWalk(struct nodeTree *x) {
  if(strcmp(x->key,NIL) != 0) {
    RBInorderTreeWalk(x->Left);
    if(x->color == RED)
      printf("[%s|R] ", x->key);
    else
      printf("[%s|B] ", x->key);
    RBInorderTreeWalk(x->Right);
  }
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeSearch(struct nodeTree *x, char k[]) {
  if ((strcmp(x->key,NIL) == 0) || (strcmp(k, x->key) == 0)) {
    return x;
  }
  if(strcmp(k,x->key) < 0) {
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
  if(strcmp(x->Left->key,NIL) != 0) {
    y->Left->p = x;
  }
  y->p = x->p;
  if(strcmp(x->p->key,NIL) == 0) {
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
  if(strcmp(x->Right->key,NIL) != 0) {
    y->Right->p = x;
  }
  y->p = x->p;
  if(strcmp(x->p->key,NIL) == 0) {
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
  while (strcmp(x->Left->key,NIL) != 0) {
    x = x->Left;
  }
  return x;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeMaximum(struct nodeTree *x) {
  while (strcmp(x->Right->key,NIL) != 0) {
    x = x->Right;
  }
  return x;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreeSuccessor(struct nodeTree *x) {
  if (strcmp(x->Right->key,NIL) != 0) {
    return RBTreeMinimum(x->Right);
  }
  struct nodeTree *y;
  y = x->p;
  while ((strcmp(y->key,NIL) != 0) && (x == y->Right)) {
    x = y;
    y = y->p;
  }
  return y;
}
//-----------------------------------------------------------------------------//
struct nodeTree *RBTreePredecessor(struct nodeTree *x) {
  if (strcmp(x->Left->key,NIL) != 0) {
    return RBTreeMaximum(x->Left);
  }
  struct nodeTree *y;
  y = x->p;
  while ((strcmp(y->key,NIL) != 0) && (x == y->Left)) {
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
struct nodeTree *RBTreeInsert(struct nodeTree *T, char element[]) {
  struct nodeTree *x, *y, *z;
  z = (struct nodeTree *) malloc(sizeof(struct nodeTree));
  strcpy(z->key,element);
  z->color = RED;
  z->Left = AssignNIL();
  z->Left->p = z;
  z->Right = AssignNIL();
  z->Right->p = z;
  if(strcmp(T->key,NIL) != 0) {
    y = T->p;
  } else {
    y = T;
  }
	x = T;
	while(strcmp(x->key, NIL) != 0) {
		y = x;
		if(z->key < x->key) {
			x = x->Left;
    } else {
			x = x->Right;
    }
	}
	z->p = y;
	if(strcmp(y->key,NIL) == 0) {
		T = z;
	} else {
    free(x);
		if(strcmp(z->key,y->key) < 0) {
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
	if((strcmp(z->Left->key,NIL) == 0) || (strcmp(z->Right->key,NIL) == 0)) {
		y = z;
	} else {
		y = RBTreeSuccessor(z);
  }
	if(strcmp(y->Left->key,NIL) != 0) {
		x = y->Left;
	} else {
		x = y->Right;
  }
	x->p = y->p;
	if(strcmp(y->p->key,NIL) == 0) {
		T = x;
	} else {
		if(y == y->p->Left) {
			y->p->Left = x;
		} else {
			y->p->Right = x;
    }
	}

	if(y != z) {
		strcpy(z->key,y->key);
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
  while(strcmp(T->key,NIL) != 0) {
    T = RBTreeDelete(T, T);
  }
  return T;
}
//-----------------------------------------------------------------------------//
struct nodeTree *SearchInAll(struct nodeTree *T, struct nodeTree *x, char element[]) {
  char temp[64];
  struct nodeTree *z;
  if(strcmp(x->key,NIL) != 0) {
    x = SearchInAll(T, x->Left, element);
    strcpy(temp, element);
    strcat(temp, x->key);
    z = RBTreeSearch(T, temp);
    if((strcmp(z->key,NIL) != 0) && (strcmp(z->key,element) == 0)) {
      return z;
    }
    strcpy(temp, x->key);
    strcat(temp, element);
    z = RBTreeSearch(T, temp);
    if((strcmp(z->key,NIL) != 0) && (strcmp(z->key,element) == 0)) {
      return z;
    }
    x = SearchInAll(T, x->Right, element);
  }
  return x;
}

int main() {
  struct nodeTree *T, *z;
  char temp[32], concat[64];
  T = AssignNIL();
  while(scanf("%s",temp) != EOF && (strcmp(temp,".") != 0)) {
    if(strcmp(T->key,NIL) == 0) {
      T = RBTreeInsert(T, temp);
    } else {
      T = RBTreeInsert(T, temp);
      z = SearchInAll(T,T,temp);
      if(strcmp(z->key,NIL) != 0) {
        printf("%s\n", z->key);
      }  
    }
  }

  return 0;
}