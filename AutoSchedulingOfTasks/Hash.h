// this hash table use to search

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef _HEADER_H_
#define _HEADER_H_

#define TABLESIZE 30
#define ASSIGNNAMESIZE 100
#pragma warning(disable:4996)

typedef struct assignmentInfo
{
	char* assignName;
	char* dueDate; // key
	int estimateTime;
	struct assignmentInfo* next;
}assignmentInfo;

typedef struct dateSearchTable // for use date to seach assign
{
	assignmentInfo* table[TABLESIZE];
}dateSearchTable;

typedef struct nameSearchTable // for use name to search
{
	assignmentInfo* table[TABLESIZE];
}nameSearchTable;


nameSearchTable* initnameSearchTable(void);
dateSearchTable* initdateSearchTable(void);
assignmentInfo* createAssignmentInfo(char* assignName, char* dueDate, int estimateTime);
unsigned int getHash(char* dueDate);
void insertToDateSearchTable(dateSearchTable* table, assignmentInfo* assign);
void insertToNameSearchTable(nameSearchTable* table, assignmentInfo* assign);
void searchByName(nameSearchTable* table, char* assignName);
void searchByDate(dateSearchTable* table, char* dueDate);
void deleteByDate(dateSearchTable* table, char* dueDate, char* assignName); // use in deleteByName
void deleteByName(nameSearchTable* nameTable, dateSearchTable* dateTable, char* assignName);


#endif