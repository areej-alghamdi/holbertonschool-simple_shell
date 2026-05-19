#include "shell.h"

/**
 * is_delim - checks if character is a delimiter
 * @c: character
 * @delim: delimiters string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strtok - custom strtok function without using standard strtok
 * @str: string to tokenize
 * @delim: delimiter characters
 * Return: pointer to next token or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	char *current_token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL || *next_token == '\0')
		return (NULL);
	while (*next_token && is_delim(*next_token, delim))
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	current_token = next_token;
	while (*next_token && !is_delim(*next_token, delim))
		next_token++;
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	return (current_token);
}

/**
 * _getenv - gets an environment variable without using standard getenv
 * @name: name of the variable
 * Return: value of the variable or NULL
 */
char *_getenv(const char *name)
{
	int i = 0, j;

	if (!name || !environ)
		return (NULL);
	while (environ[i])
	{
		j = 0;
		while (name[j] && environ[i][j] == name[j])
			j++;
		if (name[j] == '\0' && environ[i][j] == '=')
			return (environ[i] + j + 1);
		i++;
	}
	return (NULL);
}
