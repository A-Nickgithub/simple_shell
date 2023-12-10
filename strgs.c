#include "shell.h"
/**
 * _strlen - returns the length of a string
 * @string: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *string)
{
	int n = 0;

	if (!string)
		return (0);

	while (*string++)
		n++;
	return (n);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @string1: the first string
 * @string2: the second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @hay: string to search
 * @n: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *hay, const char *n)
{
	while (*n)
		if (*n++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * _strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}
