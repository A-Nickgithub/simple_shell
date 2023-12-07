#include "shell.h"

/**
 * _strcpy - copies a string
 * @destination: the destination
 * @source: the source
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
	int n = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[n])
	{
		destination[n] = source[n];
		n++;
	}
	destination[n] = 0;
	return (destination);
}

/**
 * _strdup - duplicates a string
 * @string: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int length = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--string;
	return (ret);
}

/**
 *_puts - prints an input string
 *@string: the string to be printed
 * Return: Nothing
 */
void _puts(char *string)
{
	int n = 0;

	if (!string)
		return;
	while (string[n] != '\0')
	{
		_putchar(string[n]);
		n++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @chara: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char chara)
{
	static int n;
	static char buff[WRITE_BUF_SIZE];

	if (chara == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buff, n);
		n = 0;
	}
	if (chara != BUF_FLUSH)
		buff[n++] = chara;
	return (1);
}
