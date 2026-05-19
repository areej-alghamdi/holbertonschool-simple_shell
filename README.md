# Simple Shell

## Description
This project is a simple UNIX command language interpreter. It reads commands from either a file or standard input and executes them. It replicates basic functionalities of the `sh` shell, demonstrating a deep understanding of processes, system calls, and program execution. This project is a core part of the Holberton School curriculum.

## Features
* Displays a prompt and waits for user input.
* Executes standard commands (e.g., `/bin/ls`).
* Handles commands with arguments (e.g., `ls -l`).
* Implements `PATH` resolution (e.g., `ls` works without the full path).
* Handles the End-Of-File (EOF) condition (`Ctrl+D`).
* Handles the `SIGINT` signal (`Ctrl+C`) without terminating the shell.
* Supports both interactive and non-interactive modes.
* Returns proper exit status codes (e.g., `127` when a command is not found).
* **Built-in commands:**
  * `exit`: Exits the shell smoothly, with optional exit status.
  * `env`: Prints the current environment variables.
  * `setenv VARIABLE VALUE`: Sets a new environment variable or updates an existing one.
  * `unsetenv VARIABLE`: Removes an environment variable.

## Requirements
* Allowed editors: `vi`, `vim`, `emacs`
* All files will be compiled on Ubuntu 20.04 LTS
* Code must follow the Betty style and will be checked using `betty-style.pl` and `betty-doc.pl`
* No memory leaks are allowed
* All header files should be include guarded

## Compilation and Installation
To compile the shell, clone this repository and run the following command:

    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Examples

### Interactive Mode

    $ ./hsh
    ($) ls
    AUTHORS  man_1_simple_shell  README.md  shell.h  main.c
    ($) env
    USER=ubuntu
    LANGUAGE=en_US
    PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
    ($) exit
    $

### Non-Interactive Mode

    $ echo "ls" | ./hsh
    AUTHORS  man_1_simple_shell  README.md  shell.h  main.c
    $

## Authors
* Abeer Alsayari
* Alghamdi Areej
