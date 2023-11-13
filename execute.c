#include "shell.h"

/**
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
		char *argv[4];

		int argc = 0;

		token(lines, argv);

		argv[0] = (char *)lines;
		argv[1] = NULL;

		token(lines, argv);

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
} */

/**
 * main - Entry point of program
 *
 * Return: 0 on sucess
 */
int main(int argc, char *argv[])
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
		pid_t pid = fork();

		if (pid == -1)
		{
			/**if (execve (argv[0], argv, char *envp[]) == -1)
			{
				perror("fork and execve issue");
				exit(1);
			}*/
			perror("fork issues");
			exit(1);
		}
		if (pid == 0)
		{
			token(line_ptr, argv); 
			char *argv[] = {"/bin/ls", "-l", "/usr/","-a", NULL};
			char *custom_env[] = {
				"MY_ENV_VAR=my value",
				"ANOTHER_ENV=another value",
				NULL
			};
			if (execve(argv[0], argv, custom_env) == -1)
			{
				perror("execve issues");
				exit(1);
			}
		}

		/**	int i;

			for (i = 0; environ[i] != NULL; i++)
			{
				printf("%d", environ[i]);
				getchar();
			}*/
		else
		{
			int status;
			wait(&status);
		}
	}

	free(line_ptr);

	return (0);
}
