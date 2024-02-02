//Filename: Queue.cpp
//Programmer: Run Ji 润
//First Version: December 30, 2023

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

Node* initQueue()
{
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == NULL)
	{
		exit(1);
	}
	head->data = 0;
	head->next = NULL;
	return head;
}

void* enQueue(Node* head, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		exit(1);
	}
	node->data = data;

	Node* tailNode = head;
	for (int i = 0; i < head->data; i++)
		{
			tailNode = tailNode->next;
		}
		node->next = tailNode->next;
		tailNode->next = node;
		head->data++;
}

void printQueue(Node* head)
{
	Node* temp = head->next;
	while (temp != NULL)
	{
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
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

int deQueue(Node* head)
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
		head->data--;
		return data;
	
	}
}

int main(void)
{
	Node* queue = initQueue();
	enQueue(queue,1);
	enQueue(queue,2);
	enQueue(queue,3);
	enQueue(queue,4);
	printQueue(queue);

	int i = deQueue(queue);
	printf("data = %d\n", i);
	printQueue(queue);
	return 0;
}