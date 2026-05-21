#include "shell.h"

/**
 * remove_comments - removes comments from the input string
 * @buf: the input string from getline
 *
 * Return: void
 */
void remove_comments(char *buf)
{
	int i = 0;

	if (!buf)
		return;

	while (buf[i])
	{
		/* Check if '#' is at the start or preceded by a space */
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
		i++;
	}
}
