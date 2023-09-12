#include "shel.h"

/**
 * freeArray - Frees the memory allocated for an array of strings.
 *
 * @ptr: The array of strings to be freed.
 * @numstrs: The number of strings in the array.
 *
 * This function iterates through the array of strings and frees each string,
 * and then frees the array itself. If ptr is NULL, it does nothing.
 */
void freeArray(char **ptr, int numstrs)
{
	int i;

	if (ptr == NULL || ptr[0] ==  NULL)
		return;

	for (i = 0; i < numstrs; i++)
	{
		free(ptr[i]), ptr[i] = NULL;
	}
	free(ptr), ptr = NULL;
}

/**
 * _strdup - Duplicates a string.
 * @str: Pointer to the original string.
 *
 * Return: A pointer to the duplicated string.
 */

char *_strdup(char *str)
{
	char *A;
	unsigned int i;

	if (str == NULL)
		return (NULL);
	A = (char *)malloc(sizeof(char) * strlen(str) + 1);

	if (A == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		A[i] = str[i];

	A[i] = '\0';
	return (A);
}

/**
 * _strcmp - Compares two strings.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 * Return:Returns an integer representing the comparison result.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0, rest = 1;

	for (i = 0; s2[i] != '\0'; i++)
	{
		rest = (s1[i] + '0') - (s2[i] + '0');

		if (rest != 0)
			break;
	}
	return (rest);
}

/**
 * str_concat - concatenates two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: A pointer to the concanited string.
 */

char *str_concat(char *s1, char *s2)
{
	char *A;
	unsigned int i, j;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	A = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (A == NULL)
		return (NULL);

	for (i = 0; s1[i] != '\0'; i++)
		A[i] = s1[i];

	for (j = 0; s2[j] != '\0'; j++)
		A[i++] = s2[j];
	A[i] = '\0';

	return (A);
}

/**
 * _isspace - checks if the str is all white spaces
 * @ch: str
 * Return: 1 if true else 0
*/

int _isspace(char ch)
{
	return (ch == ' ' || ch == '\t');
}
