#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * _itoa - Converts an integer to a string dynamically
 * @num: The integer to convert
 *
 * Return: A newly allocated string containing the number, or NULL on failure
 */
char *_itoa(int num)
{
	char buffer[20];
	int i = 0, j, is_negative = 0;
	char *str;

	if (num == 0)
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}
	while (num > 0)
	{
		buffer[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (is_negative)
		buffer[i++] = '-';

	str = malloc(i + 1);
	if (!str)
		return (NULL);

	for (j = 0; j < i; j++)
		str[j] = buffer[i - 1 - j];
	str[i] = '\0';

	return (str);
}

/**
 * expand_variables - Replaces $?, $$, and environment variables in args
 * @args: Null-terminated array of command arguments
 * @last_status: The exit status of the previously executed command
 *
 * Return: void
 */
void expand_variables(char **args, int last_status)
{
	int i = 0;
	char *var_value, *replacement_str;

	while (args && args[i])
	{
		if (args[i][0] == '$' && args[i][1] != '\0' && args[i][1] != ' ')
		{
			if (args[i][1] == '?')
			{
				replacement_str = _itoa(last_status);
				free(args[i]);
				args[i] = replacement_str;
			}
			else if (args[i][1] == '$')
			{
				replacement_str = _itoa(getpid());
				free(args[i]);
				args[i] = replacement_str;
			}
			else
			{
				/* Assumes getenv is allowed. Use custom _getenv if required */
				var_value = getenv(args[i] + 1);
				free(args[i]);
				if (var_value)
				{
					args[i] = strdup(var_value);
				}
				else
				{
					args[i] = malloc(1);
					args[i][0] = '\0'; /* Replace undefined vars with empty string */
				}
			}
		}
		i++;
	}
}
