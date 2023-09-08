#include "shell.h"

/**
 * _strSplit - Splits a string into an array of tokens based on whitespace.
 *
 * @cmd: The input string to be split.
 * @numStrings: A pointer to store the number of strings in the result array.
 *
 * Return: A dynamically allocated array of strings (tokens).
 *         The last element of the array is set to NULL.
 *         Returns NULL if memory allocation fails or if cmd is NULL.
 */
char **splitString(char *input, int *numStrings)
{
	const char *delimiters = " \t\n";
	char *token;
	char **result = NULL;
	char *copy = _strdup(input);
	if (!copy)
	{
		*numStrings = 0;
		return NULL;
	}

	*numStrings = 0;

	token = strtok(copy, delimiters);
	while (token != NULL)
	{
		(*numStrings)++;
		result = (char **)realloc(result, (*numStrings) * sizeof(char *));
		result[(*numStrings) - 1] = _strdup(token);
		token = strtok(NULL, delimiters);
	}
	result = (char **)realloc(result, ((*numStrings) + 1) * sizeof(char *));
	result[(*numStrings)] = NULL;

	free(copy);
	return result;
}

/**
 * freeArray - Frees the memory allocated for an array of strings.
 *
 * @ptr: The array of strings to be freed.
 * @numStrings: The number of strings in the array.
 *
 * This function iterates through the array of strings and frees each string,
 * and then frees the array itself. If ptr is NULL, it does nothing.
 */
void freeArray(char **ptr, int numStrings)
{
	int i;
	if (ptr == NULL)
	{
		return;
	}

	for (i = 0; i < numStrings; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
}

/**
 * __strdup - Duplicates a string.
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
	int i, rest;

	for (i = 0; s2[i] != '\0'; i++)
	{
		rest = (s1[i] + '0') - (s2[i] + '0');

		if (rest != 0)
			break;
	}
	return (rest);
}