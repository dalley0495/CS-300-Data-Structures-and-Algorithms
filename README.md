CS 300: Data Structures and Algorithms

This repository contains work from my CS 300 Data Structures and Algorithms course. The artifacts included demonstrate my ability to analyze data structures and use them to solve a programming problem in C++.

Reflection
What was the problem you were solving in the projects for this course?

The goal of the projects was to create an advising assistance program for the Computer Science department at ABCU. The program needed to read course information from a file, store the courses in an appropriate data structure, display all courses in alphanumeric order, and allow an academic advisor to search for an individual course and view its prerequisites. In Project One, I designed and analyzed solutions using a vector, hash table, and binary search tree. In Project Two, I implemented the final program in C++ using a binary search tree.

How did you approach the problem? Why are data structures important to understand?

I approached the problem by first considering how each data structure would handle loading, searching, storing, and displaying course information. I compared the runtime and memory requirements of vectors, hash tables, and binary search trees before selecting a binary search tree for the final program. Understanding data structures is important because the structure chosen for a program can have a major impact on how efficiently the program performs different operations. For this project, the binary search tree was useful because an in-order traversal could display the courses in alphanumeric order while still supporting course searches.

How did you overcome roadblocks you encountered?

One of the challenges was making sure the course data was loaded and parsed correctly from the CSV file while also handling courses with different numbers of prerequisites. I worked through the problem by breaking the program into smaller functions and testing each part individually. I first made sure the project compiled, then tested loading the data, printing the complete course list, searching for individual courses, handling invalid course numbers, and preventing users from accessing course information before the data was loaded. Testing one feature at a time made it easier to identify and correct problems.

How has this work expanded your approach to designing software and developing programs?

This project helped me see the value of designing a solution before immediately beginning to code. Comparing multiple data structures in Project One made me think about how design decisions affect the final implementation. I now pay more attention to the operations a program needs to perform and consider which algorithms and data structures are best suited for those requirements instead of simply choosing the first solution that works.

How has this work evolved the way you write maintainable, readable, and adaptable programs?

My approach to writing code has become more organized. In Project Two, I separated responsibilities into functions for loading course data, searching for courses, printing course information, and traversing the binary search tree. I also used descriptive names, comments, input validation, and consistent formatting. Breaking a program into smaller pieces makes the code easier to read, test, maintain, and modify later. This project reinforced that readable code is important not only for other developers but also for being able to return to my own work and quickly understand how it functions.

Portfolio Artifacts
ProjectOne_Runtime_and_Memory_Analysis.docx — Runtime, memory, and data structure analysis from Project One.
ProjectTwo.cpp — C++ advising assistance program that loads course data into a binary search tree, prints courses in alphanumeric order, and displays individual course and prerequisite information.
