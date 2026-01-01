# Simple Shell - Holberton School

## Project Overview

This project implements a simple UNIX command interpreter in C, inspired by the Thompson shell and `/bin/sh`.

The shell:

- Reads commands from standard input (interactive mode) or from a pipeline/file (non-interactive mode).
- Parses the command line into tokens (command + arguments).
- Resolves the command using the PATH environment variable (or uses an absolute/relative path directly).
- Creates a new process to execute the command (when appropriate).
- Waits for the command to finish, then prompts for the next one.

This is part of the Holberton School low-level programming curriculum.

---

## Features

- Display a prompt when in interactive mode:
  - Example: `#cisfun$ `
- Read and execute commands line by line.
- Support for commands with arguments:
  - Example: `ls -l /tmp`
- Use the `PATH` environment variable to find executables:
  - Example: `ls` resolves to `/bin/ls` (or similar).
- Support absolute and relative paths:
  - `/bin/ls`, `./a.out`, etc.
- Do **not** call `fork` if the command does not exist.
- Handle end-of-file (EOF), e.g. `Ctrl+D`.
- Proper error handling and exit codes.
- Works in:
  - Interactive mode
  - Non-interactive mode (e.g. `echo "ls" | ./hsh`)

### Built-in Commands

- `exit`  
  Exits the shell.  
  No arguments are handled in this version.

- `env`  
  Prints the current environment, one variable per line.

---

## Learning Objectives

By working on this project, we learned to:

- Explain who designed and implemented the original UNIX operating system.
- Explain who wrote the first UNIX shell.
- Explain who invented the B language (predecessor to C).
- Explain who Ken Thompson is.
- Describe how a shell works internally.
- Understand what PID and PPID are.
- Manipulate the environment of the current process.
- Distinguish between a function and a system call.
- Create processes using `fork`.
- Use the different prototypes of `main`.
- Use the `PATH` to locate executables.
- Execute another program using `execve`.
- Suspend execution until one of the children terminates (`wait`, `waitpid`).
- Understand EOF ("end-of-file") and how to handle it.

---

## How It Works (High-Level)

1. **Prompt**  
   If the input is from a terminal (`isatty`), print the shell prompt.

2. **Read Input**  
   Use `getline` to read a full line from standard input.

3. **Trim and Tokenize**  
   - Remove leading/trailing spaces.
   - Use `strtok` to split the line into tokens:
     - `args[0]` = command
     - `args[1..n]` = arguments

4. **Handle Built-ins**
   - If the command is `exit`, the shell terminates.
   - If the command is `env`, the shell prints the environment.

5. **Resolve Command**
   - If the command contains `/`, treat it as a path and check if it is executable.
   - Otherwise, search for the command in the directories listed in `PATH`.

6. **Execute Command**
   - If the command is found:
     - Call `fork` to create a child process.
     - In the child, call `execve`.
     - In the parent, call `waitpid` to wait for the child.
   - If the command is not found:
     - Print an error of the form:
       - `./hsh: <command_number>: <command>: not found`
     - Do **not** call `fork`.

7. **Loop**
   - Read the next command until EOF or `exit`.

---

## Compilation

The shell is compiled using:

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---
## File Structure 
```
holbertonschool-simple_shell
├── main.c
├── shell.c
├── prompt.c
├── shell.h
├── AUTHORS
├── man_1_simple_shell
└── README.md
```
----
## Authors

Solaf Alessa 
Hanin Al Sayed Hassan



