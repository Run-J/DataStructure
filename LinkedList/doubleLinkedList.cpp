#include <stdio.h>
#include <stdlib.h>

#define TURE 1 
#define FALSE 0
typedef struct Node
{
	int data;
	struct Node* pre;
	struct Node* next;
}Node;

Node* initList()
{
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == NULL)
	{
		exit(1);
	}
	head->data = 0;
	head->next = NULL;
	head->pre = NULL;
	return head;
}

void headInsert(Node* L, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		exit(1);
	}
	node->data = data;
	if (L->data == 0) //Linked list is empty
	{
		node->next = L->next;
		node->pre = L;
		L->next = node;
		L->data++;
	}
	else
	{
		node->next = L->next;
		node->pre = L;
		L->next->pre = node;
		L->next = node;
		L->data++;
	}
}

void tailInsert(Node* L, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		exit(1);
	}
	node->data = data;
	node->next = NULL;

	Node* pre = L;
	while (pre->next != NULL)
	{
		pre = pre->next;
	}
	pre->next = node;
	node->pre = pre;
	L->data++;
}

int deleteNode(Node* L, int data)
{
	Node* current = L->next;
	while (current != NULL)
	{
		if (current->data == data)
		{
			current->pre->next = current->next;
			current->next->pre = current->pre;
			free(current);
			L->data--;
			return TURE;
		}
		current = current->next;
	}
	return FALSE;
}

void printList(Node* L)
{
	Node* temp = L->next;
	while (temp != NULL)
	{
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

int main(void)
{
	Node* list = initList();
	headInsert(list, 1);
	headInsert(list, 2);
	headInsert(list, 3);
	printList(list);

	tailInsert(list, 4);
	tailInsert(list, 5);
	tailInsert(list, 6);
	printList(list);

	deleteNode(list, 5);
	deleteNode(list, 2);
	printList(list);
	return 0;
}