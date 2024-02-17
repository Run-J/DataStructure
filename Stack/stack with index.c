#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define ARRAY_SIZE 10

typedef struct stack
{
	int* data;
	int topIndex;
}stack;

stack* initStack(void);
void push(int data, stack* stack);
bool isStackEmpty(stack* stack);
bool isStackFull(stack* stack);
int peek(stack* stack);
int pop(stack* stack);

int pop(stack* stack)
{
	if (isStackEmpty(stack) == true)
	{
		printf("The stack is empty now");
		exit(0);
	}

	int topData = stack->data[stack->topIndex];
	stack->topIndex--;
	return topData;
}

int peek(stack* stack)
{
	if (isStackEmpty(stack) == true)
	{
		printf("The stack is empty now");
		exit(0);
	}

	int topData = stack->data[stack->topIndex];
	return topData;
}

bool isStackFull(stack* stack)
{
	if (stack->topIndex == ARRAY_SIZE - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isStackEmpty(stack* stack)
{
	if (stack->topIndex == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void push(int data, stack* stack)
{
	if (isStackFull(stack) == true)
	{
		printf("The stack is fully");
		return;
	}

	stack->topIndex++;
	stack->data[stack->topIndex] = data;
}


stack* initStack(void)
{
	stack* newStack = (stack*)malloc(sizeof(stack));
	newStack->data = (int*)malloc(sizeof(int) * ARRAY_SIZE);
	newStack->topIndex = -1;
	return newStack;
}

int main(void)
{
	stack* newStack = initStack();
	push(1, newStack);
	push(2, newStack);
	push(3, newStack);

	printf("%d\n", peek(newStack));
	printf("%d\n", pop(newStack));
	printf("%d\n", pop(newStack));
	printf("%d\n", pop(newStack));
	printf("%d\n", pop(newStack));

	return 0;
}