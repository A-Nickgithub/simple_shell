#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @delm: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *string, char *delm)
{
	int a, b, c, d, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delm)
		delm = " ";
	for (a = 0; string[a] != '\0'; a++)
		if (!is_delm(string[a], delm) && (is_delm(string[a + 1], delm)
				|| !string[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delm(string[a], delm))
			a++;
		c = 0;
		while (!is_delm(string[a + c], delm) && string[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = string[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @string: the input string
 * @delm: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char delm)
{
	int a, b, c, d, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (a = 0; string[a] != '\0'; a++)
		if ((string[a] != delm && string[a + 1] == delm) ||
		    (string[a] != delm && !string[a + 1]) || string[a + 1] == delm)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (string[a] == delm && string[a] != delm)
			a++;
		c = 0;
		while (string[a + c] != delm && string[a + c] && string[a + c] != delm)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = string[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}
