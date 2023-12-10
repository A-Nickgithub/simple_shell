#include "shell.h"

/**
 * interact - returns true if shell is interactive mode
 * @inform: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interact(inform_t *inform)
{
	return (isatty(STDIN_FILENO) && inform->readfd <= 2);
}

/**
 * is_delm- checks if character is a delimeter
 * @y: char to check
 * @delm: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delm(char y, char *delm)
{
	while (*delm)
		if (*delm++ == y)
			return (1);
	return (0);
}

/**
 *_alpha - checks for alphabetic character
 *@y: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _alpha(int y)
{
	if ((y >= 'a' && y <= 'z') || (y >= 'A' && y <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *my_atoi - converts a string to int
 *@s: str to be converted
 *Return: 0 if no numbers in str, converted number otherwise
 */

int my_atoi(char *s)
{
	int z, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (z = 0;  s[z] != '\0' && flag != 2; z++)
	{
		if (s[z] == '-')
			sign *= -1;

		if (s[z] >= '0' && s[z] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[z] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
