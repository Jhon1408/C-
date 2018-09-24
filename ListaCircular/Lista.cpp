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


int main()
{
   struct node *tail;
   int element, operation;
   tail = NULL;
   while (scanf("%d", &operation) != EOF)
   {
         if (operation == 1)
         {
            scanf("%d", &element);
            tail = InsertCircularList(tail, element);
            PrintCircularList(tail);
         }
         else
         {
             if (operation == 2)
             {
                scanf("%d", &element);
                tail = DeleteElementCircularList(tail, element);
                PrintCircularList(tail);
             }
         }
   }
}
