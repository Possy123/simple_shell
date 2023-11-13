#include "shell.h"
/**
 *
 *
 */
void execute_search(char *input, char **argv)
{
	char *path_ctrl = getenv("PATH");

	if (path_ctrl != NULL)
	{
		char *path[32];
		token(path_ctrl, paths);

		char *current_d[1024];

		if (getcwd(current, sizeof(current_d)) == NULL)
		{
			perror("getcwd issues");
			exit(1);
		}
		for (int i = 0; path[i] != NULL; i++)
		{
			char *complete_path[1024];
			snprintf(complete_path, sizeof(complete_path), "%s %s", path[i], input);

			if(access(complete_path, X_OK) == 0)
			{
				if (execve(complete_path, argv, NULL) == -1)
				{
					perror("error");
					exit(1);
				}
				break;
			}
		}
	}
	else
	{
		printf("Path environment not set\n");
	}
	printf("command not found");
	exit(1);
}
