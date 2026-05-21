#include "shell.h"

/**
 * _atoi_exit - custom string to int for exit status
 * @s: string
 * @error: pointer to error flag
 * Return: integer status
 */
int _atoi_exit(char *s, int *error)
{
	unsigned long res = 0;
	int i = 0;

	*error = 0;
	if (!s)
		return (0);
	if (s[i] == '+')
		i++;
	for (; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			*error = 1;
			return (2);
		}
		res = res * 10 + (s[i] - '0');
	}
	return (res & 0xFF);
}

/**
 * handle_builtins - handles builtin commands
 * @args: parsed arguments
 * @line: input line
 * @av: main arguments
 * @last_status: status of the last executed command
 * Return: 1 if executed, 0 otherwise
 */
int handle_builtins(char **args, char *line, char **av, int *last_status)
{
	int status = 0, error = 0, i = 0;

	if (!args[0])
		return (0);
	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1])
		{
			status = _atoi_exit(args[1], &error);
			if (error)
			{
				write(STDERR_FILENO, av[0], _strlen(av[0]));
				write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
				write(STDERR_FILENO, args[1], _strlen(args[1]));
				write(STDERR_FILENO, "\n", 1);
				free(line);
				free_env();
				exit(2);
			}
			free(line);
			free_env();
			exit(status);
		}
		free(line);
		free_env();
		exit(*last_status);
	}
	if (_strcmp(args[0], "env") == 0)
	{
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}
	if (_strcmp(args[0], "cd") == 0)
    return (handle_cd(args, av, last_status));
	return (handle_env_builtins(args));
}
/**
 * handle_cd - changes the current working directory
 * @args: parsed arguments (args[1] is the target directory)
 * @av: main arguments (for error message prefix)
 * @last_status: pointer to last command's exit status
 * Return: 1 (always handled as a builtin)
 */
int handle_cd(char **args, char **av, int *last_status)
{
	char *target, *home, *oldpwd;
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	home = _getenv("HOME");
	oldpwd = _getenv("OLDPWD");
	if (args[1] == NULL)
		target = home;
	else if (_strcmp(args[1], "-") == 0)
		target = oldpwd;
	else
		target = args[1];
	if (target == NULL || chdir(target) != 0)
	{
		
	    write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
		if (args[1])
			write(STDERR_FILENO, args[1], _strlen(args[1]));
		write(STDERR_FILENO, "\n", 1);
		*last_status = 2;
		return (1);		

	}
	_setenv("OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		_setenv("PWD", cwd);
	return (1);
}

