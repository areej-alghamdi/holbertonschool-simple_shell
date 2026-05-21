#include "shell.h"

/**
 * handle_help - Implements the help builtin
 * @args: Command arguments
 *
 * Return: 1 on success
 */
int handle_help(char **args)
{
	char *str;

	if (!args[1])
		str = "help: help [BUILTIN]\n";
	else if (_strcmp(args[1], "cd") == 0)
		str = "cd: cd [dir]\n";
	else if (_strcmp(args[1], "exit") == 0)
		str = "exit: exit [n]\n";
	else if (_strcmp(args[1], "env") == 0)
		str = "env: env\n";
	else if (_strcmp(args[1], "setenv") == 0)
		str = "setenv: setenv [variable] [value]\n";
	else if (_strcmp(args[1], "unsetenv") == 0)
		str = "unsetenv: unsetenv [variable]\n";
	else if (_strcmp(args[1], "help") == 0)
		str = "help: help [BUILTIN]\n";
	else
	{
		write(STDERR_FILENO, "bash: help: no help topics match `", 34);
		write(STDERR_FILENO, args[1], _strlen(args[1]));
		write(STDERR_FILENO, "'\n", 2);
		return (1);
	}
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
