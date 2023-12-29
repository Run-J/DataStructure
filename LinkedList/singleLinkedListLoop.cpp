#include<stdio.h>
#include<stdlib.h>

#define TURE 1
#define FAIL 0

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
	L->next = L;
	return L;
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
	L->next = node;
	L->data++;
}

void printList(Node* L) {
	
	if (L->next == L) {
		printf("The list is empty.\n");
		return;
	}

	Node* temp = L->next;
	do 
	{
		printf("%d->", temp->data);
		temp = temp->next;
	} while (temp != L); 

	printf("HEAD\n"); 
	printf("List Length: %d\n", L->data);
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

	Node* temp = L;
	while (temp->next != L)
	{
		temp = temp->next;
	}

	temp->next = node;
	L->data++;
}

int deleteNode(Node* L, int data)
{
	Node* preNode = L;
	Node* currentNode = L->next;
	while (currentNode != L)
	{
		if (currentNode->data == data)
		{
			preNode->next = currentNode->next;
			free(currentNode);
			L->data--;
			return TURE;
		}
		else
		{
			preNode = currentNode;
			currentNode = currentNode->next;
		}
	}
	return FAIL;
}

int main(void)
{
	Node* list = initList();
	headInsert(list, 1);
	headInsert(list, 2);
	headInsert(list, 3);
	headInsert(list, 4);
	headInsert(list, 5);
	printList(list);

	tailInsert(list, 6);
	tailInsert(list, 7);
	tailInsert(list, 8);
	printList(list);

	deleteNode(list, 6);
	printList(list);

	return 0;
}