#include"Schedule.h"

void generateSchedule(assignmentNode* assign, scheduler* scheduler)
{
    assignmentInfo* newAssign = createAssignmentInfo(assign->assignName, assign->dueDate, assign->estimateTime);
    int thisMonthMaxDate = getMaxDateOfCurrentMonth();

    while (newAssign->estimateTime != 0)
    {
        if (newAssign->estimateTime <= scheduler->month[scheduler->todayDate].remainingWorktime)
        {
            newAssign->next = scheduler->month[scheduler->todayDate].assign;
            scheduler->month[scheduler->todayDate].assign = newAssign;
            scheduler->month[scheduler->todayDate].remainingWorktime -= newAssign->estimateTime;
            if (scheduler->todayDate == thisMonthMaxDate) // meet end of month
            {
                scheduler->todayDate = 0;
            }
            break;
        }
        else if (scheduler->month[scheduler->todayDate].remainingWorktime > 0)
        {
            assignmentInfo* partialAssign = createAssignmentInfo(newAssign->assignName, newAssign->dueDate, scheduler->month[scheduler->todayDate].remainingWorktime);
            partialAssign->next = scheduler->month[scheduler->todayDate].assign;
            scheduler->month[scheduler->todayDate].assign = partialAssign;
            newAssign->estimateTime -= scheduler->month[scheduler->todayDate].remainingWorktime;

            scheduler->month[scheduler->todayDate].remainingWorktime = 0;
            scheduler->todayDate++;
            if (scheduler->todayDate == thisMonthMaxDate)
            {
                scheduler->todayDate = 0;
            }
        }
        else if (scheduler->month[scheduler->todayDate].remainingWorktime == 0)
        {
            scheduler->todayDate++;
            if (scheduler->todayDate == thisMonthMaxDate)
            {
                scheduler->todayDate = 0;
            }
        }
        
    }
}


void generateMonthSchedule(assignmentNode* root, scheduler* scheduler)
{
    if (root == NULL)
    {
        return;
    }
    generateMonthSchedule(root->leftChild, scheduler->month);
    generateSchedule(root, scheduler->month);
    generateMonthSchedule(root->rightChild, scheduler->month);
}


struct tm* getTodayDate(void)
{
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    return local;
}


int isLeapYear(int year) 
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    }
    else {
        return 0;
    }
}


int getMaxDateOfCurrentMonth(void) 
{
    struct tm* today = getTodayDate();
    int month = today->tm_mon + 1; 
    int year = today->tm_year + 1900;

    switch (month) 
    {
    case 2:
        return isLeapYear(year) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}


void addExamToSchedule(assignmentNode* examRoot, scheduler* scheduler)
{
    if (examRoot == NULL)
    {
        return;
    }
    addExamToSchedule(examRoot->leftChild, scheduler->month);
    generateExamwithSchedule(examRoot, scheduler->month);
    addExamToSchedule(examRoot->rightChild, scheduler->month);
}


void generateExamwithSchedule(assignmentNode* exam, day month[])
{
    int dayBeforeExam = getDayBeforeIndex(exam->dueDate);
    assignmentInfo* newExam = createAssignmentInfo(exam->assignName, exam->dueDate, exam->estimateTime);
    newExam->next = month[dayBeforeExam].assign;
    month[dayBeforeExam].assign = newExam;
}


int getDayBeforeIndex(const char* dateStr)
{
    struct tm tmDate;
    if ( sscanf(dateStr, "%d-%d-%d", &tmDate.tm_year, &tmDate.tm_mon, &tmDate.tm_mday) == 3 )
    {
        return tmDate.tm_mday -1 -1;
    }
    printf("calculate the day before issue\n");
    return 1;
}


void printMonthSchedule(scheduler* scheduler)
{
    int size = getMaxDateOfCurrentMonth();
    struct tm* today = getTodayDate();

    for (int i = 0; i < size; i++)
    {
        printf("%d/%d\n", today->tm_mon + 1, i + 1);
        assignmentInfo* current = scheduler->month[i].assign;
        while (current)
        {
            printf("\Task: %s, Time: %d hours\n", current->assignName, current->estimateTime);
            current = current->next;
        }
    }
}


scheduler* initialScheduler(void)
{
    scheduler* newScheduler = (scheduler*)malloc(sizeof(scheduler));
    if (newScheduler == NULL)
    {
        printf("ERROR MEMORY ALLOCTION");
        return 1;
    }

    for (int i = 0; i < 31; i++)
    {
        newScheduler->month[i].assign = NULL;
        newScheduler->month[i].remainingWorktime = MAXWORKTIME;
    }
    newScheduler->todayDate = getTodayDate()->tm_mday - 1;

    return newScheduler;
}