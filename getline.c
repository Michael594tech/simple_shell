#include "shell.h"
/**
 * our_strlen - Custom string length function
 * @str: Input string
 * Return: Length of the string
 */
size_t our_strlen(const char *str);
/**
 * our_getline - Custom getline function
 * @line: Pointer to the line buffer
 * @len: Pointer to the length of the buffer
 * @stream: The stream to read from
 *
 * Description:
 * This function reads a line from the provided stream into the line buffer.
 *
 * Return:
 * -The number of characters read(excluding the newline character)if successful
 * - -1 if an error occurs or the end of the file is reached.
 */
ssize_t our_getline(char **line, size_t *len, FILE *stream)
{
	char *getline;
	ssize_t read;

	if (*line == NULL || *len == 0)
	{
		*len = 1024;
		*line = malloc(*len);
		if (*line == NULL)
		{
			return (-1);
		}
	}

	getline = fgets(*line, *len, stream);
	if (getline != NULL)
	{
		read = our_strlen(*line);

		if (read > 0 && (*line)[read - 1] == '\n')
		{
			(*line)[read - 1] = '\0';
			read--;
		}
		return (read);
	}
	else
	{
		return (-1);
	}
}
