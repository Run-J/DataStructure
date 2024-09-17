#include "hash.h"
#include "BST.h"
#include "Schedule.h"
#include <stdbool.h>

#define MAX_CHAR_SIZE 50
#define USER_NUMBERINPUT_BUFFER 20
#define LINE_BUFFER_FILE 512

void menu(void);
char* getUserInput(void);
char* getUserInputDate(void);
char* appendReviewToExamName(const char* examName);
bool isValidDate(const char* date);
int getUserNumber(void);
void showMenuAndProcessUserChoice(int choice, nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root, assignmentNode** examRoot);
void processAdd(nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root, bool exam);
void processSearch(nameSearchTable* nameTable, dateSearchTable* dateTable);
void processDelete(nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root);
void generateASchedule(assignmentNode* root, assignmentNode* examRoot);
void loadTasksFromFile(nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root, bool isExam);


int main(void)
{
	nameSearchTable* nameTable = initnameSearchTable();
	dateSearchTable* dateTable = initdateSearchTable();
	assignmentNode* root = NULL;
	assignmentNode* examRoot = NULL;
	
	int userChoice = 0;
	do
	{
		menu();
		userChoice = getUserNumber();
		showMenuAndProcessUserChoice(userChoice, nameTable, dateTable, &root, &examRoot);

	} while (userChoice != 9);

	return 0;
}


void menu(void)
{
	printf
	(
		"\n\n"
		"The Assignment\\Exam\\Tasks Scheduler\n"
		"Please choose an option:\n"
		"1. Add new assignment\n"
		"2. Add new exam\n"
		"3. Mark the completion of an assignment\\exam\n"
		"4. Search for a assignment\\exam by name or date\n"
		"5. Show upcoming dues\n"
		"6. Generate a schedule\n"
		"7. Load assignments from a file\n"
		"8. Load exams from a file\n"
		"9. Exit\n"
		"Enter your choice: "
	);
}


void showMenuAndProcessUserChoice(int choice, nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root, assignmentNode** examRoot)
{
	switch (choice)
	{
	case 1:
		processAdd(nameTable, dateTable, root, false);
		break;
	case 2:
		processAdd(nameTable, dateTable, examRoot, true);
		break;
	case 3:
		processDelete(nameTable, dateTable, root);
		break;
	case 4:
		processSearch(nameTable, dateTable);
		break;
	case 5:
		printf("\nComing Assignment: \n");
		inorderPrint(*root);
		printf("\nComing Exam: \n");
		inorderPrintExam(*examRoot);
		break;
	case 6:
		generateASchedule(*root, *examRoot);
		break;
	case 7:
		loadTasksFromFile(nameTable, dateTable, root, false);
		break;
	case 8:
		loadTasksFromFile(nameTable, dateTable, examRoot, true);
		break;
	case 9:
		printf("Exiting the program...\n");
		break;
	default:
		printf("Invalid choice. Please try again.\n");
		break;
	}

}


void processAdd(nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root, bool exam)
{
	// get info
	char* assignmentName = '\0';
	char* assignDueDate = '\0';
	int estimateTime = 0;

	if (exam != true)
	{
		printf("Enter Assignment Name: ");
		assignmentName = getUserInput();
		printf("Enter Due Date (YYYY-MM-DD): ");
		assignDueDate = getUserInputDate();
		printf("Enter Assignment Estimated Time (in hours): ");
		estimateTime = getUserNumber();
	}
	else
	{
		printf("Enter Exam Name: ");
		assignmentName = getUserInput();
		char* temp = appendReviewToExamName(assignmentName);
		free(assignmentName);
		assignmentName = temp;
		printf("Enter Exam Date (YYYY-MM-DD): ");
		assignDueDate = getUserInputDate();
		printf("Enter Difficult level ( 1-3 ): ");
		estimateTime = getUserNumber();
	}

	// insert to the hsah table
	assignmentInfo* newAssign = createAssignmentInfo(assignmentName, assignDueDate, estimateTime);

	insertToNameSearchTable(nameTable, newAssign);
	insertToDateSearchTable(dateTable, newAssign);

	// insert to the tree
	assignmentNode* newNode = createNode(assignmentName, assignDueDate, estimateTime);
	*root = insertNode(*root, newNode);

	free(assignmentName);
	free(assignDueDate);
}


void processSearch(nameSearchTable* nameTable, dateSearchTable* dateTable)
{
	printf
	(
		"How would you like to search for an assignment?\n"
		"1. By assignment name\n"
		"2. By exam name\n"
		"3. By date\n"
		"Enter your choice: "
	);

	int searchOption = getUserNumber();

	switch (searchOption) 
	{
	case 1: 
	{
		printf("Enter the name of the assignment: ");
		char* name = getUserInput();
		searchByName(nameTable, name);
		free(name); 
		break;
	}
	case 2:
	{
		printf("Enter the name of the exam: ");
		char* name = getUserInput();
		char* temp = appendReviewToExamName(name);
		free(name);
		name = temp;
		searchByName(nameTable, name);
		free(name);
		break;
	}
	case 3: 
	{
		printf("Enter the due date of the assignment (YYYY-MM-DD): ");
		char* date = getUserInputDate(); 
		if (!isValidDate(date)) 
		{
			printf("Invalid date format.\n");
		}
		else 
		{
			searchByDate(dateTable, date);
		}
		free(date);
		break;
	}
	default:
		printf("Invalid choice. Please try again.\n");
		break;
	}
}


void processDelete(nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root)
{
	printf
	(
		"Enter the name of the task to delete: \n"
		"1. By assignment name\n"
		"2. By exam name\n"
		"Enter your choice: "
	);

	int searchOption = getUserNumber();
	switch (searchOption)
	{
	case 1:
	{
		printf("Enter the name of the assignment: ");
		char* name = getUserInput();
		deleteByName(nameTable, dateTable, name);
		*root = deleteNode(*root, name);
		free(name);
		break;
	}
	case 2:
	{
		printf("Enter the name of the exam: ");
		char* name = getUserInput();
		char* temp = appendReviewToExamName(name);
		free(name);
		name = temp;
		deleteByName(nameTable, dateTable, name);
		*root = deleteNode(*root, name);
		free(name);
		break;
	}
	default:
		printf("Invalid choice. Please try again.\n");
		break;
	}
}


void generateASchedule(assignmentNode* root, assignmentNode* exam)
{
	scheduler* newScheduler = initialScheduler();
	generateMonthSchedule(root, newScheduler); // only assign
	addExamToSchedule(exam, newScheduler); // then add exam to the schedule, due to dont follow the assign logical rule
	printMonthSchedule(newScheduler);
}


char* getUserInput(void)
{
	char buffer[MAX_CHAR_SIZE] = "";
	char* userInput = NULL;
	char* newLinePos = NULL;

	fgets(buffer, sizeof(buffer), stdin);
	if ((newLinePos = strchr(buffer, '\n')) != NULL)
	{
		*newLinePos = '\0';
	}
	else
	{
		char clearStdinBuffer = '\0';
		do
		{
			clearStdinBuffer = getchar();
		} while (clearStdinBuffer != '\n' && clearStdinBuffer != EOF);
		printf("###CAUTION: Input is truncated to %c character\n", buffer[MAX_CHAR_SIZE - 2]);
	}

	userInput = (char*)malloc(strlen(buffer) + 1);
	if (userInput == NULL)
	{
		printf("Memory Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	strcpy(userInput, buffer);

	return userInput;
}


bool isValidDate(const char* date) 
{
	int year, month, day;
	if (sscanf(date, "%d-%d-%d", &year, &month, &day) == 3) 
	{
		int len = strlen(date);
		if (len == 10 && date[4] == '-' && date[7] == '-') // ex. 2023-11-23
		{
			if (year >= 1000 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31) 
			{
				return true;
			}
		}
	}
	return false;
}


char* getUserInputDate(void) 
{
	char* date = NULL;
	do 
	{
		date = getUserInput();
		if (!isValidDate(date)) 
		{
			printf("Invalid date format. Please enter the date in YYYY-MM-DD format: ");
			free(date);
			date = NULL;
		}
	} while (date == NULL);
	return date;
}


int getUserNumber(void)
{
	int userChoice = 0;
	char buffer[USER_NUMBERINPUT_BUFFER] = "";
	char* newLinePos = NULL;

	fgets(buffer, sizeof(buffer), stdin);

	if ((newLinePos = strchr(buffer, '\n')) != NULL)
	{
		*newLinePos = '\0';
	}

	if (sscanf(buffer, "%d", &userChoice) != 1)
	{
		printf("Please enter the correct format number\n");
		return false;
	}
	return userChoice;
}


char* appendReviewToExamName(const char* examName) 
{
	size_t newLength = strlen(examName) + strlen(" review") + 1;
	char* newExamName = (char*)malloc(newLength);
	if (newExamName == NULL) 
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	strcpy(newExamName, examName);
	strcat(newExamName, " review");

	return newExamName;
}


void loadTasksFromFile(nameSearchTable* nameTable, dateSearchTable* dateTable, assignmentNode** root, bool isExam) 
{
	printf("Enter file name: ");
	char* fileName = getUserInput();
	FILE* file = fopen(fileName, "r");
	if (!file) 
	{
		printf("Error opening file! Check the file path etc.\n");
		free(fileName);
		return;
	}

	char lineBuffer[LINE_BUFFER_FILE];
	while (fgets(lineBuffer, sizeof(lineBuffer), file) != NULL)
	{
		char name[MAX_CHAR_SIZE] = { 0 };
		char dueDate[USER_NUMBERINPUT_BUFFER] = { 0 };
		int time = 0;
		if (sscanf(lineBuffer, "%[^,],%[^,],%d", name, dueDate, &time) == 3)
		{
			// Process each task
			char* processedName = isExam ? appendReviewToExamName(name) : strdup(name);
			assignmentInfo* newAssign = createAssignmentInfo(processedName, dueDate, time);
			insertToNameSearchTable(nameTable, newAssign);
			insertToDateSearchTable(dateTable, newAssign);
			assignmentNode* newNode = createNode(processedName, dueDate, time);
			*root = insertNode(*root, newNode);
			free(processedName);
		}
	}

	fclose(file);
	free(fileName);
	printf("Tasks loaded successfully.\n");
}



