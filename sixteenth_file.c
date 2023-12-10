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

/**
 * buildHistoryList - Adds entry to a history linked list
 * @info: Structure containing potential arguments
 * @command: Command string to be added to the history
 * @linecount: The history linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *command, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	addNodeEnd(&node, command, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}


/**
 * renumberHistoryList - Renumbers the history linked list after changes
 * @info: Structure containing potential arguments
 *
 * Return: The new histcount
 */
int renumberHistoryList(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
