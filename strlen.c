#include "shell.h"
/**
 * our_strlen - Calculate the length of a string
 * @str: The input string
 *
 * Description:
 * This function counts the number of characters in the string 'str' until
 * it encounters a null-terminating character ('\0').
 *
 * Return:
 * The number of characters in the string.
 */
size_t our_strlen(const char *str)
{
	size_t i = 0;
	
	if (str == NULL)
		return (0);

	while (str[i] != '\0')
		i++;
	return (i);
}
