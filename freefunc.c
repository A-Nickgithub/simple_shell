#include "shelly.h"

/**
* freebuffers - frees buffers
* @buf: buffer to be freed
* Return: no return
*/
void freebuffers(char **buf)
{
	int a = 0;

	if (!buf || buf == NULL)
		return;
	while (buf[a])
	{
		free(buf[a]);
		a++;
	}
	free(buf);
}
