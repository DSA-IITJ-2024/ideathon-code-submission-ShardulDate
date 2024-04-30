[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/234bMY4A)

# Go to the folder "algorithm for engine" and run the workable.cpp

# Course Schedule Management System

This is a C++ program that manages course schedules for educational institutions. It allows users to input course data, allocate classrooms, and generate schedules based on various constraints.

## Features

- **Graph Coloring Algorithm:** Utilizes a graph coloring algorithm to assign time slots to courses while minimizing conflicts.
- **Room Allocation:** Automatically assigns available rooms to classes, ensuring optimal space utilization.
- **Dynamic Scheduling:** Users can add or remove courses and declare holidays dynamically, with the schedule adjusting accordingly.
- **Input from File:** Supports input of course data from a text file for ease of use.

## Usage

1. **Compile:** Compile the program using a C++ compiler. For example:
    ```
    g++ main.cpp -o schedule_manager
    ```
2. **Input Data:** Create an input file containing course data in the specified format.
3. **Run:** Execute the compiled program and follow the prompts to input the name of the input file and other necessary information.
4. **View Schedule:** The program will generate and display the course schedule with assigned room numbers.
5. **Manage Schedule:** Users can remove courses or declare holidays by following the on-screen instructions.

## Input File Format

The input file should contain the following information:

- Number of courses
- Course names
- Common students between courses (adjacency matrix representation)

Example:
4 DSA IML IC Maths 0 1 A 2 B C 3 D E F 2 G H 0


Issues:
Front end, engine and algorithm integration was giving last minute issues
