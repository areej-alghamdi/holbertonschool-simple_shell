#ifndef SHELL_H
#define SHELL_H

/* Tasks 1, 2, 3 by abeer alsayari */ 
/* Tasks 4, 5, 6 by areej alghamdi */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void parse_command(char *line, char **args);
int execute_command(char **args, char **av, char *line);
char *find_path(char *command);
#endif
