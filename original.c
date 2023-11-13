#include "shell.h"
/**
 *
 */

/*vioid execute_line(char *lines, char **argv, char **envp)*/
extern char **environ;

void execute_line(char *lines, char *envp[])
{
	char *argv[32];
	/*char *envp[] = {NULL};*/

	unsigned int i;

	token(lines, argv);

	pid_t new_pid = fork();

	/*token(lines, argv);*/

	if (new_pid == -1)
	{
		perror("execve error");
		exit(1);
	}

	if (new_pid == 0)
	{

		/*for (char **env = environ; *env != NULL; env++)
                {
                        printf("%s\n", *env);
                }*/
		/*if (strcmp(argv[0], "exit") == 0)
		{
			exit(0);
		}*/
		/**char *envp[] = {NULL}*/

		/*if (execve(argv[0],argv, environ) == -1)
		{
			perror("execve issues");
			exit(1);
		}*/

		/*token(lines, argv);*/

		/*for (char **env = environ; *env != NULL; env++)
		{
			printf("%s\n", *env);
		}*/


		/*int argc = 0;*/



		token(lines, argv);
		search_exe(argv[0], argv,envp);

		/*argv[0] = (char *)lines;
		argv[1] = NULL;*/

		/**token(lines, argv);
		char *path_var = getenv("PATH");

		if (path_var != NULL)
		{
			printf("PATH: %s\n", path_var);
		}
		else
		{
			printf("PATH environment not set\n");
		}
		

		if (execve(argv[0], argv, NULL) == -1)
		if (execve(lines, argv, NULL) == -1)
		{
			perror("execve");
			free(line_ptr);
			fprintf(stderr, "Command not found: %s\n", argv[0]);
			exit(1);
		}*/
	}

	else
	{
		int status;

		wait(&status);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		{
			fprintf(stderr, "Command not found: %s\n", lines);
		}
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
	unsigned int i;

	/*char *argv[] = {"bin/ls", "-l", "/tmp", NULL};*/

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
		line_ptr[strcspn(line_ptr, "\n")] = '\0';

		/*char *argv = {"bin/ls", "-l", "/tmp", NULL};*/
		/*token(line_ptr, argv);*/

		/*char *envp[] = {"MY_VARIABLE=my_value", NULL};*/
		execute_line(line_ptr);
	}
	free(line_ptr);

	return (0);
}
