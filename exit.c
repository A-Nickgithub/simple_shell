#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, m;
	char *t = dest;

	n = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		m = a;
		while (m < n)
		{
			dest[m] = '\0';
			m++;
		}
	}
	return (t);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, m;
	char *t = dest;

	a = 0;
	m = 0;
	while (dest[a] != '\0')
		a++;
	while (src[m] != '\0' && m < n)
	{
		dest[a] = src[m];
		a++;
		m++;
	}
	if (m < n)
		dest[a] = '\0';
	return (t);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
