#include "shell.h"
/**
 * our_strcpy - Copy a string from source to destination
 * @dest: The destination string to copy into
 * @src: The source string to be copied
 *
 * Description:
 * This function copies the contents of the source string 'src' (including
 * the null-terminating character) into the destination string 'dest'
 *
 * Return:
 * A pointer to the final string 'dest'.
 */
char *our_strcpy(char *dest, char *src)
{
	int len = 0, i = 0;

	len = 0;
	while (src[len] != '\0')
		len++;

	for (; i < len; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}
