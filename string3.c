#include "shell.h"

/**
 **_strncpy - string s copied
 *@dest: string to be copied destination
 *@src: the source 
 *@count: length of characters
 *Return: string concatenated
 */

char *_strncpy(char *dest, char *src, int count)
{
	int j;


	for (j = 0; j < count - 1 && src[j] != '\0'; j++)
	{
		dest[j] = src[j];
	}

	dest[j] = '\0';

	return (dest);
}


/**
 **_strncat - two strings are concatenated
 *@dest: 1st string
 *@src: 2nd string
 *@count: the count of bytes to be used
 *Return: string concatenated
 */

char *_strncat(char *dest, char *src, int count)
{
	char *str = dest;
	int x, y;

	for (x = 0; dest[x] != '\0'; x++)
	{

	}

	for (y = 0; src[y] != '\0' && y < count; y++)
	{
		dest[x + y] = src[y];
	}

	dest[x + y] = '\0';

	return (str);
}


/**
 **_strchr - character in a string is located
 *@str: parsed string
 *@ch: the xter to search
 *Return: (str) memory area ptr
 */

char *_strchr(char *str, char ch)
{
	for (; *str != '\0'; str++)
	{
		if (*str == ch)
			return (str);
	}

	return (NULL);
}
