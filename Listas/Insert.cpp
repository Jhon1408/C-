#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node {
  int key;
  struct node *next;
};

void printList(struct node * head) {
  struct node * q;
  q = head;
  while (q != NULL) {
    printf("%d -> ", q -> key);
    q = q -> next;
  }
  printf("NULL\n");
}

struct node *Insert(struct node *head, int element) {
    struct node *newnode, *actual, *prev;
    newnode = (struct node *) malloc (sizeof (struct node));
    newnode -> key = element;
    if (head == NULL) {
      newnode -> next = head;
      head = newnode;
    } else {
      if (element <= head -> key) {
        newnode -> next = head;
        head = newnode;
      } else {
        prev = NULL;
        actual = head;
        while ((actual != NULL) && (element > actual -> key)) {
          prev = actual;
          actual = actual -> next;
        }
        prev -> next = newnode;
        newnode -> next = actual;
      }
    }
    return head;
}

struct node *Remove(struct node *head, int element) {
  struct node *p, *q;
  if(head == NULL) {
    printf("empty list. imposible delete element.\n");
  } else {
    if (element == head -> key) {
      q = head;
      head = head -> next;
      free(q);
    } else {
      if (element < head -> key) {
        printf("Element %d is not in the list.", element);
      }
      p = NULL;
      q = head;
      while ((q != NULL) && (element > q -> key)) {
        p = q;
        q = q -> next;
        free(q);
      }
      if (q != NULL) {
        p -> next = q -> next;
        free(q);
      } else {
        printf("Element %d is not in the list.", element);
      }
    }
  }
}

int main() {
  struct node * head;
  int op, element;
  head = NULL;
  while(scanf("%d", &op) != EOF) {
    scanf("%d", &element);
    switch (op) {
      case 1:
        head = Insert(head, element);
        printList(head);
        break;
      case 2:
        head = Remove(head, element);
        printList(head);
        break;
      default:
        printf("operacion invalida");
        break;
    }
  }
  return 0;
}
