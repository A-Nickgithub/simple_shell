#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @st: the string to be converted
 * Return: 0 if no number,-1 on error
 */
int _erratoi(char *st)
{
	int n = 0;
	unsigned long int result = 0;

	if (*st == '+')
		st++;
	for (n = 0;  st[n] != '\0'; n++)
	{
		if (st[n] >= '0' && st[n] <= '9')
		{
			result *= 10;
			result += (st[n] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @inform: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(inform_t *inform, char *errstr)
{
	_eputs(inform->fname);
	_eputs(": ");
	print_d(inform->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inform->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @filedes: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int input, int filedes)
{
	int (*__putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (filedes == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @numb: number
 * @base: base
 * @flag: argument flags
 * Return: string
 */
char *convert_number(long int numb, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int n;

	for (n = 0; buff[n] != '\0'; n++)
		if (buff[n] == '#' && (!n || buff[n - 1] == ' '))
		{
			buff[n] = '\0';
			break;
		}
}
