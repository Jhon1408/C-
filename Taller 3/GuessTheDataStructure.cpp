#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define infinite 2147483647;
#define infNegative -2147483647;
int heapSize = 0;

struct node {
  int key;
  struct node *next;
};

struct node *Push(struct node *top, int element) {
  struct node *newNode;
  newNode = (struct node *) malloc(sizeof(struct node));
  newNode->key = element;
  newNode->next = top;
  top = newNode;
  return top;
}

int Pop(struct node **top) {
  struct node *q;
  int element = infNegative;
  if(*top == NULL)
    printf("Nope, vacio karnal.\n");
  else {
    q = *top;
    element = q->key;
    *top = (*top)->next;
    free(q);
  }
  return element;
}

struct node *ENQUEUE(struct node *tail, int element) {
  struct node *newNode;
  newNode = (struct node *) malloc(sizeof(struct node));
  newNode->key = element;
  if (tail == NULL) {
    newNode->next = newNode;
    tail = newNode;
  } else {
    newNode->next = tail->next;
    tail->next = newNode;
    tail = newNode;
  }
  return tail;
}

int DEQUEUE(struct node **tail) {
  struct node *q;
  int element = infNegative;
  if (*tail == NULL) {
    printf("Nope, lista vacia.\n");
  } else {
    if (*tail == (*tail)->next) {
      element = (*tail)->key;
      free(*tail);
      *tail == NULL;
    } else {
      q = (*tail)->next;
      element = q->key;
      (*tail)->next = q->next;
      free(q);
    }
  }
  return element;
}

int Parent(int i) {
  return (int) floor(i/2);
}

int Left(int i) {
    return (2 * i);
}

int Right(int i) {
  return ((2 * i) + 1);
}

void MinHeapify(int Q[], int i) {
  int l = Left(i);
  int r = Right(i);
  int least;

  if ((l <= heapSize) && (Q[l] < Q[i])) {
    least = l;
  } else {
    least = i;
  }

  if ((r <= heapSize) && (Q[r] < Q[least])) {
    least = r;
  }

  if (least != i) {
    int temp = Q[i];
    Q[i] = Q[least];
    Q[least] = temp;
    MinHeapify(Q, least);
  }
}

int MinPQ_Minimum(int Q[]) {
  return Q[1];
}

int MinPQ_Extract(int Q[]) {
  int min = 0;
  if(heapSize < 1) {
    printf("Error (Heap underflow!)\n");
  } else {
    min = Q[1];
    Q[1] = Q[heapSize];
    heapSize = heapSize - 1;
    MinHeapify(Q, 1);
  }
  return min;
}

void MinPQ_DecreaseKey(int Q[], int i, int key) {
  if (key > Q[i]) {
    printf("Error (New key is higher than current key)");
  } else {
    Q[i] = key;
    int temp;
    while ((i > 1) && (Q[Parent(i)] > Q[i])) {
      temp = Q[i];
      Q[i] = Q[Parent(i)];
      Q[Parent(i)] = temp;
      i = Parent(i);
    }
  }
}

void MinPQ_Insert(int Q[], int key) {
  heapSize = heapSize + 1;
  Q[heapSize] = infinite;
  MinPQ_DecreaseKey(Q, heapSize, key);
}

int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    struct node *top, *tail;
    int flagPilas = 1, flagColas = 1, flagPrioridad = 1, k, operation, Q[10005];
    heapSize = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &operation);
      if (operation == 1) {
        scanf("%d", &k);
        MinPQ_Insert(Q, k);
        top = Push(top, k);
        tail = ENQUEUE(tail, k);
      } else {
        if (operation == 2) {
          scanf("%d", &k);
          if (MinPQ_Extract(Q) != k) {
            flagPrioridad = 0;
          }
          if (Pop(&top) != k) {
            flagPilas = 0;
          }
          if (DEQUEUE(&tail) != k) {
            flagColas = 0;
          }
        }
      }
    }
    int sum = flagPrioridad + flagPilas + flagColas;
    switch (sum) {
      case (0):
        printf("impossible\n");
        break;
      case (3):
        printf("impossible\n");
        break;
      case (2):
        printf("not sure\n");
        break;
      case (1):
        if (flagPrioridad == 1) {
          printf("priority queue\n");
        } else {
          if (flagPilas == 1) {
            printf("stack\n");
          } else {
            printf("queue\n");
          }
        }
        break;
    }
  }
  return 0;
}
