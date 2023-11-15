#include "shell.h"
/**
 * main - Entry point of program
 * @argc: the argument count
 * @argv: argument vector
 *
 * Return: 0 on sucess
 */
int main(int argc, char *argv[])
{
	char *line_ptr = NULL;
	size_t bufsize = 0;
	ssize_t readlines;

	if (argc < 1)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		readlines = getline(&line_ptr, &bufsize, stdin);

		if (readlines == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("error reading input");
				break;
			}
		}
		if (readlines > 0 && line_ptr[readlines - 1] == '\n')
		{
			line_ptr[readlines - 1] = '\0';
		}
		execute_command(line_ptr, argv[0]);
	}
	free(line_ptr);

	return (0);
}
