#include "shell.h"

/**
 * execute_command - execute command
 * @command: command
 * @program: the program's name
 */
void execute_command(char *command, char *program)
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
		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, NULL) == -1)
		{
			perror(program);
			free(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
