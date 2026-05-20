#include "shell.h"
/**
 * get_location - searches for a command in the PATH directories
 * @command: the name of the command to find (e.g. "ls")
 *
 * Description: If command contains a '/' or is in the current
 * directory, check it directly. Otherwise, split PATH by ':' and
 * search each directory until an executable file is found.
 *
 * Return: full path string (must be freed by caller), or NULL
 * if not found or not executable.
 */

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int cmd_len, dir_len;


	if (strchr(command, '/') != NULL)
        {
                if (access(command, X_OK) == 0)
                        return (_strdup(command));
                return (NULL);
        }
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
			if (access(file_path, X_OK) == 0)
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
 * execute_command - forks and executes a command in a child process
 * @args: NULL-terminated array of arguments (args[0] is the command)
 * @av: main argument vector (used for error message prefix)
 * @line: input line buffer to free on child error
 * @last_status: pointer to last command's exit status (updated here)
 *
 * Description: Handles built-in commands first. If not a builtin,
 * finds the command path using get_location, forks, and executes.
 * Prints an error and updates last_status to 127 if not found.
 *
 * Return: 0 on success or builtin handled, 127 if command not found
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

/**
 * parse_command - splits an input line into tokens (arguments)
 * @line: the input string to tokenize (modified in place)
 * @args: array to store the resulting token pointers
 *
 * Description: Uses _strtok with space, tab, and newline as
 * delimiters. The last element of args is set to NULL so it can
 * be passed directly to execve.
 */

void parse_command(char *line, char **args)
{
	char *token;
	int i = 0;

	token = _strtok(line, " \n\t");
	while (token != NULL)
	{
		args[i++] = token;
		token = _strtok(NULL, " \n\t");
	}
	args[i] = NULL;
}
