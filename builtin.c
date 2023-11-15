#include "main.h"

/**
 * print_env - print environment
 * @env:environment variable
 */
void print_env(char **env)
{
	unsigned int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * exit_command - exit builtin
 * @command:that is the command inputted
 * Return:strcmp
 */
int exit_command(char *command)
{
	return (strcmp(command, "exit") == 0);
}

/**
 * sigint_handler - to handle ctrl +c error
 * @signum: name of variable
 */
void sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	exit(EXIT_SUCCESS);
}

/**
 * sigint_error - to handle the error command in ctrl c
 */
void sigint_error(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("Error setting up signal handler");
		exit(EXIT_FAILURE);
	}
}
