#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define infNegative -2147483647;

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

int main() {
  struct node *top;
  int operacion, element;
  top = NULL;
  while (scanf("%d", &operacion) != EOF) {
    if (operacion == 1) {
      scanf("%d", &element);
      top = Push(top,element);
    } else {
      if (operacion == 2) {
        element = Pop(&top);
        if(element != -2147483647) {
          printf("%d\n", element);
        }
      } else {
        printf("Bad operation, use:\n1: Push\n2: Pop\n");
      }
    }
  }
  return 0;
}
