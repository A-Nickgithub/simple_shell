#include "shell.h"

/**
 *_eputs - prints an input string
 * @strg: the string to be printed
 * Return: Nothing
 */
void _eputs(char *strg)
{
	int n = 0;

	if (!strg)
		return;
	while (strg[n] != '\0')
	{
		_eputchar(strg[n]);
		n++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @chara: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char chara)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (chara == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (chara != BUF_FLUSH)
		buf[n++] = chara;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @chara: The character to print
 * @filedes: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char chara, int filedes)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (chara == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(filedes, buf, n);
		n = 0;
	}
	if (chara != BUF_FLUSH)
		buf[n++] = chara;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @strg: the string to be printed
 * @filedes: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *strg, int filedes)
{
	int n = 0;

	if (!strg)
		return (0);
	while (*strg)
	{
		n += _putfd(*strg++, filedes);
	}
	return (n);
}
