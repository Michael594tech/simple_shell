0x16. C - Simple Shell

This is a README.md file which describes the simple shell project
ALX Simple_Shell Project

Description:

This repository contains my implementation of the simple_shell function in C as part of the ALX School curriculum. My simple_shell function is capable of handling the following:

Display a prompt and wait for the user to type a command.
A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word.
No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
Compilation:

To compile our simple_shell function, use the following command:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

This will compile all C source files in the current directory and produce an expected outcome.

Author:

Michael Tonga
