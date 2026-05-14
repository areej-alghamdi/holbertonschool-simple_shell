#include "shell.h"

/**
 * match_env_name - matches environment variable name
 * @env_var: environment variable string
 * @name: name to match
 * Return: 1 if match, 0 otherwise
 */
int match_env_name(char *env_var, char *name)
{
	int j = 0;

	while (name[j] && env_var[j] == name[j])
		j++;
	if (name[j] == '\0' && env_var[j] == '=')
		return (1);
	return (0);
}

/**
 * _setenv - sets an environment variable
 * @name: variable name
 * @value: variable value
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *name, char *value)
{
	int i = 0, len = 0;
	char *new_var, **new_env;

	if (!name || !value)
		return (-1);
	new_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (!new_var)
		return (-1);
	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);
	while (environ[i])
	{
		if (match_env_name(environ[i], name))
		{
			free(environ[i]);
			environ[i] = new_var;
			return (0);
		}
		i++;
	}
	while (environ[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	for (i = 0; i < len; i++)
		new_env[i] = environ[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(environ);
	environ = new_env;
	return (0);
}

/**
 * _unsetenv - removes an environment variable
 * @name: variable name
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(char *name)
{
	int i = 0, j;

	if (!name)
		return (-1);
	while (environ[i])
	{
		if (match_env_name(environ[i], name))
		{
			free(environ[i]);
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
			return (0);
		}
		i++;
	}
	return (0);
}

/**
 * handle_env_builtins - handles setenv and unsetenv
 * @args: parsed arguments
 * Return: 1 if executed, 0 otherwise
 */
int handle_env_builtins(char **args)
{
	if (_strcmp(args[0], "setenv") == 0)
	{
		if (!args[1] || !args[2])
			write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
		else
			_setenv(args[1], args[2]);
		return (1);
	}
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		if (!args[1])
			write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		else
			_unsetenv(args[1]);
		return (1);
	}
	return (0);
}
