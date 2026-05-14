#ifndef SHELL_H
#define SHELL_H

/* Advanced Tasks: 100% Custom Functions by Abeer Alsayari */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* strings1.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);

/* strings2.c */
int is_delim(char c, const char *delim);
char *_strtok(char *str, const char *delim);
char *_getenv(const char *name);

/* builtins.c */
int _atoi_exit(char *s, int *error);
int handle_builtins(char **args, char *line, char **av);

/* exec.c */
char *get_location(char *command);
int execute_command(char **args, char **av, char *line);

/* main.c */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void parse_command(char *line, char **args);

#endif
