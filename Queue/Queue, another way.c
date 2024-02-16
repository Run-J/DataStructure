#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node
{
	int data;
	struct Node* nextNode;
}Node;

typedef struct Queue
{
	Node* front;
	Node* tail;
}Queue;

Queue* initQueue(void);
Node* createNode(int data);
void enQueue(Queue* queue, int data);
void deQueue(Queue* queue);
bool isQueueEmpty(Queue* queue);
void checkFront(Queue* queue);
void printQueue(Queue* queue);

void deQueue(Queue* queue)
{
	if (isQueueEmpty(queue))
	{
		printf("The queue is empty now\n");
		return;
	}

	Node* temp = queue->front->nextNode;
	Node* currentDeQueue = queue->front;
	printf("The first node's data just deQueue from the queue: %d\n", currentDeQueue->data);
	free(currentDeQueue);
	queue->front = temp;
}

void printQueue(Queue* queue)
{
	if (isQueueEmpty(queue))
	{
		printf("The queue is empty now\n");
		return;
	}

	Node* temp = queue->front;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->nextNode;
	}
}

void checkFront(Queue* queue)
{
	if (isQueueEmpty(queue))
	{
		printf("The queue is empty now\n");
	}
	else
	{
		printf("The first node's data in the queue: %d\n", queue->front->data);
	}
}


bool isQueueEmpty(Queue* queue)
{
	if (queue->front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void enQueue(Queue* queue, int data)
{
	Node* newNode = createNode(data);
	if (isQueueEmpty(queue))
	{
		queue->front = newNode;
		queue->tail = newNode;
	}
	else
	{
		queue->tail->nextNode = newNode;
		queue->tail = newNode;
	}
}

Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Memory alloction failure");
		exit(0);
	}
	newNode->data = data;
	newNode->nextNode = NULL;
	return newNode;
}

Queue* initQueue(void)
{
	Queue* newQueue = (Queue*)malloc(sizeof(Queue));
	if (newQueue == NULL)
	{
		printf("Memory alloction failure");
		exit(0);
	}
	newQueue->front = NULL;
	newQueue->tail = NULL;

	return newQueue;
}

int main(void)
{
	Queue* newQueue = initQueue();
	enQueue(newQueue, 1);
	enQueue(newQueue, 2);
	enQueue(newQueue, 3);
	printf("Now, this is full data that queue have\n");
	printQueue(newQueue);
	// checkFront(newQueue); // just check, not free

	deQueue(newQueue); // there doing free(queue->front)
	printf("Now, this is full data that queue have after deQueue\n");
	printQueue(newQueue);

	return 0;
}