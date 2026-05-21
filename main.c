#include "shell.h"

void init_env(void)
{
	int i = 0;
	char **new_env;

	if (!environ)
	{
		environ = malloc(sizeof(char *));
		if (environ)
			environ[0] = NULL;
		return;
	}
	while (environ[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		exit(1);
	for (i = 0; environ[i]; i++)
		new_env[i] = _strdup(environ[i]);
	new_env[i] = NULL;
	environ = new_env;
}

void free_env(void)
{
	int i = 0;

	if (environ)
	{
		for (i = 0; environ[i]; i++)
			free(environ[i]);
		free(environ);
		environ = NULL;
	}
}

void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}

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
			count = read(STDIN_FILENO, buf, 1024);
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

int main(int ac, char **av)
{
	char *line = NULL, *args[100], *orig_args[100];
	ssize_t read_bytes;
	size_t len = 0;
	int last_status = 0, k;

	(void)ac;
	signal(SIGINT, sigint_handler);
	init_env();
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
			free_env();
			exit(last_status);
		}
		if (line[read_bytes - 1] == '\n')
			line[read_bytes - 1] = '\0';
		
		remove_comments(line);
		
		parse_command(line, args);
		for (k = 0; args[k]; k++)
			orig_args[k] = args[k];
		orig_args[k] = NULL;
		expand_variables(args, last_status);
		execute_command(args, av, line, &last_status);
		for (k = 0; args[k]; k++)
		{
			if (args[k] != orig_args[k])
				free(args[k]);
		}
	}
	free(line);
	free_env();
	return (last_status);
}
