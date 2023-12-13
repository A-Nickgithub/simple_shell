#include "shell.h"
/**
 * _strcat - concatenates two strings
 * @string1: first string
 * @string2: second string to be concatenated
 * Return: pointer to the concatenated string
 */
char *_strcat(char *string1, char *string2)
{
	char *concatstring;
	int length1 = _strlen(string1), length2 = _strlen(string2), iterator1, iterator2;

	concatstring = malloc(sizeof(char) * (length1 + length2 + 1));
	if (concatstring == NULL)
	{
		printf("Error: impossible to allocate memory");
		exit(98);
	}
	for (iterator1 = 0; string1[iterator1] != '\0'; iterator1++)
	{
		concatstring[iterator1] = string1[iterator1];
	}
	for (iterator2 = 0; string2[iterator2] != '\0'; iterator2++)
	{
		concatstring[iterator1 + iterator2] = string2[iterator2];
	}
	concatstring[iterator1 + iterator2] = '\0';
	return (concatstring);
}

/**
 * _strcmp - compares two strings
 * @s1: string one
 * @s2: string two
 * Return: 0 if match, anything else if they don't match
 */
int _strcmp(char *s1, char *s2)
{
	int a = 0, k = 0, greater;
	int length1, length2;

	if (!s1 || !s2)
		return (-1);

	length1 = _strlen(s1);
	length2 = _strlen(s2);

	if (!length1 || !length2)
		return (-1);

	while (s1[a] != 0 && s2[a] != 0)
	{
		if (s1[a] == s2[a])
		{
			k++;
		}
		a++;
	}
	greater = length1 > length2 ? length1 : length2;
	if (k == greater)
		return (0);
	return (-1);
}
/**
 * _strcpy - prints string
 * Return: length of string
 * @dest: destiny string
 * @source: source string
 */
char *_strcpy(char *dest, char *source)
{
	int c = 0;

	int a;

	while (source[c] != 0)
	{
		c++;
	}

	dest[c] = '\0';
	for (a = 0; a < c; a++)
		dest[a] = source[a];

	return (dest);
}
/**
 * _strdup - gives a pointer to memory space
 * @str: string
 * Return: pointer
 */
char *_strdup(char *str)
{
	char *chara;

	unsigned int size = 0, a;

	if (str == NULL)
		return (NULL);

	while (*(str + size))
		size++;

	chara = malloc(sizeof(char) * (size + 1));

	if (chara == NULL)
		return (NULL);

	for (a = 0; a < size; a++)
		*(chara + a) = *(str + a);

	*(chara + size) = '\0';
	return (chara);
}
/**
 * _strlen - len of string
 * Return: length of string
 * @s: string
 */
int _strlen(char *s)
{
	int count = 0;

	if (!s)
		return (count);

	while (s[count] != 0)
		count++;
	return (count);
}
