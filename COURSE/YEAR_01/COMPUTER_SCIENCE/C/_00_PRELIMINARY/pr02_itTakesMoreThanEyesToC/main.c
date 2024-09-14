/**
 * @desc
 * Write a C program to implement a complex task scheduling system. The program should 
 * allow users to create, update, delete, and view tasks. Each task should have a title, 
 * description, priority level, deadline, and status (e.g., pending, completed). The system 
 * should also support advanced scheduling features like task recurrence and dependency 
 * management (where one task depends on the completion of another).
 * 
 * @note
 * Use the `struct` keyword to define a `Task` structure that encapsulates all relevant 
 * information about each task, including dependencies on other tasks.
 * 
 * @note
 * Implement an efficient scheduling algorithm that takes into account task priorities, 
 * deadlines, and dependencies to determine the optimal order of task execution. The 
 * program should alert the user if a task cannot be scheduled due to dependency issues 
 * or conflicting deadlines.
 * 
 * @note
 * Use the `<time.h>` library to manage and calculate deadlines, recurring tasks, and 
 * task durations. The user should be able to set tasks to recur at specific intervals 
 * (e.g., daily, weekly, monthly) and the program should automatically generate the 
 * next occurrence of the task.
 * 
 * @note
 * Implement file management to save all tasks to a file and load them on program startup. 
 * Ensure that the file format is designed to handle task dependencies and recurrences 
 * effectively. Use binary files and index-based approaches to handle potentially large 
 * datasets.
 * 
 * @note
 * The program should include an interactive menu-driven interface that allows the user 
 * to perform all operations on the tasks. The interface should support advanced 
 * filtering and sorting options (e.g., sorting by deadline, priority, or status).
 * 
 * @note
 * Carefully manage memory, especially when dealing with dynamic arrays and linked 
 * structures that represent task dependencies. Ensure that tasks are properly 
 * deallocated when deleted, and handle circular dependencies gracefully.
 * 
 * @note
 * Implement input validation for all user inputs, including validation of date formats, 
 * priority levels, and task dependencies. Handle errors and edge cases, such as tasks 
 * with the same deadline but different priorities.
 */
