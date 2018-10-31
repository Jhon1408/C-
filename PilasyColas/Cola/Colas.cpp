#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define infNegative -2147483647;

struct node {
  int key;
  struct node *next;
};

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

int main() {
  struct node *tail;
  int operation, element;
  tail = NULL;
  while (scanf("%d", &operation) != EOF) {
    if (operation == 1) {
      scanf("%d", &element);
      tail = ENQUEUE(tail, element);
    } else {
      if (operation == 2) {
        element = DEQUEUE(&tail);
        if (element != -2147483647) {
          printf("%d\n", element);
        }
      } else {
        printf("Bad operation, use:\n1: Push\n2: Pop\n");
      }
    }
  }
  return 0;
}
