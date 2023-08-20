#include "shell.h"

/**
 * _strlen - a function that returns the string len
 * @str: the string 
 * Return: integer length of string
 */

int _strlen(char *str)
{
	int x = 0;

	if (!str)
	return 0;

	for (; *str != '\0'; str++)
	x++;

	return x;
}

/**
 * _strcmp - compares two strings
 * @str1: the 1st string
 * @str2: the 2nd string
 * Return: neg if str1 < str2
 */

int _strcmp(char *str1, char *str2)
{
	for (; *str1 && *str2; str1++, str2++)
	{
		if (*str1 != *str2)
		return ((*str1 - *str2));
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - if needle starts with haystack it's checked
 * @haystacks: searched string
 * @needles: found substring
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *soup, const char *meat)
{
	for (; *meat; meat++, soup++)
	{
		if (*meat != *soup)
			return (NULL);
	}

	return ((char *)soup);
}


/**
 * _strcat - merges two strings
 * @_dest: the destination string
 * @_src: the source string
 *
 * Return: pointer to destination string
 */

char *_strcat(char *_dest, char *_src)
{
	char *rt = _dest;

	for (; *_dest; _dest++)
	{

	}

	for (; *_src; _src++, _dest++)
	{
		*_dest = *_src;
	}

	*_dest = *_src;

	return rt;
}
