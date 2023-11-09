#include "main.h"
/**
 *
 */
void execute_line(char *lines)
{
	pid_t new_pid = fork();

	if (new_pid == -1)
	{
		perror("execve error");
		exit(1);
	}

	if (new_pid == 0)
	{
		char *argv[36];
		/*int argc = 0;*/

		/*token(lines, argv);*/

		argv[0] = (char *)lines;
		argv[1] = NULL;

		token(lines, argv);

		if (execve(argv[0], argv, NULL) == -1)
		{
			fprintf(stderr, "Command not found: %s\n", lines);
		}
	}
	else
	{
		int status;

		wait(&status);
	}
}
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
	pid_t pid;

	while (1)
	{
		printf("$ ");
		readlines = getline(&line_ptr, &bufsize, stdin);

		if (readlines == -1)
		{
			if (feof(stdin))
			{
				printf("\nend (Control D) of file\n");
			}
			else
			{
				perror("getline");
			}
			break;
		}
		if (readlines == 1 && line_ptr[0] == '\n')
		{
			free(line_ptr);
			continue;
		}
		if (line_ptr[readlines -1] == '\n')
		{
			line_ptr[readlines - 1] = '\0';
		}
		execute_line(line_ptr);
	}
	free(line_ptr);

	return (0);
}
