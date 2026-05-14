#include "shell.h"

/**
 * get_location - finds command path
 * @command: command string
 * Return: full path or NULL
 */
char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int cmd_len, dir_len;
	struct stat buffer;

	if (stat(command, &buffer) == 0)
		return (_strdup(command));
	path = _getenv("PATH");
	if (path)
	{
		path_copy = _strdup(path);
		if (!path_copy)
			return (NULL);
		cmd_len = _strlen(command);
		path_token = _strtok(path_copy, ":");
		while (path_token != NULL)
		{
			dir_len = _strlen(path_token);
			file_path = malloc(cmd_len + dir_len + 2);
			if (!file_path)
			{
				free(path_copy);
				return (NULL);
			}
			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			free(file_path);
			path_token = _strtok(NULL, ":");
		}
		free(path_copy);
	}
	return (NULL);
}

/**
 * execute_command - forks and executes
 * @args: arguments array
 * @av: main arguments
 * @line: input line
 * @last_status: pointer to update the exit status
 * Return: status
 */
int execute_command(char **args, char **av, char *line, int *last_status)
{
	pid_t child_pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL || handle_builtins(args, line, av, *last_status))
		return (0);

	cmd_path = get_location(args[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": 1: ", 5);
		write(STDERR_FILENO, args[0], _strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		*last_status = 127;
		return (127);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(av[0]);
			free(line);
			free(cmd_path);
			free_env();
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		free(cmd_path);
	}
	return (0);
}
