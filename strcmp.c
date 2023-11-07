#include "shell.h"
/**
 * our_strcmp - Compare two strings
 * @string1: The first string to compare
 * @string2: The second string to compare
 *
 * Description:
 * This function compares two strings and determines their lexical order
 *
 * Return:
 * - An integer value less than, equal to, or greater than zero if 'string1'
 * is found to be less than, equal to, or greater than 'string2', respectively
 */
int our_strcmp(const char *string1, const char *string2)
{
	while (*string1 && *string2 && *string1 == *string2)
	{
		string1++;
		string2++;
	}

	return ((int)(*string1 - *string2));
}
