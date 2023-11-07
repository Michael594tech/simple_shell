#include "shell.h"
/**
 * our_strcat - Concatenate two strings
 * @final_str: The string to append to
 * @str_to: The string to add
 *
 * Description:
 * This function concatenates the string 'str_to' to the end of the 'final_str'
 *
 * Return:
 * A pointer to the resulting string after concatenation.
 */
char *our_strcat(char *final_str, char *str_to)
{
	int i, j;

	i = 0;
	while (final_str[i] != '\0')
		i++;

	j = 0;
	while (str_to[j] != '\0')
	{
		final_str[i] = str_to[j];
		j++;
		i++;
	}
	final_str[i] = '\0';

	return (final_str);
}
