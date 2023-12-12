#include "shell.h"

/**
 * customShell - main shell loop
 * @shellInfo: the parameter & return info struct
 * @arguments: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int customShell(info_t *shellInfo, char **arguments)
{
	ssize_t readResult = 0;
	int builtinReturn = 0;

	while (readResult != -1 && builtinReturn != -2)
	{
		clearInfo(shellInfo);
		if (interactive(shellInfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		readResult = getInput(shellInfo);
		if (readResult != -1)
		{
			setInfo(shellInfo, arguments);
			builtinReturn = findBuiltin(shellInfo);
			if (builtinReturn == -1)
				findCommand(shellInfo);
		}
		else if (interactive(shellInfo))
			_putchar('\n');
		freeInfo(shellInfo, 0);
	}
	writeHistory(shellInfo);
	freeInfo(shellInfo, 1);
	if (!interactive(shellInfo) && shellInfo->status)
		exit(shellInfo->status);
	if (builtinReturn == -2)
	{
		if (shellInfo->errNum == -1)
			exit(shellInfo->status);
		exit(shellInfo->errNum);
	}
	return (builtinReturn);
}

/**
 * findBuiltin - finds a builtin command
 * @shellInfo: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int findBuiltin(info_t *shellInfo)
{
	int i, builtinRet = -1;
	builtin_table builtinTable[] = {
		{"exit", customExit},
		{"env", customEnv},
		{"help", customHelp},
		{"history", customHistory},
		{"setenv", customSetenv},
		{"unsetenv", customUnsetenv},
		{"cd", customCd},
		{"alias", customAlias},
		{NULL, NULL}
	};

	for (i = 0; builtinTable[i].type; i++)
		if (_strcmp(shellInfo->argv[0], builtinTable[i].type) == 0)
		{
			shellInfo->lineCount++;
			builtinRet = builtinTable[i].func(shellInfo);
			break;
		}
	return (builtinRet);
}


/**
 * findCommand - finds a command in PATH
 * @shInfo: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(info_t *shInfo)
{
	char *commandPath = NULL;
	int i, argCount;

	shInfo->path = shInfo->argv[0];
	if (shInfo->lineCountFlag == 1)
	{
		shInfo->lineCount++;
		shInfo->lineCountFlag = 0;
	}
	for (i = 0, argCount = 0; shInfo->arg[i]; i++)
		if (!isDelim(shInfo->arg[i], " \t\n"))
			argCount++;
	if (!argCount)
		return;

	commandPath = findPath(shInfo, _getenv(shInfo, "PATH="), shInfo->argv[0]);
	if (commandPath)
	{
		shInfo->path = commandPath;
		forkCommand(shInfo);
	}
	else
	{
		if ((interactive(shInfo) || _getenv(shInfo, "PATH=")
			 || shInfo->argv[0][0] == '/') && isCommand(shInfo, shInfo->argv[0]))
			forkCommand(shInfo);
		else if (*(shInfo->arg) != '\n')
		{
			shInfo->status = 127;
			printError(shInfo, "not found\n");
		}
	}
}

/**
 * forkCommand - forks an exec thread to run cmd
 * @shellInfo: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(info_t *shellInfo)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(shellInfo->path, shellInfo->argv, getEnviron(shellInfo)) == -1)
		{
			freeInfo(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(shellInfo->status));
		if (WIFEXITED(shellInfo->status))
		{
			shellInfo->status = WEXITSTATUS(shellInfo->status);
			if (shellInfo->status == 126)
				printError(shellInfo, "Permission denied\n");
		}
	}
}

