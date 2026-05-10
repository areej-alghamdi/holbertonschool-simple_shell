#include "shell.h"

/* Tasks 1, 2, 3 by abeer alsayari */

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line = NULL, *args[100], *token;
	size_t len = 0;
	ssize_t read_bytes;
	int i, status;
	pid_t child_pid;

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
		token = strtok(line, " ");
		if (!token)
			continue;
		i = 0;
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
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
	}
	free(line);
	return (0);
}
