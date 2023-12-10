#include "shell.h"

/**
 * getHistoryFile - Obtains the history file path
 * @info: Parameter struct
 *
 * Return: Allocated string containing the history file path
 */
char *getHistoryFile(info_t *info)
{
	char *homeDir, *filePath;

	homeDir = _getenv(info, "HOME=");
	if (!homeDir)
		return (NULL);

	filePath = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HIST_FILE) + 2));
	if (!filePath)
		return (NULL);

	filePath[0] = 0;
	_strcpy(filePath, homeDir);
	_strcat(filePath, "/");
	_strcat(filePath, HIST_FILE);

	return (filePath);
}

/**
 *writeHistoryFile-Generates a file or appends to an existing file with history
 * @info: Parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistoryFile(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

