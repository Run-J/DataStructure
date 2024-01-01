//Filename: CircularQueue.cpp
//Programmer: Run Ji 润
//First Version: December 31, 2023

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 6

typedef struct Queue
{
	int front;
	int rear;
	int data[MAXSIZE];
}Queue;

Queue* initQueue()
{
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	if (Q == NULL)
	{
		exit(1);
	}
	Q->front = Q->rear = 0;
	return Q;
}

int isFull(Queue* Q)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isEmpty(Queue* Q)
{
	if (Q->front == Q->rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int enQueue(Queue* Q, int data)
{
	if (isFull(Q))
	{
		return -1;
	}
	else
	{
		Q->data[Q->rear] = data;
		Q->rear = (Q->rear + 1) % MAXSIZE;
		return 0;
	}
}

int deQueue(Queue* Q)
{
	if (isEmpty(Q))
	{
		return -1;
	}
	else
	{
		int data = Q->data[Q->front];
		Q->front = (Q->front + 1) % MAXSIZE;
		return data;
	}
}


void printQueue(Queue* Q)
{
	int index = Q->front;
	int lenth = (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
	for (int i = 0; i < lenth; i++)
	{
		printf("%d->", Q->data[index]);
		index = (index + 1) % MAXSIZE;
	}
	printf("NULL\n");

}

int main(void)
{
	Queue* Q = initQueue();
	enQueue(Q, 1);
	enQueue(Q, 2);
	enQueue(Q, 3);
	enQueue(Q, 4);
	enQueue(Q, 5);
	printQueue(Q);

	deQueue(Q);
	deQueue(Q);
	printQueue(Q);
	return 0;
}