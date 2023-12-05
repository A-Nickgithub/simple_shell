#include "shell.h"

/**
 * input_buff - buffers chained commands
 * @inform: parameter struct
 * @buff: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(inform_t *inform, char **buff, size_t *len)
{
	ssize_t c = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		c = getline(buff, &len_p, stdin);
#else
		c = _getline(inform, buff, &len_p);
#endif
		if (c > 0)
		{
			if ((*buff)[c - 1] == '\n')
			{
				(*buff)[c - 1] = '\0';
				c--;
			}
			inform->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(inform, *buff, inform->histcount++);
			{
				*len = c;
				inform->cmd_buff = buff;
			}
		}
	}
	return (c);
}

/**
 * get_input - gets a line minus the newline
 * @inform: parameter struct
 * Return: bytes read
 */
ssize_t get_input(inform_t *inform)
{
	static char *buff;
	static size_t n, m, len;
	ssize_t c = 0;
	char **buff_p = &(inform->arg), *p;

	_putchar(BUF_FLUSH);
	c = input_buff(inform, &buff, &len);
	if (c == -1)
		return (-1);
	if (len)
	{
		m = n;
		p = buff + n;

		check_chain(inform, buff, &m, n, len);
		while (m < len)
		{
			if (is_chain(inform, buff, &m))
				break;
			m++;
		}

		n = m + 1;
		if (n >= len)
		{
			n = len = 0;
			inform->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buff;
	return (c);
}

/**
 * read_buff - reads a buffer
 * @inform: parameter struct
 * @buff: buffer
 * @n: size
 * Return: c
 */
ssize_t read_buff(inform_t *inform, char *buff, size_t *n)
{
	ssize_t c = 0;

	if (*n)
		return (0);
	c = read(inform->readfiledes, buff, READ_BUF_SIZE);
	if (c >= 0)
		*n = c;
	return (c);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inform: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(inform_t *inform, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t n, len;
	size_t k;
	ssize_t c = 0, s = 0;
	char *p = NULL, *new_p = NULL, *y;

	p = *ptr;
	if (p && length)
		s = *length;
	if (n == len)
		n = len = 0;

	c = read_buff(inform, buff, &len);
	if (c == -1 || (c == 0 && len == 0))
		return (-1);

	y = _strchr(buff + n, '\n');
	k = y ? 1 + (unsigned int)(y - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + n, k - n);
	else
		_strncpy(new_p, buff + n, k - n + 1);

	s += k - n;
	n = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_numb: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
