#include "shell.h"

/* Tasks 1, 2, 3 by abeer alsayari */

/**
 * parse_command - tokenizes the input line into arguments
 * @line: the input line string
 * @args: array to store the tokens
 */
void parse_command(char *line, char **args)
{
	char *token;
	int i = 0;

	token = strtok(line, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

/**
 * execute_command - forks and executes the command
 * @args: array of parsed arguments
 * @av: main argument vector for error printing
 * @line: input line to free on error
 *
 * Return: 1 if failed, 0 on success
 */
int execute_command(char **args, char **av, char *line)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(av[0]);
			free(line);
			exit(127);
		}
	}
	else
		wait(&status);
	return (0);
}

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line = NULL, *args[100];
	size_t len = 0;
	ssize_t read_bytes;

	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		read_bytes = getline(&line, &len, stdin);
		if (read_bytes == -1)
		{
			free(line);
			exit(0);
		}
		if (line[read_bytes - 1] == '\n')
			line[read_bytes - 1] = '\0';
		parse_command(line, args);
		if (args[0] == NULL)
			continue;
		execute_command(args, av, line);
	}
	free(line);
	return (0);
}
