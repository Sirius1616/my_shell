#include "shell.h"

/**
 * atoi_error - an integer that was converted from a string
 * @str: the converted string
 * Return: 0 if no numbers in string
 */

int atoi_error(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;

	while (str[i] != '\0')
	{
	if (str[i] >= '0' && str[i] <= '9') {
            res *= 10;
            res += (str[i] - '0');
            if (res > INT_MAX)
                return (-1);
        } else {
            return (-1);
        }
	i++;
	}

	return (res);
}

/**
 * err_print - error message printed
 * @inf: the return info and parameter
 * @e_str: error type contained in the string
 * Return: 0 if number of string is null
 */

void err_print(t_info *inf, char *e_str)
{
	puts_err(inf->name_f);
	puts_err(": ");
	print_dec(inf->count_line, STDERR_FILENO);
	puts_err(": ");
	puts_err(inf->av[0]);
	puts_err(": ");
	puts_err(e_str);
}

/**
 * print_dec - a decimal number is printed in base 10
 * @in: the enter value
 * @fd: to be written into fd
 *
 * Return: characters printed number
 */


int print_dec(int in, int fd)
{
	int j, cnt = 0;
	int (*put_char)(char) = _putchar;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		put_char = putchar_err;

	if (in < 0)
	{
	absolute = -in;
	put_char('-');
	cnt++;
	} 
	else
	{
		absolute = in;
	}

	current = absolute;
	j = 1000000000;

	while (j > 1)
	{
	if (absolute / j)
	{
		put_char('0' + current / j);
		cnt++;
	}
	current %= j;
	j /= 10;
	}

	put_char('0' + current);
	cnt++;

	return (cnt);
}

/**
 * num_conv - a function that converts
 * @num: value
 * @_base: number base
 * @_flag: flag argument
 * Return: string
 */

char *num_conv(long int num, int _base, int _flag)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *pt;
	unsigned long n = num;

	if (!(_flag & UNSIGN_CONV) && num < 0)
	{
	n = -num;
	sign = '-';
	}

	arr = _flag & LOWCASE_CONV ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buff[49];
	*pt = '\0';

	for (; n != 0; n /= _base)
	{
		*--pt = arr[n % _base];
	}

	if (sign)
		*--pt = sign;

	return (pt);
}

/**
 * comment_rem - first instance of '#' is replaced with '\0' by the function
 * @buffer: string address
 *
 * Return: 0 always;
 */

void comment_rem(char *buffer)
{
	int j = 0;

	while (buffer[j] != '\0')
	{
		if (buffer[j] == '#' && (!j || buffer[j - 1] == ' '))
		{
			buffer[j] = '\0';
			break;
		}
		j++;
	}
}
