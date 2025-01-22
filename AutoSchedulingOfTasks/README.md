# Time Management Assistant Tool

## Overview
Designed a command-line tool to generate daily schedules based on user-defined working hours, task durations, and deadlines. Users can manually add tasks or load them from a file with auto-scheduling for efficient time allocation.

---

## Creative Inspiration
In my daily studies, I often have numerous assignments, tests, previews, and reviews to manage. Without a proper schedule, everything can become messy and overwhelming. To address this, I want to build a assistant tool that helps me efficiently plan my assignments and study schedule.

When faced with a large workload, I would like this tool to automatically generate a schedule based on the assignment details and test dates I provide. The input information can include the assignment name, estimated time or hours needed to complete it, and its due date. Additionally, I can input exam dates along with their difficulty level—easy exams are automatically scheduled for one hour of review, average exams for two hours, and difficult exams for three hours.

The scheduler will automatically distribute assignments across different days based on the daily working hours I define. Exam reviews will be scheduled on the day before the exam date to ensure proper preparation.

As a user, I only need to enter the tasks that need to be completed, and the program will handle the scheduling for me. This system eliminates the need to manually plan and ensures that everything is organized efficiently, automatically generating a plan for completing my tasks.

---

## Key Features
1. Built on Linux using GCC, GDB, and Makefile for streamlined builds.
2. Leveraged data structures (e.g., BST, hash tables, stacks, and linked lists) for optimized task management and improved time complexity.

---

## How Data Structures Be Used

---

## Demo

---

## Technology
C, Data Structures, Linux, GCC, GDB, Makefile

---

## Program vulnerable to what happens
1. If the time are inserted in order, it will become linkedlist, the insertion time will become less efficient, so I can choose to use more efficient tree, such as AVL, red balck
2. Validation is flawed, exam + review can continue to progress, automatically generated deadlines will lead to late.
3. Input of documents may be incorrect due to punctuationl Still need a better validation.
