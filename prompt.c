#include "shell.h"
/**
 * main - Entry point of program
 *
 * Return: 0 on sucess
 */
int main(void)
{
	char *line_ptr = NULL;
	size_t bufsize = 0;
	ssize_t readlines;
/*	unsigned int i;*/

	/*char *argv[] = {"bin/ls", "-l", "/tmp", NULL};*/

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		readlines = getline(&line_ptr, &bufsize, stdin);

		if (readlines == -1)
		{
			perror("getline");
			free(line_ptr);
			exit(EXIT_FAILURE);
		}
		if (readlines > 0 && line_ptr[readlines - 1] == '\n')
		{
			line_ptr[readlines - 1] = '\0';
		}
		execute_command(line_ptr);
	}
	free(line_ptr);

	return (0);
}
