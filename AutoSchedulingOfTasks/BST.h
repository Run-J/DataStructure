// bst use to traversal

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#ifndef _BST_H_
#define _BST_H_
#pragma warning(disable:4996)

#define ASSIGNNAMESIZE 100
#define DUEDATEINPUTSIZE 1

typedef struct assignmentNode
{
	char* assignName;
	char* dueDate; // key
	int estimateTime;
	struct assignmentNode* leftChild;
	struct assignmentNode* rightChild;
}assignmentNode;

assignmentNode* createNode(char* assignName, char* dueDate, int estimateTime);
assignmentNode* insertNode(assignmentNode* parentNode, assignmentNode* newAssign);
void inorderPrintExam(assignmentNode* root);
void inorderPrint(assignmentNode* root);
assignmentNode* deleteNode(assignmentNode* parentNode, char* assignName);
assignmentNode* findMinimum(assignmentNode* parent);

#endif