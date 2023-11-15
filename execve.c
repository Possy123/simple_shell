#include "shell.h"

/**
 * execute_command - execute command
 * @command: command
 */
void execute_command(char *line_ptr)
{
	pid_t pid;
	char *args[] = {line_ptr, NULL};
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(line_ptr, args, environ) == -1)
		{
			perror("Error: command not found");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "Error: command exited with status %d\n", WEXITSTATUS(status));
		}
	}
}
