//Filename: taskManager.c
//Project: Console Based Task Manager
//Programmer: Run Ji; 
//First version: 01/29/2024
// Description: Build a console-based task management system using linked lists and structs with dynamic memory allocation in C.
//			Add Task : Users can choose to add a new task from the head or tail of the task list.
//						To add a task, the user needs to enter the ID, title and description of the task.
//			Delete Task : Users can delete a specific task by entering the ID of the task.
//			Find Task : Users can find a task by entering the index of the task and display the details of that task.
//			Print All Tasks : Users can print out all the tasks in the current task list and their details.
//			Exit Program : User can choose to exit the program.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996)

#define USERCHOICEBUFFER 10
#define USERSTRINGBUFFER 512
#define TITLESIZE 50
#define DESCRIPTIONSIZE 512
#define SUCCESS 1
#define FAILURE 0

typedef struct task
{
	int taskId;
	char* title;
	char* description;
	struct task* nextTask;
}task;

void displayMenu(void);
int getUserNumber(void);
char* getUserString(void);
task* initTask(void);
void headAddTask(task* headNode, int taskId, const char* title, const char* description);
void tailAddTask(task* headNode, int taskId, const char* title, const char* description);
void printTask(task* headNode);
void findTaskByIndex(task* headNode, int index);
void deleteTaskByTaskId(task* headNode, int taskId);

int main(void)
{
	// Display a menu and let the user choose what they want to do.
	task* newTaskList = initTask();
	
	// Calls the appropriate function according to the user's selection. When the user selects 5, running becomes 0.
	int running = 1;
	while (running)
	{
		displayMenu();
		printf("\nPlease choose what you want to do: ");
		int userChoice = getUserNumber();
		if (userChoice == FAILURE) 
		{
			printf("Invalid input. Please try again.\n");
			continue; // Skips the remainder of the current loop and restarts the loop
		}

		switch (userChoice)
		{
		case 1:
			printf("Press 1 to insert from the head, press 2 to insert from the tail: ");
			int addChoice = getUserNumber();
			if (addChoice == FAILURE)
			{
				printf("Invalid input. Please try again.\n");
				break; // Skips the remainder of the current loop and restarts the loop
			}
			const char* userTaskTitle = NULL;
			const char* userTaskDescription = NULL;
			if (addChoice == 1) // head insert
			{
				printf("\nAdding a task...\n");
				printf("Enter taskId: ");
				int taskId = getUserNumber(); // ask user to input task id 
				if (taskId == FAILURE)
				{
					printf("Invalid input. Please try again.\n");
					break; // Skips the remainder of the current loop and restarts the loop
				}
				printf("Enter taskTitle: ");
				userTaskTitle = getUserString(); // ask user to input task title

				printf("Enter taskDescription: ");
				userTaskDescription = getUserString();  // ask user to input task description

				headAddTask(newTaskList, taskId, userTaskTitle, userTaskDescription);

				free(userTaskTitle);
				free(userTaskDescription);
				break;
			}
			else if (addChoice == 2) // tail insert
			{
				printf("\nAdding a task...\n");
				printf("Enter taskId: ");
				int taskId = getUserNumber(); // ask user to input task id 

				printf("Enter taskTitle: ");
				userTaskTitle = getUserString(); // ask user to input task title

				printf("Enter taskDescription: ");
				userTaskDescription = getUserString();  // ask user to input task description

				tailAddTask(newTaskList, taskId, userTaskTitle, userTaskDescription);

				free(userTaskTitle);
				free(userTaskDescription);
				break;
			}
			else
			{
				printf("##ERROR: valid choose, only 1 or 2\n");
			}
			break;

		case 2:
			printf("\nDeleting a task...\n");
			printf("Enter taskId: ");
			int taskId = getUserNumber();
			deleteTaskByTaskId(newTaskList, taskId);
			break;

		case 3:
			printf("\nFinding a task...\n");
			printf("Enter index: ");
			int index = getUserNumber();
			findTaskByIndex(newTaskList, index);
			break;

		case 4:
			printf("\nPrinting tasks...\n");
			printTask(newTaskList);
			break;

		case 5:
			printf("\nExiting...\n");
			running = 0;
			break;

		default:
			printf("Invalid choice, please try again.\n");
		}
	}

	/* delete following after test
	headAddTask(newTaskList, 101, "assignment 1", "This is first assignment");
	headAddTask(newTaskList, 102, "assignment 2", "This is second assignment");
	headAddTask(newTaskList, 103, "assignment 3", "This is third assignment");

	tailAddTask(newTaskList, 104, "assignment 4", "This is fourth assignment");
	tailAddTask(newTaskList, 105, "assignment 5", "This is fifth assignment");
	tailAddTask(newTaskList, 106, "assignment 6", "This is sixth assignment");
	printTask(newTaskList);

	task* foundTask = findTaskByIndex(newTaskList, 3);

	deleteTaskByTaskId(newTaskList, 102);
	printTask(newTaskList);*/

	return 0;
}


// Function: displayMenu
// Parameter: None
// Return Value: void
// Description: print the menu

void displayMenu(void) 
{
	printf("*******Menu*******\n");
	printf("Press 1 to Add Task\n");
	printf("Press 2 to Delete Task\n");
	printf("Press 3 to Find Task\n");
	printf("Press 4 to Print Tasks\n");
	printf("Press 5 to Exit\n");
	printf("******************\n");
}


// Function: getUserString
// Parameter: None
// Return Value: char* - user's input string or NULL
// Description: GetUser input string

char* getUserString(void)
{
	char buffer[USERSTRINGBUFFER] = "";
	if (fgets(buffer, sizeof(buffer), stdin) != NULL)
	{
		// remove \n from fgets
		char* newlinePos;
		if ((newlinePos = strchr(buffer, '\n')) != NULL) {
			*newlinePos = '\0';
		}

		// create a space for user input string
		char* input = (char*)malloc(strlen(buffer) + 1); // 1 for '\0'
		if (input == NULL)
		{
			printf("##ERROR: Memory allocation failed\n");
			return NULL;
		}

		strcpy(input, buffer);
		return input;
	}
	else
	{
		printf("##ERROR: Failed to get string input\n");
		return NULL;
	}

}


// Function: getUserNumber
// Parameter: None
// Return Value: int - FAILURE value, or user input number
// Description: GetUser input number

int getUserNumber(void)
{
	int userChoice = 0;
	char buffer[USERCHOICEBUFFER] = "";
	fgets(buffer, sizeof(buffer), stdin);
	if (sscanf(buffer, "%d", &userChoice) != 1)
	{
		printf("Please enter the correct format (number 1-5)");
		return FAILURE;
	}
	return userChoice;
}


// Function: initTask
// Parameter: None
// Return Value: 
//	   task* - The address pointing to the head node.
// Description:
//     Initialize a head node, which is not used to store data. It is used to make it easier to manage the linked list.

task* initTask(void)
{
	task* node = (task*)malloc(sizeof(task));
	if (node == NULL)
	{
		printf("##ERROR: Dynamic memory alloction failure\n");
		exit(FAILURE);
	}
	node->taskId = 0;
	node->title = (char*)malloc(sizeof(char) * TITLESIZE);
	node->description = (char*)malloc(sizeof(char) * DESCRIPTIONSIZE);
	node->nextTask = NULL;

	return node;
}


// Function: headAddTask
// Parameter:
//    task* headNode - Pointer to the head node of the task list.
//    int taskId - The user passes in the taskId by calling the function
//    const char* title - The user passes in the task title by calling the function
//    const char* description - The user passes in the task description by calling the function
// Return Value: None
// Description:
//    This headAddTask function is used to add a new task to the beginning of the task list. It first allocates memory for the new task,
//    then allocates memory for the task's title and description, and copies the given title and description into the newly allocated memory.
//    The new task is inserted right after the head node, becoming the first element in the list.

void headAddTask(task* headNode,int taskId, const char* title, const char* description)
{
	task* newTask = (task*)malloc(sizeof(task));
	if (newTask == NULL)
	{
		printf("##ERROR: Dynamic memory alloction failure\n");
		exit(FAILURE);
	}
	newTask->taskId = taskId;
	newTask->title = (char*)malloc(sizeof(char) * TITLESIZE);
	if (newTask->title == NULL)
	{
		printf("##ERROR: Dynamic memory alloction failure\n");
		exit(FAILURE);
	}
	newTask->description = (char*)malloc(sizeof(char) * DESCRIPTIONSIZE);
	if (newTask->description == NULL)
	{
		printf("##ERROR: Dynamic memory alloction failure\n");
		exit(FAILURE);
	}
	strcpy(newTask->title, title);
	strcpy(newTask->description, description);
	newTask->nextTask = headNode->nextTask;
	headNode->nextTask = newTask;
}


// Function: tailAddTask
// Parameter:
//    task* headNode - Pointer to the head node of the task list.
//    int taskId - The user passes in the taskId by calling the function
//    const char* title - The user passes in the task title by calling the function
//    const char* description - The user passes in the task description by calling the function
// Return Value: None
// Description:
//    This tailAddTask function creates a new task to be added after the last node in the link list. 
//	  First, find the last node by while loop. Then allocate memory for the new task as well as title and description, 
//    and finally, using the strcpy, assign the parameters passed by the user through the function call to the title and description.

void tailAddTask(task* headNode, int taskId, const char* title, const char* description)
{
	task* temp = headNode;
	while (temp->nextTask != NULL) // "temp" will point to the last node of linked list after while loop finish
	{
		temp = temp->nextTask;
	}

	task* newTask = (task*)malloc(sizeof(task));
	if (newTask == NULL)
	{
		printf("##ERROR: Dynamic memory alloction failure\n");
		exit(FAILURE);
	}

	newTask->taskId = taskId;
	newTask->title = (char*)malloc(sizeof(char) * TITLESIZE);
	if (newTask->title == NULL)
	{
		printf("##ERROR: Dynamic memory alloction failure\n");
		exit(FAILURE);
	}
	newTask->description = (char*)malloc(sizeof(char) * DESCRIPTIONSIZE);
	if (newTask->description == NULL)
	{
		printf("##ERROR: Dynamic memory alloction failure\n");
		exit(FAILURE);
	}
	strcpy(newTask->title, title);
	strcpy(newTask->description, description);
	
	newTask->nextTask = NULL;
	temp->nextTask = newTask;
}


// Function: printTask
// Parameter:
//	  task* headNode - Pointer to the head node of the task list.
// Return Value: None
// Description: 
//     This function starts by looping through the first node of the linked list (the next one in the head node) 
//     and prints its contents if it is not empty.

void printTask(task* headNode)
{
	task* current = headNode->nextTask;
	while (current != NULL)
	{
		printf("Task ID: %d\n", current->taskId);
		printf("Title: %s\n", current->title);
		printf("Description: %s\n", current->description);
		printf("\n");
		current = current->nextTask;
	}
}


// Function: findTaskByIndex
// Parameters:
//     task* headNode - Pointer to the head node of the task linked list.
//     int index - The index of the task to find in the linked list.
// Return Value: 
//	   task* - Returns a pointer to the task found at the specified index in the linked list. 
//     Returns NULL if no task is found at that index.
// Description: 
//	   Iterates through the task linked list starting from the node after the head node. It prints and returns the task at the specified index. 
//	   If no task is found at that index, it prints an error message and returns NULL.

void findTaskByIndex(task* headNode, int index)
{
	int indexCount = 0;
	task* current = headNode->nextTask;
	while (current != NULL)
	{
		if (indexCount == index)
		{
			printf("Founded index %d task: TaskId: %d, TaskTitle: %s, TaskDescription: %s\n\n", index, current->taskId, current->title, current->description);
			return;
		}
		indexCount++;
		current = current->nextTask;
	}
	printf("##ERROR: No task found\n\n");
}


// Function: deleteTaskByTaskId
// Parameters:
//     task* headNode - Pointer to the head node of the task linked list.
//     int taskId - The ID of the task to delete from the linked list.
// Return Value: None. Prints a message indicating whether the deletion was successful or not.
// Description: 
//		Iterates through the task linked list starting from the node after the head node, 
//		looking for a task with the specified taskId. If found, the task is removed from the list, 
//		its memory is freed, and a success message is printed. If the task is not found, an error message is printed.

void deleteTaskByTaskId(task* headNode, int taskId)
{
	task* pre = headNode;
	task* current = headNode->nextTask;
	while (current != NULL)
	{
		if (current->taskId == taskId)
		{
			pre->nextTask = current->nextTask;
			free(current->title);
			free(current->description);
			free(current);
			printf("Delete %d Successfully.\n\n", taskId);
			break;
		}
		current = current->nextTask;
		pre = pre->nextTask;
	}

	printf("Delete Failed. ##ERROR: No taskid found\n\n");
}
