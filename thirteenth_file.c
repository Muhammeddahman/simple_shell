#include "shell.h"

/**
 * initializeInfo - Initializes the fields of an InfoStruct.
 * @info: The address of the InfoStruct.
 */
void initializeInfo(InfoStruct *info)
{
	info->argument = NULL;
	info->argumentsArray = NULL;
	info->executablePath = NULL;
	info->argumentCount = 0;
}
