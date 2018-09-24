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

//---------------------------------------------------------------------------------------------------------
int ganador(struct node *tail, int k) {
   struct node *q;
   int index, result;
   while(tail != tail -> next) {
      for(index = 1; index < k; index++)
         tail = tail -> next;
      q = tail -> next;
      tail -> next = q -> next;
      free(q);
   }
   result = tail -> key;
   free(tail);
   return result;
}

struct node *CreateCircularListDoublyLinked(int n) {
  struct node *tail;
  tail = NULL;
  for (int i = 2; i <= n; i++) {
    tail = InsertInCircularBoundlyLinkedList(tail, i);
  }
  return tail;
}

int solver(int n) {
  struct node *tail;
  int m, winner;
  for (int i = 1; ; i++) {
    tail = CreateCircularListDoublyLinked(n);
    winner = ganador(tail, i);
    if (winner == 2) {
      m = i;
      break;
    }
  }
  return m;
}

int JosephusLottery(struct node *tail, int k) {
  struct node *q;
  int index, clock = 0, result;
  tail = tail->next;
  while (tail != tail->next) {
    if (clock % 2 == 0) {
      for (index = 1; index < k; index++) {
        tail = tail->next;
      }
      q = tail;
      tail = tail->next;
      q->prev->next = q->next;
      q->next->prev = q->prev;
      free(q);
      clock++;
    } else {
      for (index = 1; index < k; index++) {
        tail = tail->prev;
      }
      q = tail;
      tail = tail->prev;
      q->prev->next = q->next;
      q->next->prev = q->prev;
      free(q);
      clock++;
    }
  }
  result = tail->key;
  free(tail);
  return result;
}

int main() {
  int n, k;
  while (scanf("%d %d", &n, &k) && ((n != 0) && (k != 0))) {
    m = solver(n, k);
    printf("%d\n", m);
  }
  return 0;
}
