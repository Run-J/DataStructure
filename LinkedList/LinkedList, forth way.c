#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

typedef struct LinkedList
{
	Node* head;
}LinkedList;

Node* createNode();
void headInsert(LinkedList* list, int data);
void printList(LinkedList* list);
LinkedList* initLinkedList(void);

LinkedList* initLinkedList()
{
	LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
	if (newLinkedList == NULL)
	{
		exit(0);
	}

	newLinkedList->head = NULL;
	return newLinkedList;
}

Node* createNode()
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

void headInsert(LinkedList* list, int data)
{
	Node* node = createNode();
	node->data = data;
	node->next = list->head;
	list->head = node; // update head
}

void printList(LinkedList* list)
{
	Node* temp = list->head;
	while (temp != NULL)
	{
		printf("node = %d\n", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main(void)
{
	LinkedList* newLinkedList = initLinkedList();
	headInsert(newLinkedList, 1);
	headInsert(newLinkedList, 2);
	headInsert(newLinkedList, 3);
	printList(newLinkedList);
}