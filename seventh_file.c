#include "shell.h"

/**
 * isExecutableCommand - Determines if a file is an executable command
 * @info: Pointer to the info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutableCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateCharacters - Duplicates characters in a given range
 * @pathStr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to a new buffer containing the duplicated characters
 */
char *duplicateCharacters(char *pathStr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathStr[i] != ':')
			buffer[k++] = pathStr[i];
	buffer[k] = '\0';
	return (buffer);
}

