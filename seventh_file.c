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

/**
 * findCmdInPath - Finds the specified command in the PATH string
 * @info: Pointer to the info struct
 * @pathStr: The PATH string
 * @cmd: The command to find
 *
 * Return: Full path of the command if found, or NULL
 */
char *findCmdInPath(info_t *info, char *pathStr, char *cmd)
{
	int i = 0, currPos = 0;
	char *path;

	if (!pathStr)
		return (NULL);
	if ((strlen(cmd) > 2) && startswith(cmd, "./"))
	{
		if (isExecutableCommand(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathStr[i] || pathStr[i] == ':')
		{
			path = duplicateCharacters(pathStr, currPos, i);
			if (!*path)
				strcat(path, cmd);
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (isExecutableCommand(info, path))
				return (path);
			if (!pathStr[i])
				break;
			currPos = i;
		}
		i++;
	}
	return (NULL);
}
