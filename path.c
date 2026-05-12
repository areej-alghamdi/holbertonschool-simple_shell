#include "shell.h"

/**
 * find_path - searches for a command in the PATH directories
 * @command: the command name to find (e.g. "ls")
 *
 * Description: If command contains a '/', treat it as a path and
 * check directly. Otherwise, split PATH by ':' and search each
 * directory until the command is found.
 *
 * Return: full path string (must be freed by caller), or NULL if
 * not found or not executable.
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path_env = getenv("PATH");
	if (path_env == NULL || *path_env == '\0')
		return (NULL);
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
} 
