#ifndef SHELL_H
#define SHELL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>

#define MAX_INPUT_LENGTH 100

int odd(int n);
void execute_command(char *command);
int main(void);
char *get_input(void);
void exit_shell(void);


#endif
