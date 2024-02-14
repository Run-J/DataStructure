#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* nextNode;
}Node;

Node* createNode(void);
//Node* headInsert(int data, Node* head);
void headInsert(int data, Node** head);
void tailInsert(int data, Node** head);
void printList(Node* head);

int main(void)
{
	Node* newList = NULL;
	//newList = headInsert(1, newList);
	//newList = headInsert(2, newList);
	//newList = headInsert(3, newList);
	headInsert(1, &newList);
	headInsert(2, &newList);
	headInsert(3, &newList);
	tailInsert(4, &newList);
	tailInsert(5, &newList);
	tailInsert(6, &newList);
	printList(newList);

	return 0;
}

void printList(Node* head)
{
	while (head != NULL)
	{
		printf("DATA: %d\n", head->data);
		head = head->nextNode;
	}
}

//Node* headInsert(int data, Node* head)
//{
//	Node* newNode = createNode();
//	newNode->data = data;
//	newNode->nextNode = head;
//	return newNode;
//}

void headInsert(int data, Node** head)
{
	Node* newNode = createNode();
	newNode->data = data;
	newNode->nextNode = *head;
	*head = newNode;
}

void tailInsert(int data, Node** head)
{
	Node* newNode = createNode();
	newNode->data = data;
	newNode->nextNode = NULL;

	Node* temp = *head;
	if (temp == NULL)
	{
		*head = newNode;
		return;
	}

	while (temp->nextNode != NULL)
	{
		temp = temp->nextNode;
	}

	temp->nextNode = newNode;
}

Node* createNode(void)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("memory allocation failure");
		exit(0);
	}

	return newNode;
}

