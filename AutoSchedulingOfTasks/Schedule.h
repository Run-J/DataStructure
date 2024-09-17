#pragma once

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"Hash.h"
#include"BST.h"

#pragma warning(disable: 4996)

#define MAXWORKTIME 6 // hours

typedef struct day
{
    assignmentInfo* assign;
    int remainingWorktime;
}day;

typedef struct scheduler
{
    day month[31];
    int todayDate;
} scheduler;

struct tm* getTodayDate(void);
int getMaxDateOfCurrentMonth(void);
int isLeapYear(int year);
void generateSchedule(assignmentNode* assign, scheduler* scheduler);
void printMonthSchedule(scheduler* scheduler);
void generateMonthSchedule(assignmentNode* root, scheduler* scheduler);
void addExamToSchedule(assignmentNode* examRoot, scheduler* scheduler);
void generateExamwithSchedule(assignmentNode* exam, day month[]);

scheduler* initialScheduler(void);
