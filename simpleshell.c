#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - main function
 * Return: The command executed in shell
 */
int main(void)
{
	pid_t pid;
	int status;
	char *buffer = NULL;
	size_t bufsize = 0;
	char *token;
	char *delim = " \n";
	char *argv[1024];

	while (1)
	{
		write(1, "$ ", 2);
		if (getline(&buffer, &bufsize, stdin) == -1)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Unsuccessful");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			token = strtok(buffer, delim);
			argv[0] = token;
			argv[1] = NULL;
			if (execve(argv[0], argv, NULL) == -1)
				perror("Error");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
	free(buffer);

	return (0);
}
