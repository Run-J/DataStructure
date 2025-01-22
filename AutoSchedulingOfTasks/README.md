# Time Management Assistant Tool

## Overview
A command-line tool designed to generate daily schedules based on user-defined working hours, task durations, and deadlines. Users can manually add tasks or load them from a file, enabling auto-scheduling for efficient time allocation.

---

## Creative Inspiration
In my daily studies, managing assignments, tests, previews, and reviews often becomes overwhelming. To address this, I created an assistant tool to efficiently plan my study schedule and assignments.

### How It Works:
- Users provide task details such as:
  - Assignment name, estimated time required, and due date.
  - Exam dates and difficulty levels (easy = 1 hour, average = 2 hours, difficult = 3 hours).
- The tool:
  - Automatically distributes tasks across days based on user-defined daily working hours.
  - Schedules exam reviews for the day before each exam.

This system eliminates the need for manual planning by organizing tasks efficiently and automatically generating a plan for task completion.

---

## Key Features
1. Built on Linux using **GCC**, **GDB**, and **Makefile** for streamlined builds and debugging.
2. Leverages **optimized data structures** (e.g., BST, hash tables, stacks, linked lists) for task management and time complexity improvements.

---

## How Data Structures Are Used

### Goal and Data Structure Selection

The program's goal is to **optimize time complexity**. Key requirements include:
- **Sorting tasks by date** to list all current tasks.
- **Searching for task details** by name.
- **Searching for tasks on a specific date.**
- **Inserting new tasks** and **deleting completed tasks.**
- **Generating a schedule** based on tasks.

To meet these requirements efficiently, the following **data structures** are used:

### **1. Hash Table + Linked List**
- **Purpose:**  
  Used for **searching task details by name** and **retrieving tasks by date**, as well as for insertion and deletion.
- **Why Hash Table:**  
  - Provides **O(1)** time complexity for insertions and lookups using **key-value pairs**.
  - Inefficient for sorting, so a **BST** is used for that purpose.
- **Collision Handling:**  
  - **Separate Chaining:** Uses **linked lists** to store multiple tasks that hash to the same index.

### **2. BST + Recursion (Default Option)**  
- **Purpose:**  
  Used to **sort tasks by date** and **list them in ascending order of due dates**.
- **Why Recursion:**  
  - Provides straightforward and **readable code** for **in-order traversal**.
  - Suitable for trees of moderate depth where stack overflow is unlikely.

#### **2.1. Iterative + Manual Stack (Optional Alternative)**
- **Purpose:**  
  An alternative to recursion for **in-order traversal** in cases where the tree depth is very large.
- **Advantages:**
  - **Prevents stack overflow** for deep trees.
  - Offers better control over the traversal process.
- **Trade-offs:**
  - May increase code complexity compared to recursion.
  - Avoids the overhead of recursive function calls.

### **3. Array + Linked List**
- **Purpose:**  
  Implements the **scheduler**, where tasks and exams are organized by day.
- **Structure:**
  - **Array:** Represents up to 31 days in a month for **O(1)** access to specific days.
  - **Linked List:** Dynamically stores tasks for each day, supporting varying workloads.
- **Benefits:**  
  - Combines **efficient access** with **dynamic task storage.**
  - Ensures **flexible scheduling** and task retrieval while maintaining daily work limits.

This structure ensures the program achieves **optimal time complexity** while addressing the specific requirements efficiently.

---

## Demo


---

## Technology
- **Languages:** C
- **Tools:** GCC, GDB, Makefile
- **Data Structures:** Hash Table, Linked List, BST, Manual Stack

---

## Known Limitations
1. **Inefficient BST Insertion:**  
   If tasks are inserted in order, the BST can degrade to a linked list, reducing efficiency. Switching to a self-balancing tree (e.g., AVL, Red-Black Tree) can improve performance.
2. **Validation Issues:**  
   - Review scheduling for exams may conflict with task deadlines, leading to delays.
   - Incorrectly formatted input files (e.g., punctuation errors) can cause errors.
3. **Improved Validation Needed:**  
   Better validation mechanisms are required for document parsing and task scheduling.
