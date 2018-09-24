#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node {
  int key;
  struct node *next;
  struct node *prev;
};
//----------------------------------------------------------------------------------------------------
struct node *InsertInCircularBoundlyLinkedList (struct node *tail, int element) {
  struct node *newnode;
  newnode = (struct node *) malloc (sizeof(struct node));
  newnode->key = element;

  if (tail == NULL) {
    newnode->next=newnode;
    newnode->prev=newnode;
    tail=newnode;
  } else {
    newnode->next = tail->next;
    tail->next->prev = newnode;
    newnode->prev = tail;
    tail->next = newnode;
    tail = newnode;
  }
  return tail;
}
//------------------------------------------------------------------------------------------------
struct node *DeleteInDoubleLinkedList (struct node *tail, int element) {
  struct node *previo, *actual;
  if(tail == NULL) {
    printf("imposible delete. empty list.\n");
  } else {
    if(tail == tail->next) {
      if(element == tail->key) {
        free(tail);
        tail = NULL;
      } else {
        printf("element %d is not in list.\n", element);
      }
    } else {
      previo = NULL;
      actual = tail->next;
      while(( previo != tail) && (actual->key != element)) {
        previo = actual;
        actual = actual->next;
      }
      if(previo==tail) {
        printf("element %d is not in list.\n", element);
      } else {
        if(previo == NULL)
          previo=tail;

        if(actual == tail)
          tail=tail->prev;

        previo->next = actual->next;
        actual->next->prev = previo;
        free(actual);
      }
    }
  }
return tail;
}
//--------------------------------------------------------------------------------------------------------
void PrintFromLeftToRight(struct node *tail) {
  struct node *front,*back;
  if(tail == NULL) {
    printf("empty list.\n");
  } else {
    back = NULL;
    front = tail->next;
    while(back != tail) {
      printf("%d -->",front->key);
      back = front;
      front = front->next;
    }
    printf("...\n");
  }
}

int main() {
  
  return 0;
}
