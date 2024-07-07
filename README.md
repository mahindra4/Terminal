# Linux Terminal Emulator

This project is a Linux Terminal Emulator developed using C++. It mimics basic functionalities of a Linux terminal, allowing users to execute commands and manage files within a simulated file system environment.

## Features

- **Command Execution:** Supports basic Linux commands such as `ls`, `cd`, `mkdir`, `touch`, `rm`, `mv` and more.
- **File Management:** Allows users to create, delete, and navigate directories and files.
- **Command History:** Keeps a history of executed commands for easy reference and repetition.
- **User Interface:** Provides a command-line interface that closely resembles the actual Linux terminal.

## Technologies Used

- **C++:** The primary programming language used to develop the terminal emulator.
- **Standard Template Library (STL):** Utilized for data structures and algorithms.
- **System Calls:** Used for executing commands and managing files.

## Getting Started

To get a local copy up and running, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/linux_terminal_emulator.git
1. **Navigate to the project directory:**
   ```bash
   cd linux_terminal_emulator
1. **Compile the project:**
   ```bash
   g++ terminal.cpp main.cpp -o terminal
1. **Run the terminal emulator:**
   ```bash
   ./terminal
