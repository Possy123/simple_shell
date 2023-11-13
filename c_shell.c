#include "shell.h"
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
		/**char *argv[4;*/

		/*int argc = 0;*/

		/*token(lines, argv);*/

		/*argv[0] = (char *)lines;
		argv[1] = NULL;*/
		int argc = 0;
		char *argv[32];

		token(lines, argv);
		execute_search(argv[0], argv);

		if (execve(argv[0], argv, NULL) == -1)
		{
			fprintf(stderr, "Command not found: %s\n", lines);
			free(lines);
			exit(1);
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
int main(int argc, char *argv[], char *envp[])
{
	char *line_ptr = NULL;
	size_t bufsize = 0;
	ssize_t readlines;
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		readlines = getline(&line_ptr, &bufsize, stdin);

		if (readlines == -1)
		{
			if (feof(stdin))
			{
				printf("end (Control D) of file\n");
			}
			else
			{
				perror("getline");
			}
			break;
		}
		/**if (readlines == 1 && line_ptr[0] == '\n')
		{
			free(line_ptr);
			continue;
		}
		if (line_ptr[readlines -1] == '\n')
		{
			line_ptr[readlines - 1] = '\0';
		}*/
	}
	/**free(line_ptr);*/

	return (0);
}
