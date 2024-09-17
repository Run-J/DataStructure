###What the program can do:
This program allows manual add/file entry to add things that need to be done and then use the program to perform CRUD operations, in addition the program can automatically generate a schedule based on the time available to be allocated each day.


###Data structure skills used by the program:
Two hash tables paired with linked lists, two BSTs, manual simulation of stack for iterate.
Special way to compute hash, using different binary tree traversal order.


###Program vulnerable to what happens
1. if the time are inserted in order, it will become linkedlist, the insertion time will become less efficient, so you can choose to use more efficient tree, such as AVL, red balck
2. validation is flawed, exam + review can continue to progress, automatically generated deadlines will lead to late
3. Input of documents may be incorrect due to punctuation.


###Project Background and Description:
In my daily studies, there will be very many assignments/tests/previews/reviews, etc. All these things will be messy if I don’t plan a perfect schedule. So, I want to build a small program that will help me to plan my assignments/studies schedule.


###Problem Statement:
If I have a lot of homework and studying to complete, I would like this program to automatically generate a schedule based on the assignment information/test dates I enter.

The information I enter can include the name of the assignment, the difficulty of the assignment (three difficulty levels easy, average, difficult), the estimated time/hours to complete, and the due date.
As well as the exam date and difficulty (easy exams are automatically scheduled for one hour, average for two hours, and difficult for three hours).

As a user, just enter the jobs that need to be done and no longer need to think about how to schedule them, the system will plan them according to the time. So, this program automatically helps me to generate a plan for job completion. 
