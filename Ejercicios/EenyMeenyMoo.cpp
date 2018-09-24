#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node {
      int key;
      struct node *next;
};

struct node *InsertCircularList(struct node *tail, int element) {
      struct node *p;
      p = (struct node *) malloc (sizeof (struct node));
      p -> key = element;
      if (tail == NULL) {
         p -> next = p;
         tail = p;
      } else {
         p -> next = tail -> next;
         tail -> next = p;
         tail = p;
      }
      return tail;
}

void PrintCircularList(struct node *tail) {
  struct node *actual, *prev;
  if (tail == NULL) {
     printf("The list is empty\n");
  } else {
      prev = NULL;
      actual = tail -> next;
      while (prev != tail) {
            printf("%d -> ", actual -> key);
            prev = actual;
            actual = prev -> next;
      }
      printf(". . .\n");
  }
}

struct node *DeleteCircularList(struct node *tail) {
      struct node *actual;

      if (tail == NULL) {
         printf("Imposible delete of list. The list is empty.\n");
      } else {
          if (tail -> next == tail) {
             free(tail);
             tail = NULL;
          } else {
               actual = tail -> next;
               tail -> next = actual -> next;
               free(actual);
          }
      }
      return tail;
}

struct node *DeleteElementCircularList(struct node *tail, int element) {
      struct node *actual, *prev;
      if (tail == NULL) {
         printf("Imposible delete of list. The list is empty.\n");
      } else {
          if (tail -> next == tail) {
             if (tail -> key == element) {
                free(tail);
                tail = NULL;
             } else {
                  printf("Element %d is not in the list\n", element);
             }
          } else {
              prev = NULL;
              actual = tail -> next;
              while ((prev != tail) && (actual -> key != element)) {
                    prev = actual;
                    actual = actual -> next;
              }
              if (actual -> key == element) {
                 if (prev == NULL)
                    prev = tail;
                 if (actual == tail)
                    tail = prev;
               prev -> next = actual -> next;
               free(actual);
               } else {
                    printf("Element %d is not in the list\n", element);
               }
          }
      }
      return tail;
}

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

struct node *CreateCircularList(int n) {
  struct node *tail;
  tail = NULL;
  for (int i = 2; i <= n; i++) {
    tail = InsertCircularList(tail, i);
  }
  return tail;
}

int solver(int n) {
  struct node *tail;
  int m, winner;
  for (int i = 1; ; i++) {
    tail = CreateCircularList(n);
    winner = ganador(tail, i);
    if (winner == 2) {
      m = i;
      break;
    }
  }
  return m;
}

int main() {
   int n, m;
   while (scanf("%d", &n) && (n != 0)) {
     m = solver(n);
     printf("%d\n", m);
   }
   return 0;
}
