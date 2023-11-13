#include "shell.h"
/**
 *
 */
void token(char *lines, char **argv)
{
	char *token;
	char *delim = " \n";
	int i = 0;

	token = strtok(lines, delim);

	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	argv[i] = NULL;
}
