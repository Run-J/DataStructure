#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

Node* initList()
{
	Node* L = (Node*)malloc(sizeof(Node));
	if (L == NULL)
	{
		exit(1);
	}
	L->data = 0;
	L->next = NULL;
	return L;
}

void headInsert(Node* L, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{ // Check if malloc was successful
		exit(1);
	}
	node->data = data;
	node->next = L->next;
	L->next = node;
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

	Node* temp = L;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = node;
}

void deleteNode(Node* L, int data)
{
	Node* pre = L;
	Node* current = L->next;
	while (current)
	{
		if (current->data == data)
		{
			pre->next = current->next;
			free(current);
			break;
		}	
		pre = current;
		current = current->next;
	}

}

void printList(Node* L)
{
	Node* node = L->next;
	while (node != NULL)
	{
		printf("node = %d\n", node->data);
		node = node->next;
	}
	printf("\n");
}

int main(void)
{
	Node* list = initList();
	headInsert(list, 1);
	headInsert(list, 2);
	headInsert(list, 3);
	headInsert(list, 4);
	headInsert(list, 5);
	tailInsert(list, 1);
	tailInsert(list, 2);
	tailInsert(list, 3);
	printList(list);

	deleteNode(list, 5);
	deleteNode(list, 3);
	printList(list);
}