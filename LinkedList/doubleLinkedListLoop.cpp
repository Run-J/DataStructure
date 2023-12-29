#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
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
	head->next = head;
	head->pre = head;
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
	node->next = L->next;
	node->pre = L;
	L->next = node;
	L->next->pre = node;
	L->data++;
}

void tailInsert(Node* L, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		exit(1);
	}
	node->data = data;
	node->next = L;

	Node* last = L;
	while (last->next != L)
	{
		last = last->next;
	}
	last->next = node;
	node->pre = last;
	L->pre = node;
	L->data++;
}

void printList(Node* L)
{
	Node* temp = L->next;
	while (temp != L)
	{
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
	printf("Number of node: %d\n", L->data);
}

int deleteNode(Node* L, int data)
{
	Node* current = L->next;
	while (current != L)
	{
		if (current->data == data)
		{
			current->pre->next = current->next;
			current->next->pre = current->pre;
			free(current);
			L->data--;
			return TRUE;
		}
		current = current->next;
	}
	return FALSE;
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

	deleteNode(list, 3);
	deleteNode(list, 5);
	printList(list);

	return 0;
}