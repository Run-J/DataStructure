#include "hash.h"

nameSearchTable* initnameSearchTable(void)
{
	nameSearchTable* hashTable = (nameSearchTable*)malloc(sizeof(nameSearchTable));
	if (hashTable == NULL)
	{
		printf("The nameSearch hash table init memory failure");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < TABLESIZE; i++)
	{
		hashTable->table[i] = NULL;
	}

	return hashTable;
}

dateSearchTable* initdateSearchTable(void)
{
	dateSearchTable* hashTable = (dateSearchTable*)malloc(sizeof(dateSearchTable));
	if (hashTable == NULL)
	{
		printf("The dateSearch hash table init memory failure");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < TABLESIZE; i++)
	{
		hashTable->table[i] = NULL;
	}

	return hashTable;
}

assignmentInfo* createAssignmentInfo(char* assignName, char* dueDate, int estimateTime)
{
	assignmentInfo* assignInfo = (assignmentInfo*)malloc(sizeof(assignmentInfo));
	if (assignInfo == NULL)
	{
		printf("Assignment info memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	assignInfo->assignName = (char*)malloc(sizeof(char) * ASSIGNNAMESIZE);
	if (assignInfo->assignName == NULL)
	{
		printf("Assignment name memory allocation error\n");
		free(assignInfo);
		exit(EXIT_FAILURE);
	}
	strcpy(assignInfo->assignName, assignName);

	assignInfo->dueDate = _strdup(dueDate);
	if (assignInfo->dueDate == NULL)
	{
		printf("dueDate memory allocation error\n");
		free(assignInfo);
		exit(EXIT_FAILURE);
	}

	assignInfo->estimateTime = estimateTime;
	assignInfo->next = NULL;

	return assignInfo;
}

unsigned int getHash(char* dueDate)
{
	unsigned hash = 0;
	int weight = 1;

	while (*dueDate != '\0')
	{
		hash = hash + (*dueDate) * weight;
		dueDate++;
		weight++;
	}

	return hash % TABLESIZE;
}

void insertToDateSearchTable(dateSearchTable* table, assignmentInfo* assign)
{
	unsigned int hash = getHash(assign->dueDate);

	if (table->table[hash] == NULL)
	{
		table->table[hash] = assign;
	}
	else
	{
		assign->next = table->table[hash];
		table->table[hash] = assign;
	}
}

void insertToNameSearchTable(nameSearchTable* table, assignmentInfo* assign)
{
	unsigned int hash = getHash(assign->assignName);

	if (table->table[hash] == NULL)
	{
		table->table[hash] = assign;
	}
	else
	{
		assign->next = table->table[hash];
		table->table[hash] = assign;
	}
}

void searchByName(nameSearchTable* table, char* assignName)
{
	unsigned int hashIndex = getHash(assignName);
	assignmentInfo* assign = table->table[hashIndex];

	if (assign == NULL)
	{
		printf("The assignment was not found.");
		return;
	}

	while (assign != NULL)
	{
		if (strcmp(assign->assignName, assignName) == 0)
		{
			printf("This assignment Duedate: %s, Estimate Time: %d hours\n", assign->dueDate, assign->estimateTime);
		}
		assign = assign->next;
	}
}

void searchByDate(dateSearchTable* table, char* dueDate)
{
	unsigned int hashIndex = getHash(dueDate);
	assignmentInfo* assign = table->table[hashIndex];

	if (assign == NULL)
	{
		printf("Today is a leisurely day.");
		return;
	}

	while (assign != NULL)
	{
		if (strcmp(assign->dueDate, dueDate) == 0)
		{
			printf("Assignment Name: %s, Estimate Time: %d hours\n", assign->assignName, assign->estimateTime);
		}
		assign = assign->next;
	}
}

void deleteByName(nameSearchTable* nameTable, dateSearchTable* dateTable, char* assignName) 
{
	unsigned int hashIndex = getHash(assignName);
	assignmentInfo* current = nameTable->table[hashIndex];
	assignmentInfo* prev = NULL;

	while (current != NULL) // can found
	{
		if (strcmp(current->assignName, assignName) == 0) 
		{
			// delete it in dateTable before delete it in name table
			deleteByDate(dateTable, current->dueDate, assignName);

			if (prev == NULL) // the node to be deleted is the head node of the linked list
			{
				nameTable->table[hashIndex] = current->next;
			}
			else // the node to be deleted is the middle/end of the lkinked list
			{
				prev->next = current->next;
			}

			free(current->assignName);
			free(current->dueDate);
			free(current);

			printf("Assignment '%s' has been deleted from name table.\n", assignName);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("Assignment '%s' was not found in name table.\n", assignName);
}


void deleteByDate(dateSearchTable* table, char* dueDate, char* assignName) 
{
	unsigned int hashIndex = getHash(dueDate);
	assignmentInfo* current = table->table[hashIndex];
	assignmentInfo* prev = NULL;

	while (current != NULL) 
	{
		if (strcmp(current->dueDate, dueDate) == 0 && strcmp(current->assignName, assignName) == 0) // found
		{
			if (prev == NULL) 
			{
				// the node to be deleted is the head node of the linked list
				table->table[hashIndex] = current->next;
			}
			else 
			{
				// the node to be deleted is the middle/end of the lkinked list
				prev->next = current->next;
			}
			// there is no need to free the node again, because this node will be freed in deleteByName
			printf("Assignment '%s' on %s has been deleted from date table.\n", assignName, dueDate);
			return;
		}
		// check next node of linked list on the same cell
		prev = current;
		current = current->next;
	}
}

