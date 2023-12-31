//Filename: Stack.cpp
//Programmer: Run Ji 润
//First Version: December 30, 2023

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

Node* initStack()
{
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == NULL)
	{
		exit(1);
	}
	head->next = NULL;
	head->data = 0;
	return head;
}

int isEmpty(Node* head)
{
	if (head->data == 0 || head->next == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int pop(Node* head)
{
	if (isEmpty(head))
	{
		return -1;
	}
	else
	{
		Node* node = head->next;
		int data = node->data;
		head->next = node->next;
		free(node);
		return data; 
		head->data--;
	}
}

void push(Node* head, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		exit(1);
	}
	node->data = data;
	node->next = head->next;
	head->next = node;
	head->data++;
}

void printStack(Node* head)
{
	Node* temp = head->next;
	while (temp != NULL)
	{
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

int main(void)
{
	Node* S = initStack();
	push(S, 1);
	push(S, 2);
	push(S, 3);
	push(S, 4);
	printStack(S);

	int i = pop(S);
	printf("Current element: %d\n", i);
	printStack(S);

	int j = pop(S);
	printf("Current element: %d\n", j);
	printStack(S);

	return 0;
}