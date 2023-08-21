#include "shell.h"

/**
 * my_exit - shell is exited
 * @details: potential arguments contained in shell.
 * Return: exit
 */


int my_exit(t_info *details)
{
	int e_code;

	if (details->av[1])
	{
		e_code = atoi(details->av[1]);

		if (e_code == 0 && details->av[1][0] != '0')
		{
			details->stat = 2;
			err_print(details, "Illegal number: ");
			puts_err(details->av[1]);
			putchar_err('\n');
			return (1);
		}

	details->error_code = e_code;
	return (-2);
	}

	details->error_code = -1;
	return (-2)
}


/**
 * change_cd - Current directory will be changed
 * @details: Arguments contained in structure.
 *  Return: Always 0
 */

int change_cd(t_info *details)
{
	char buff[1024], *dir, *current_dir;
	char *old_pwd, *new_pwd;
	int c_dir_ret;

	c_dir_ret = 0;
	current_dir = getcwd(buff, 1024);

	if (!current_dir)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
	}
	else if (!details->av[1])
	{
		dir = get_env(details, "HOME=");
		if (!dir)
		{
			dir = get_env(details, "PWD=");
		}
		c_dir_ret = chdir(dir ? dir : "/");
	}
	else if (_strcmp(details->av[1], "-") == 0)
	{
		old_pwd = get_env(details, "OLDPWD=");
		if (!old_pwd)
	{
		_puts(current_dir);
		_putchar('\n');
		return (1);
	}
	_puts(old_pwd);
	_putchar('\n');
	c_dir_ret = chdir(old_pwd ? old_pwd : "/");
	}
	else
	{
		c_dir_ret = chdir(details->av[1]);
	}

	if (c_dir_ret == -1)
	{
		err_print(details, "can't cd into ");
		puts_err(details->av[1]);
		putchar_err('\n');
	}
	else
	{
		set_env(details, "OLDPWD", current_dir);
		new_pwd = getcwd(buff, 1024);
		set_env(info, "PWD", new_pwd);
	}

	return (0);
}


/**
 * help_cd - function that helps
 * @details: Arguments contained in structure
 *  Return: Always 0
 */

int help_cd(t_info *details)
{
	char **arr_arg;

	arr_arg = details->av;
	_puts("Usage: cd [directory]\n");
	_puts("Change the current working directory.\n\n");
	_puts("Options:\n");
	_puts("  directory     The directory to change to.\n");


	if (*arr_arg)
	{
		_puts("Argument passed: ");
		_puts(*arr_arg);
		_putchar('\n');
	}

	return (0);
}
