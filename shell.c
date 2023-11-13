#include "main.h"
/**
 * main - main code
 * @ac: argument count
 * @argv: argument vector
 * @env: enviroment
 * Return: 0 on sucess
 */
int main(int ac, char **argv, char **env)
{
	char *path = getenv("PATH");

	char *buffer = NULL;
	size_t bufsize = 0;

	sigint_error();

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		if (getline(&buffer, &bufsize, stdin) == -1)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		argv = (char **)malloc((sizeof(buffer) + 1) * sizeof(char *));
		token(buffer, argv);
		if (exit_command(argv[0]))
		{
			free(argv);
			break;
		}
		if (strcmp(argv[0], "env") == 0)
		{
			print_env(env);
			free(argv);
			continue;
		}

			execute_command(argv, env, path);

		free(argv);
	}
	free(buffer);

	return (0);
}
