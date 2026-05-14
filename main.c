#include "shell.h"

/**
 * _getline - custom getline using static buffer
 * @lineptr: pointer to buffer
 * @n: buffer size
 * @stream: file stream
 * Return: bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buf[1024];
	static ssize_t count, pos;
	ssize_t i = 0, j;
	char c, *new_ptr;

	if (!lineptr || !n || !stream)
		return (-1);
	if (!*lineptr)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}
	while (1)
	{
		if (pos >= count)
		{
			count = read(fileno(stream), buf, 1024);
			pos = 0;
			if (count <= 0)
				return (i == 0 ? -1 : i);
		}
		c = buf[pos++];
		if ((size_t)i >= *n - 1)
		{
			*n += 128;
			new_ptr = malloc(*n);
			if (!new_ptr)
				return (-1);
			for (j = 0; j < i; j++)
				new_ptr[j] = (*lineptr)[j];
			free(*lineptr);
			*lineptr = new_ptr;
		}
		(*lineptr)[i++] = c;
		if (c == '\n')
			break;
	}
	(*lineptr)[i] = '\0';
	return (i);
}

/**
 * parse_command - splits input into tokens
 * @line: input string
 * @args: array to hold tokens
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

/**
 * main - shell entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0
 */
int main(int ac, char **av)
{
	char *line = NULL, *args[100];
	size_t len = 0;
	ssize_t read_bytes;

	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		read_bytes = _getline(&line, &len, stdin);
		if (read_bytes <= 0)
		{
			if (isatty(STDIN_FILENO) && read_bytes == 0)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}
		if (line[read_bytes - 1] == '\n')
			line[read_bytes - 1] = '\0';
		parse_command(line, args);
		execute_command(args, av, line);
	}
	free(line);
	return (0);
}
