#include "shell.h"

/**
 * is_exec - determines if a file is an executable command
 * @inform: the info struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_exec(info_t *inform, char *path)
{
	struct stat st;

	(void)inform;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chara - duplicates characters
 * @pathstrg: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chara(char *pathstrg, int start, int stop)
{
	static char buff[1024];
	int n = 0, k = 0;

	for (k = 0, n = start; n < stop; n++)
		if (pathstrg[n] != ':')
			buff[k++] = pathstrg[n];
	buff[k] = 0;
	return (buff);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inform: the info struct
 * @pathstrg: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *inform, char *pathstrg, char *cmd)
{
	int n = 0, curr_pos = 0;
	char *path;

	if (!pathstrg)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_exec(inform, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrg[n] || pathstrg[n] == ':')
		{
			path = dup_chara(pathstrg, curr_pos, n);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_exec(inform, path))
				return (path);
			if (!pathstrg[n])
				break;
			curr_pos = n;
		}
		n++;
	}
	return (NULL);
}
