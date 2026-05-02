# Task Manager

A command-line task manager written in C, using linked lists for data storage.

## Features

- Add, display, update and delete tasks
- Priority levels: LOW, MEDIUM, HIGH
- Status tracking: PENDING, IN_PROGRESS, DONE
- Data persistence via binary file
- Checksum validation for data integrity
- JSON export
- Statistics report

## Build
make

## Usage
./task_manager

## Project Structure

| File | Description |
|------|-------------|
| main.c | Entry point and menu logic |
| task.c | Task creation, display and deletion |
| task.h | Structures and function prototypes |
| utils.c | Checksum, file I/O, JSON export, stats |

## Author

Landry Kayita-Nkore  
B.Sc. Software Engineering — UQAM  
