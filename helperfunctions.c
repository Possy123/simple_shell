#include "main.h"
/**
 * token - token to pass
 * @input: to pass input
 * @argv: argument vector
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
 * @argv: argument vector
 * @env: environment
 */
void execute_command(char **argv, char **env)
{
	if (strchr(argv[0], '/') != NULL)
	{
		execute_c(argv, env);
	}
	else
	{
		execute_path(argv, env, NULL);
	}
}


/**
 * execute_c - execute command
 * @argv: argument vector
 * @env: environent variable
 */
void execute_c(char **argv, char **env)
{
	pid_t pid;
	int status;

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

	}
}

/**
 * execute_path - execute path
 * @argv: argument vector
 * @env: environment variable
 * @path: path
 */
void execute_path(char **argv, char **env, char *path)
{
	char *toks, *path_dup;
	char *command_path;
	struct stat st;

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

				commandpath(argv, env, command_path);
				break;
			}

			free(command_path);
			toks = strtok(NULL, ":");
		}
		free(command_path);
		free(path_dup);
	}
}

/**
 * commandpath - Command path
 * @argv: argument vector
 * @env: environment variable
 * @command_path: command path
 */
void commandpath(char **argv, char **env, char *command_path)
{
	pid_t pid;
	int status;

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
		if (WIFEXITED(status) == 0)
		{
		}
	}
}

