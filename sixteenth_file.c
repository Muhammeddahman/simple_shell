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

