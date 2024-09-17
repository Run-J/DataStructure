#include "BST.h"

assignmentNode* createNode(char* assignName, char* dueDate, int estimateTime)
{
	assignmentNode* newAssignNode = (assignmentNode*)malloc(sizeof(assignmentNode));
	if (newAssignNode == NULL)
	{
		printf("The newAssignNode memory allocated filure");
		exit(EXIT_FAILURE);
	}

	newAssignNode->assignName = (char*)malloc(sizeof(char) * ASSIGNNAMESIZE);
	if (newAssignNode->assignName == NULL)
	{
		free(newAssignNode);
		exit(EXIT_FAILURE);
	}
	strcpy(newAssignNode->assignName, assignName);

	newAssignNode->dueDate = (char*)malloc(sizeof(char) * DUEDATEINPUTSIZE);
	if (newAssignNode->dueDate == NULL)
	{
		free(newAssignNode);
		exit(EXIT_FAILURE);
	}
	strcpy(newAssignNode->dueDate, dueDate);

	newAssignNode->estimateTime = estimateTime;

	newAssignNode->leftChild = NULL;
	newAssignNode->rightChild = NULL;
	return newAssignNode;
}


assignmentNode* insertNode(assignmentNode* parentNode, assignmentNode* newAssign)
{
	if (parentNode == NULL)
	{
		return newAssign;
	}

	if (strcmp(parentNode->dueDate, newAssign->dueDate) >= 0 ) // new <= parent
	{
		parentNode->leftChild = insertNode(parentNode->leftChild, newAssign);
	}
	else
	{
		parentNode->rightChild = insertNode(parentNode->rightChild, newAssign);
	}

	return parentNode;
}


void inorderPrint(assignmentNode* root)
{
	if (root != NULL)
	{
		inorderPrint(root->leftChild);
		printf("%s: due date %s, estimate %d hours\n", root->assignName, root->dueDate, root->estimateTime);
		inorderPrint(root->rightChild);
	}
}


void inorderPrintExam(assignmentNode* root)
{
	if (root != NULL)
	{
		inorderPrintExam(root->leftChild);
		char* tempName =(char*)malloc(strlen(root->assignName) + 1);
		if (tempName != NULL) 
		{
			strcpy(tempName, root->assignName);

			char* reviewPtr = strstr(tempName, " review");
			if (reviewPtr != NULL) 
			{
				*reviewPtr = '\0'; 
			}

			printf("%s: date %s, estimate difficulty %d (level)\n", tempName, root->dueDate, root->estimateTime);
			free(tempName);
		}
		else 
		{
			printf("Error when check review string in the name");
			exit(EXIT_FAILURE);
		}
		inorderPrintExam(root->rightChild);
	}
}


assignmentNode* deleteNode(assignmentNode* parentNode, char* assignName)
{
	if (parentNode == NULL)
	{
		return parentNode;
	}

	if (strcmp(parentNode->assignName, assignName) > 0) // searchName < parentName
	{
		parentNode->leftChild = deleteNode(parentNode->leftChild, assignName);
	}
	else if (strcmp(parentNode->assignName, assignName) < 0) // searchName > parentName
	{
		parentNode->rightChild = deleteNode(parentNode->rightChild, assignName);
	}
	else // found
	{
		// only one childNode / no childNode
		if (parentNode->leftChild == NULL && parentNode->rightChild != NULL)
		{
			assignmentNode* temp = parentNode->rightChild;
			free(parentNode->assignName);
			free(parentNode->dueDate);
			free(parentNode);
			return temp;
		}
		else if (parentNode->rightChild == NULL && parentNode->leftChild != NULL)
		{
			assignmentNode* temp = parentNode->leftChild;
			free(parentNode->assignName);
			free(parentNode->dueDate);
			free(parentNode);
			return temp;
		}
		else
		{
			free(parentNode);
			parentNode = NULL;
			return parentNode;
		}

		// two child
		assignmentNode* minimumNode = findMinimum(parentNode->rightChild);

		free(parentNode->assignName); 
		parentNode->assignName = strdup(minimumNode->assignName);
		free(parentNode->dueDate);
		parentNode->dueDate = strdup(minimumNode->dueDate);
		parentNode->estimateTime = minimumNode->estimateTime;

		parentNode->rightChild = deleteNode(parentNode->rightChild, minimumNode->assignName);
	}
	return parentNode;
}


assignmentNode* findMinimum(assignmentNode* parentNode)
{
	while (parentNode->leftChild != NULL)
	{
		parentNode = parentNode->leftChild;
	}
	return parentNode;
}
/*
use recursio to write findMinimum
assignmentNode* findMinimum(assignmentNode* parentNode)
{
	if (parentNode == NULL)
	{
		return NULL;
	}

	if (parentNode->leftChild == NULL)
	{
		return parentNode;
	}
	else
	{
		return findMinimum(parentNode->leftChild);
	}
}
*/


