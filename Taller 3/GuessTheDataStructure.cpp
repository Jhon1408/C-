#include <stdlib.h>
#include <stdio.h>
#define myinfinite 2147483647
int heapsize = 0;
//---------------------------------------------------------------------------------------------
struct node {
    int key;
    struct node *next;
};
//---------------------------------------------------------------------------------------------
//COLAS..
struct node *ENQUEUE (struct node *tail, int element) {
	struct node *newnode;
	newnode = (struct node *) malloc (sizeof(struct node));
	newnode -> key = element;

	if(tail == NULL) {
		newnode->next = newnode;
		tail = newnode;
	} else {
		newnode->next = tail->next;
		tail->next = newnode;
		tail = newnode;
	}
	return tail;
}

int DEQUEUE(struct node **tail) {
	struct node *temp;
	int element = (myinfinite*-1);
	if(*tail == NULL) {
		//No retornamos nada.
  } else {
		if(*tail == (*tail)->next) {
			element = (*tail)->key;
			free(*tail);
			*tail=NULL;
		} else {
			temp = (*tail)->next;
			element = temp->key;
			(*tail)->next = temp->next;
			free(temp);
		}
	}
	return element;
}
//---------------------------------------------------------------------------------------------------
//PILAS
struct node *PUSH (struct node *top, int element) {
	struct node *newnode;
	newnode = (struct node *) malloc (sizeof(struct node));
	newnode->key=element;
	newnode->next=top;
	top=newnode;
	return top;
}

int POP (struct node **top) {
	struct node *temp;
	int element = (myinfinite*-1);
	if(*top != NULL) {
		temp = *top;
		element = temp->key;
		*top = (*top)->next;
		free(temp);
	}
	return element;
}

//------------------------------------------------------------------------------------------------------
//COLAS DE PRIORIDAD
int F_parent(int index) {
	return index/2;
}
int F_left (int index) {
	return 2*index;
}
int F_right(int index) {
	return 2*index+1;
}

void MinHeapify(int Array[],int index) {
	int left, right,least, temp;
	left = F_left(index);
	right = F_right(index);
	if((left <= heapsize) && (Array[left] < Array[index]))
		least = left;
	else
		least = index;
	if((right <= heapsize) && (Array[right]<Array[least]))
		least = right;
	if(least != index) {
		temp = Array[index];
		Array[index] = Array[least];
		Array[least] = temp;
		MinHeapify(Array,least);
	}
}

int MinPQ_minimun(int Array[]) {
	return Array[1];
}

int MinPQ_extract(int Array[]) {
	long long int min = -1*myinfinite;
	if( heapsize < 1) {
		//No retornamos nada
	} else {
		min = Array[1];
		Array[1] = Array[heapsize];
		heapsize = heapsize - 1;
		MinHeapify(Array,1);
  }
	return min;
}

void MinPQ_DecreaseKey (int Array[],int index,int key) {
  int temp;
  if( key > Array[index] ) {
    //No retornamos nada.
  } else {
    Array[index] = key;
  }
  while ((index > 1) && ((Array[F_parent(index)])> Array[index])) {
    temp = Array[index];
    Array[index] = Array[F_parent(index)];
    Array[F_parent(index)] = temp;
    index = F_parent(index);
  }
}

void MinPQ_insert(int Array[],int key) {
     heapsize = heapsize+1;
     Array[heapsize]= (myinfinite);
     MinPQ_DecreaseKey(Array,heapsize,key);
}
//---------------------------------------------------------------------------------------------------
int main() {
	int cant_operations;
	while(scanf("%d",&cant_operations) != EOF) {
		int element, operation,cont_stack = 0,cont_queue = 0,cont_PQ = 0,cont = 0;
		struct node *tail,*top;
    heapsize = 0;
		tail=NULL;
		top = NULL;
		int array[cant_operations + 5];

		for(int index=1; index <= cant_operations;index++) {
			scanf("%d",&operation);
			if(operation == 1) {
				scanf("%d",&element);
				tail = ENQUEUE(tail,element);
				top = PUSH(top,element);
				MinPQ_insert(array,(element*-1));
			} else {
				if(operation == 2) {
					scanf("%d",&element);
					int element_stack = POP(&top);
					int element_queue = DEQUEUE(&tail);
					int element_priority_queue = MinPQ_extract(array);
          cont++;
					if(element_priority_queue == (element*-1))
						cont_PQ++;
					if(element_stack == element)
						cont_stack++;
					if(element_queue == element)
						cont_queue++;
				}
			}
		}

    if ((cont_PQ == cont) && (cont_stack != cont) && (cont_queue != cont)) {
      printf("priority queue\n");
    } else {
      if ((cont_stack == cont) && (cont_PQ != cont) && (cont_queue != cont)) {
        printf("stack\n");
      } else {
        if ((cont_queue == cont) && (cont_PQ != cont) && (cont_stack != cont)) {
          printf("queue\n");
        } else {
          if ((cont_queue == cont) || (cont_PQ == cont) || (cont_stack == cont)) {
            printf("not sure\n");
          } else {
            printf("impossible\n");
          }
        }
      }
    }
	}
	return 0;
}
