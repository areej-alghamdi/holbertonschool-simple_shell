#include "shell.h"

/**
 * remove_comments - Replaces '#' with '\0' if it starts a word
 * @line: The input string
 *
 * Return: void
 */
void remove_comments(char *line)
{
	int i = 0;

	if (!line)
		return;

	while (line[i])
	{
		if (line[i] == '#' && (i == 0 || line[i - 1] == ' '))
		{
			line[i] = '\0';
			break;
		}
		i++;
	}
}
