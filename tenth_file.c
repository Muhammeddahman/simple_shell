#include "shell.h"

/**
 * primaryFunction - The main functionality of the program
 * @argumentCount: Number of arguments
 * @argumentVector: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int primaryFunction(int argumentCount, char **argumentVector)
{
	info_t information[] = { INFO_INIT };
	int fileDescriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDescriptor)
		: "r" (fileDescriptor));

	if (argumentCount == 2)
	{
		fileDescriptor = open(argumentVector[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errorOutput(argumentVector[0]);
				_errorOutput(": 0: Can't open ");
				_errorOutput(argumentVector[1]);
				_errorCharacter('\n');
				_errorCharacter(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readFileDescriptor = fileDescriptor;
	}
	fillEnvironmentList(information);
	readCommandHistory(information);
	shellExecution(information, argumentVector);
	return (EXIT_SUCCESS);
}
