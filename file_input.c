#include "shell.h"

/**
 * handle_file_input - Handles execution when a file is passed as an argument
 * @av: Command line arguments array
 *
 * Return: void
 */
void handle_file_input(char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": 0: Can't open ", 16);
		write(STDERR_FILENO, av[1], _strlen(av[1]));
		write(STDERR_FILENO, "\n", 1);
		free_env();
		exit(127);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
