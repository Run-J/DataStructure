#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 5

typedef struct circularArray
{
	int data[SIZE];
	int front;
	int tail;
	int count; // current elements amount
}CircularArray;


CircularArray* initCircularArray(void);
bool isCircularArrayEmpty(CircularArray* array);
bool isCircularArrayFull(CircularArray* array);
void enArray(int data, CircularArray* array);
int deArray(CircularArray* array);
void printArray(CircularArray* array);
void printPhysicalArray(CircularArray* array);


void printArray(CircularArray* array)
{
	printf("The following is logical order (start with position of front pointer)\n");
	for (int i = 0; i < array->count; i++) 
	{
		int index = (array->front + i) % SIZE;
		printf("%d ", array->data[index]);
	}
	printf("\n");
}

void printPhysicalArray(CircularArray* array)
{
	printf("The following is physical order (start with really first element in array)\n");
	for (int i = 0; i < array->count; i++)
	{
		printf("%d ", array->data[i]);
	}
	printf("\n");
}


int deArray(CircularArray* array)
{
	if ( ! isCircularArrayEmpty(array) )
	{
		int data = array->data[array->front];
		array->front = (array->front + 1) % SIZE;
		array->count--;
		return data;
	}
	else
	{
		printf("The circular array is empty");
		return -1;
	}
}


void enArray(int data, CircularArray* array)
{
	if ( ! isCircularArrayFull(array) )
	{
		array->data[array->tail] = data;
		array->tail = (array->tail + 1) % SIZE;
		array->count++;
	}
	else
	{
		printf("The at %d in circular array is full\n", array->front);
		return;
	}
}


bool isCircularArrayFull(CircularArray* array)
{
	return array->count == SIZE;
}


bool isCircularArrayEmpty(CircularArray* array)
{
	return array->count == 0;
}


CircularArray* initCircularArray(void)
{
	CircularArray* newCircularArray = (CircularArray*)malloc(sizeof(CircularArray));
	if (newCircularArray == NULL)
	{
		printf("Memory allocation failure");
		exit(1);
	}

	newCircularArray->front = 0;
	newCircularArray->tail = 0;
	newCircularArray->count = 0;

	return newCircularArray;
}

int main(void)
{
	CircularArray* aCircularArray = initCircularArray();
	enArray(1, aCircularArray);
	enArray(2, aCircularArray);
	enArray(3, aCircularArray);
	enArray(4, aCircularArray);
	enArray(5, aCircularArray);
	enArray(6, aCircularArray);
	
	deArray(aCircularArray);
	enArray(7, aCircularArray);

	printArray(aCircularArray);
	printPhysicalArray(aCircularArray);

	return 0;
}