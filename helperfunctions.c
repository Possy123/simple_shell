#include "main.h"
/**
 * token - token to pass
 * input: to pass input
 * argv: argument vector
 */
void token(char *input, char **argv)
{
	char *tokenizer;
	char *delim = " \n";
	int a = 0;

	tokenizer = strtok(input, delim);
	while (tokenizer != NULL)
	{
		argv[a] = tokenizer;
		tokenizer = strtok(NULL, delim);
		a++;
	}
	argv[a] = NULL;
}

/**
 * execute_command - To execute the program
 * argv: argument vector
 * env: environment
 * path: the path to pass
 */

void execute_command(char** argv, char** env, char* path)
{
	pid_t pid;
	int status;
	char* path_dup, *toks, *command_path;
	struct stat st;

	if (strchr(argv[0], '/') != NULL) 
	{
		pid = fork();
		if (pid == -1) 
		{
			perror("Unsuccessful");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) 
		{
			if (execve(argv[0], argv, env) == -1) 
			{
				perror("Error");
				exit(EXIT_FAILURE);
			}
		} 
		else 
		{
			wait(&status);
			if (WIFEXITED(status))
			{
					
			}

		}
	}
	else
	{
		path = getenv("PATH");
		if (path != NULL)
		{
			path_dup = strdup(path);
			toks = strtok(path_dup, ":");

			while (toks != NULL)
			{
				command_path = malloc(strlen(toks) + strlen(argv[0]) + 2);
				strcpy(command_path, toks);
				strcat(command_path, "/");
				strcat(command_path, argv[0]);
				strcat(command_path, "\0");

				if (stat(command_path, &st) == 0)
				{
					pid = fork();
					if (pid == -1)
					{
						perror("Unsuccessful");
						exit(EXIT_FAILURE);
					}
					if (pid == 0)
					{
						if (execve(command_path, argv, env) == -1)
						{
							perror("Error");
							free(command_path);
							exit(EXIT_FAILURE);
						}
					}
					else
					{
						wait(&status);
						if (WIFEXITED(status))
						{
							break;
						}
					}
				}
				free(command_path);
				toks = strtok(NULL, ":");
			}

			free(command_path);
			free(path_dup);
		}
	}
}
