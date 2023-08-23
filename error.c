#include "shell.h"

/**
 * puts_err - a string is printed
 * @s: to be printed
 *
 * Return: void
 */
void puts_err(char *s)
{
	if (!s)
		return;

	for (int x = 0; s[x] != '\0'; x++)
	{
		putchar_err(s[x]);
	}
}

/**
 * putchar_err - character ch is written to the stderr
 * @ch: char to be printed
 *
 * Return: 1 when successful.
 */

int putchar_err(char ch)
{
	static int i;
	static char buf[WR_BUFFER_SZ];

	if (i >= WR_BUFFER_SZ || ch == BUFFER_FLUSH)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUFFER_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * filedes_put - char ch is written to given file descriptor
 * @ch: printed char
 * @fd: write to the filedescriptor
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */


int filedes_put(char ch, int fd)
{
	static int j;
	static char buf[WR_BUFFER_SZ];

	 if (j >= WR_BUFFER_SZ || ch == BUFFER_FLUSH)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (ch != BUFFER_FLUSH)
		buf[j++] = ch;
	return (1);
}

/**
 * filedes_puts - an input string is printed
 * @s: printed string
 * @fd: written to filedescriptor
 * Return: char number puted
 */

int filedes_puts(char *s, int fd)
{
	if (!s)
		return (0);

	int u = 0;

	while (*s)
	{
		u += filedes_put(*s++, fd);
	}

	return (u);
}
