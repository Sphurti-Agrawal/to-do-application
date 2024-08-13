# To-Do List Application in C

This is a simple command-line To-Do List application written in C. The application allows users to manage their tasks by adding new tasks, viewing existing tasks, deleting tasks, and marking tasks as complete. The tasks are stored in a text file so that they persist between sessions.

## Features

- **Add Task**: Add a new task with a description and priority level (High, Medium, Low).
- **View Tasks**: Display all tasks with their description, priority, and completion status.
- **Delete Task**: Remove a task from the list.
- **Mark Task Complete**: Mark a specific task as completed.
- **Persistent Storage**: Tasks are stored in a text file (`todolist.txt`) to ensure they are saved between sessions.

## File Structure

- `todolist.c`: The main C source file containing the implementation of the To-Do List application.
- `todolist.txt`: The text file where tasks are stored. This file is created automatically when tasks are added.

## Getting Started

### Prerequisites

To compile and run this program, you'll need:

- A C compiler (e.g., `gcc`)
- A terminal or command-line interface
- Visual Studio Code (or any text editor of your choice)

To run the code : write the following commands in terminal <br>
gcc .\tasks_manager.c <br>
.\a
