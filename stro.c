#include "shell.h"

/**
 * _strtok - tokenizes a string
 * @string: string to be tokenized
 * @delm: delimitator for the tokens
 * Return: pointer to each token
 */
char *_strtok(char *string, char *delm)
{
	int c;
	static char *str;

	if (!string)
		string = str;
	c = *string++;
	while (_strchr(delm, c))
	{
		if (c == 0)
			return (0);
		c = *string++;
	}
	--string;
	str = string + _strcspn(string, delm);
	if (*str != 0)
	{
		*str = 0;
		str++;
	}
	return (string);
}
/**
 * _strchr - locates character in string
 * @s: string
 * @b: character to locate
 * Return: pointer to the first occurrence of the character
 */
char *_strchr(char *s, char b)
{
	while (*s != 0)
	{
		if (*s == b)
			return (s);
		s++;
	}
	if (*s == b)
		return (s);
	return (0);
}

/**
 * _strcspn - gets the length of a prefix string
 * @s: string
 * @pref: prefix string
 * Return: number of bytes in the initial seg of s
 */
unsigned int _strcspn(char *s, char *pref)
{
	unsigned int len = 0, a = 0;

	while (s[len] != 0)
	{
		int flag = 0;

		for (a = 0; pref[a] != 0; a++)
		{
			if (s[len] == pref[a])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			len++;
		else
			break;
	}
	return (len);
}
