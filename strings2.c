#include "shell.h"

/**
 * _strcpy - string is copied
 * @_dest: the dest
 * @_src: the src
 * Return: destination pointer
 */
char *_strcpy(char *_dest, char *_src)
{
	int x;

	if (_dest == _src || _src == 0)
		return (_dest);

	for (x = 0; _src[x]; x++)
	{
		_dest[x] = _src[x];
	}

	_dest[x] = 0;
	return (_dest);
}


/**
 * _strdup - string is duplicated
 * @strr: duplicated string
 *
 * Return: duplicated string pointer
 */

char *_strdup(const char *strr)
{
	int lengths = 0;
	char *rt;

	if (strr == NULL)
		return NULL;

	for (; *strr; strr++)
		lengths++;

	rt = malloc(sizeof(char) * (lengths + 1));
	if (!rt)
		return NULL;

	lengths++;
	while (lengths--)
	{
		lengths--;
		rt[lengths] = *strr--;
	}

	return (rt);
}


/**
 *_puts - input string is printed
 *@strr: printed sring
 * Return: void
 */

void _puts(char *strr)
{
	int x;

	if (!strr)
		return;

	for (x = 0; strr[x] != '\0'; x++)
	{
		_putchar(strr[x]);
	}
}


/**
 * _putchar - prints the character c to stdout
 * @ch: printed xter
 * Return: On failure -1 and 1 on success
 */

int _putchar(char ch)
{
	static int x;
	static char arr[WR_BUFFER_SZ];

	if (x >= WR_BUFFER_SZ || ch == BUFFER_FLUSH)
	{
		write(1, arr, x);
		x = 0;
	}

	if (ch != BUFFER_FLUSH)
		arr[x++] = ch;

    return (1);
}
