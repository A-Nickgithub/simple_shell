#include "shelly.h"

/**
* append - adds path to command
* @path: path of command
* @command: user entered command
* Return: buffer containing command with path on success
* NULL on failure
*/
char *append(char *path, char *command)
{
	char *buf;
	size_t a = 0, n = 0;

	if (command == 0)
		command = "";

	if (path == 0)
		path = "";

	buf = malloc(sizeof(char) * (_strlen(path) + _strlen(command) + 2));
	if (!buf)
		return (NULL);

	while (path[a])
	{
		buf[a] = path[a];
		a++;
	}

	if (path[a - 1] != '/')
	{
		buf[a] = '/';
		a++;
	}
	while (command[n])
	{
		buf[a + n] = command[j];
		n++;
	}
	buf[a + n] = '\0';
	return (buf);
}
