#include "shell.h"

/**
 * interact - interactive, it will return true
 * @details: address of struct
 * Return: 0 if not in interactive mode, 1 otherwise
 */

int interact(t_info *details)
{
	int is_interactive = 0;

	if (isatty(STDIN_FILENO))
	{
		if (details->read_file_desc <= 2)
		{
			is_interactive = 1;
		}
	}

	return (is_interactive);
}


/**
 * is_delimiter - finds out if xter is a delimeter
 * @ch: checked xter
 * @delimiter: string delimiter
 * Return: 0 if false, 1 if otherwise
 */

int is_delimiter(char ch, char *delimiter)
{
	for (int i = 0; delimiter[i] != '\0'; i++)
	{
		if (delimiter[i] == ch)
		{
			return (1);
		}
	}
	return (0);
}


/**
 *_isalpha - gets character that are alphabetic
 *@ch: inputed character
 *Return: 1 if c is not alphabetic, 0 otherwise
 */

int _isalpha(int ch)
{
	return (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? 1 : 0);
}



/**
 *_atoi - string to an integer conversion
 *@str: converted string
 *Return: converted number
 */

int _atoi(char *str)
{
	int output = 0;
	int sig = 1;
	int flg = 0;
	int j = 0;

	while (str[j] != '\0' && flg != 2)
	{
		if (str[j] == '-')
		{
			sig *= -1;
		}
		else if (str[j] >= '0' && str[j] <= '9')
		{
			flg = 1;
			output = output * 10 + (str[j] - '0');
		}
		else if (flg == 1)
		{
			flg = 2;
		}
		j++;
	}

	return (output * sig);
}
