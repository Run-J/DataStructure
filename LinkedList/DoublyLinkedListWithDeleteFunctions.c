#include <stdio.h>
#include <stdlib.h>

struct Student {
    int StudentId;
    int Age;
    struct Student* PreviousStudent;
    struct Student* NextStudent;
} temp;

void InsertNewHead(struct Student** head, struct Student** tail, int studentId, int age);
void InsertNewTail(struct Student** head, struct Student** tail, int studentId, int age);

void PrintList(struct Student* head);
void FreeList(struct Student* head);
struct Student* CreateNewNode(int studentId, int age);
void DeleteHead(struct Student** head, struct Student** tail);

void DeleteHead(struct Student** head, struct Student** tail){
    if(*head == NULL){
        printf("List is Empty");
        return;
    }
    
    struct Student* temp = *head;
    *head = (*head)->NextStudent;
    
    if(*head != NULL){
        (*head)->PreviousStudent = NULL;
        
    } else {
        *tail = NULL;
    }
    
    free(temp);
}

void DeleteTail(struct Student** head, struct Student** tail){
    if(*tail == NULL){
        printf("List is Empty");
        return;
    }
    
    struct Student* temp = *tail;
    *tail = (*tail)->PreviousStudent;
    
    if(*tail != NULL){
        (*tail)->NextStudent = NULL;
        
    } else {
        *head = NULL;
    }
    
    free(temp);
}

struct Student* CreateNewNode(int studentId, int age){
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    
    if(newStudent == NULL){
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }
    
    newStudent->StudentId = studentId;
    newStudent->Age = age;
    newStudent->NextStudent = NULL;
    newStudent->PreviousStudent = NULL;

    return newStudent;
}


void FreeList(struct Student* head){
    
    struct Student* current = head;
    struct Student* tempNode;
    
    while (current != NULL) {
        tempNode = current->NextStudent;
        free(current);
        current = tempNode;
    }
    
}


void PrintList(struct Student* head){
    struct Student* current = head;
    while(current != NULL){
        printf("StudentId: %d, Age:%d\n", current->StudentId, current->Age);
        printf("-------------\n");
        current = current->NextStudent;
    }
}

void InsertNewHead(struct Student** head, struct Student** tail, int studentId, int age){
    struct Student* newStudent = CreateNewNode(studentId, age);
    
    if(*head == NULL){
        *head = newStudent;
        *tail = newStudent;
        return;
    }
    
    newStudent->NextStudent = *head;
    (*head)->PreviousStudent = newStudent;
    *head = newStudent;
}

void InsertNewTail(struct Student** head, struct Student** tail, int studentId, int age){
    struct Student* newStudent = CreateNewNode(studentId, age);
    
    if(*tail == NULL){
        *tail = newStudent;
        *head = newStudent;
        return;
    }
    
    newStudent->PreviousStudent = *tail;
    (*tail)->NextStudent = newStudent;
    *tail = newStudent;
}

int main(void) {
    struct Student* head = NULL;
    struct Student* tail = NULL;
    
    InsertNewHead(&head, &tail, 3, 10);
    InsertNewHead(&head, &tail, 2, 20);
    InsertNewHead(&head, &tail, 1, 30);
    InsertNewTail(&head, &tail, 4, 40);
    
    DeleteHead(&head, &tail);
    DeleteTail(&head, &tail);
    
    PrintList(head);
    
    FreeList(head);
    return 0;
}
