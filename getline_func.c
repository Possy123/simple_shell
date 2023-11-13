#include "main.h"
/**
 *
 *
 */

char *my_getline()
{
	static char buffer[BUFFER_SIZE];
	static char *buffer_ptr = buffer;
	static ssize_t remaining_chars = 0;
	
	char *text = (char *)malloc(BUFFER_SIZE);
	if (text == NULL)
	{
		perror("getline issures");
		exit(EXIT_FAILURE);
	}
	char *text_ptr = text;
	/*ssize_t read_chars;*/

	while (1)
	{
		if (remaining_chars <= 0)
		{
			remaining_chars = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_ptr = buffer;

			if (remaining_chars <= 0)
			{
				break;
			}
		}

		*text_ptr = *buffer_ptr;
		text_ptr++;
		buffer_ptr++;
		remaining_chars--;

		if (*(text_ptr - 1) == '\n')
		{
			break;
		}
	}
	*text_ptr = '\0';

	return (text);
}


int main()
{
	while (1)
	{
		printf("$ ");

		char *input = my_getline();
		printf("%s\n", input);

		/*free(input);*/

	}
	return (0);
}
