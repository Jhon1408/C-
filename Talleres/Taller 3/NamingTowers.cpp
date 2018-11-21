#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MyNegativeInfinite -2147483647

struct node
{
	char key;
	struct node *next;
};

//----------------------------------------------------------------------------
//PILAS

struct node *ENQUEUE(struct node *tail, char element)
{
	struct node *newnode;
	newnode = ( struct node *) malloc (sizeof (struct node));
	newnode -> key = element;
	if (tail == NULL)
	{
		newnode -> next = newnode;
		tail = newnode;
	}
	else
	{
		newnode -> next = tail -> next;
		tail -> next = newnode;
		tail = newnode;
	}
	return tail;
}

int DEQUEUE (struct node **tail)
{
	struct node *q;
	int element = MyNegativeInfinite;
	if (*tail == NULL)
		printf("The queue is empty.\n");
	else
	{
		if(*tail == (*tail) -> next)
		{
			element = ((*tail) -> key);
			free(*tail);
			*tail = NULL;
		}
		else
		{
			q = (*tail) -> next;
			element = q -> key;
			(*tail) -> next = q -> next;
			free(q);
		}
	}
	return element;
}


//----------------------------------------------------------------------------
//COLAS

struct node *PUSH(struct node *top, int element)
{
	struct node *newnode;
	newnode = (struct node *) malloc (sizeof(struct node));
	newnode -> key = element;
	newnode -> next = top;
	top = newnode;
	return top;
}

int POP (struct node **top)
{
	struct node *temp;
	int element = MyNegativeInfinite;
	if(*top != NULL)
	{
		temp = *top;
		element = temp->key;
		*top = (*top)->next;
		free(temp);
	}
	else
		printf("%the stack is empty.\n");
	return element;
}

int Comparar (char element)
{
	if (element == 'A' || element == 'H' || element == 'I'|| element == 'M' || element == 'O'
		|| element == 'T' || element == 'U' || element == 'V' || element == 'W' || element == 'X'
		|| element == 'Y')
		return 1;
	else
		return 0;
}


int main()
{

	char palabra[100];
	struct node *top, *tail;
	int operation, index, cont = 0,cont2, cont3 = 0, flag = 1;
	char  element1, element2, element3;
	top = NULL;
	tail = NULL;
	scanf("%d", &operation);

	while (cont3 < operation)
	{
		cont2 = 0;
		index = 0;
		scanf("%s", &palabra);
		while ( palabra[index] != '\0')
		{
			top = PUSH (top, palabra [index]);
			tail = ENQUEUE(tail, palabra [index]);
			index++;
			cont++;
		}
		while  (cont > 0)
		{
			element1 = POP(&top);
			element2 = DEQUEUE(&tail);
			cont--;

			if (element1 == element2)
			{
				element3 = Comparar(element1);
				if (element3 != 1)
				{
					flag = 0;
					break;
				}
			}
			else
			{
				flag = 0;
				break;
			}
		}

		if (flag == 1)
			printf("YES\n");
		else
			printf("NO\n");

		cont3++;
	}
	return 0;
}
