#include "shell.h"

/* Tasks 1, 2, 3 by abeer alsayari */
/* Tasks 3, 4, 5 by areej alghamdi */

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
/**
 * execute_command - finds the command in PATH, forks, and executes it
 * @args: array of parsed arguments (args[0] is the command name)
 * @av: main argument vector for error messages
 * @line: input line to free on child error
 *
 * Description: Uses find_path to locate the command before forking.
 * If the command does not exist, prints an error and does NOT fork.
 *
 * Return: 0 on success, 1 on failure
 */
int execute_command(char **args, char **av, char *line)
{
	pid_t child_pid;
	int status;
	char *full_path;

	full_path = find_path(args[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
		return (127);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(full_path);
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror(av[0]);
			free(full_path);
			free(line);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(full_path);
	}
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
	int last_status = 0;

	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		read_bytes = getline(&line, &len, stdin);
		if (read_bytes == -1)
		{
			free(line);
			exit(last_status);
		}
		if (line[read_bytes - 1] == '\n')
			line[read_bytes - 1] = '\0';
		parse_command(line, args);
		if (args[0] == NULL)
			continue;
		last_status = execute_command(args, av, line);
	}
	free(line);
	return (0);
}
