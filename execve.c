#include "shell.h"

/**
 * execute_command - execute command
 * @command: command
 */
void execute_command(char *line_ptr)
{
	pid_t pid;

	char *args[2];
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		args[0] = line_ptr;
		args[1] = NULL;

		if (execve(line_ptr, args, environ) == -1)
		{
			perror("Error: command not found");
			free(line_ptr);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
