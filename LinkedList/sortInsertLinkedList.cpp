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

void sortInsert(Node* L, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{ // Check if malloc was successful
		exit(1);
	}
	node->data = data;

	if (L->next == NULL)
	{
		node->next = L->next;
		L->next = node;
		return;
	}

	Node* pre = L;
	Node* temp = L->next;
	while (temp != NULL && node->data > temp->data)
	{
		temp = temp->next;
		pre = pre->next;
	}
	// follow is second way that can replace the above
	//while (temp != NULL)
	//{
	//	if (node->data < temp->data)
	//	{
	//		pre->next = node;
	//		node->next = temp;
	//		return;
	//	}
	//	
	//	temp = temp->next;
	//	pre = pre->next;
	//}

	node->next = pre->next;
	pre->next = node;
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
	sortInsert(list, 3);
	sortInsert(list, 2);
	sortInsert(list, 7);
	sortInsert(list, 1);
	sortInsert(list, 5);

	printList(list);

}