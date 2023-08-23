#include "shell.h"

/**
 * a_cmd - checks if a file is an executable command
 * @inf: structural informations
 * @paths: file path
 * Return: 0 if false or 1 if otherwise
 */

 int a_cmd(t_info *inf, char *paths)
 {
	struct stat sts;

	(void)inf;
	if (stat(paths, &sts) || !paths)
		return (0);

	if (sts.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}



/**
 * duplicate_char - character duplication
 * @path_str: string path
 * @begin: begining index
 * @_stop: final index
 *
 * Return: points to new buff
 */


char *duplicate_char(char *path_str, int begin, int end)
{
	static char buff[1024];
	int x = begin, y = 0;

	while (x < end && path_str[x] != ':')
	{
		buff[y++] = path_str[x++];
	}

	buff[y] = '\0';
	return (buff);
}


/**
 * get_path - looks for the command in the path
 * @inf: struct info
 * @path_str: string path
 * @_cmd:cmd to look for
 * Return: NULL or full path of the command when found
 */


char *get_path(t_info *inf, char *path_str, char *_cmd)
{
	int pres_pos = 0;
	char *paths;

	if (!path_str)
	return NULL;


	if ((_strlen(_cmd) > 2) && begins_with(_cmd, "./"))
	{
	if (a_cmd(inf, _cmd))
		return _cmd;
	}

	for (int x = 0; ; x++)
	{
		if (!path_str[x] || path_str[x] == ':')
		{
			paths = duplicate_char(path_str, pres_pos, x);


			if (!*paths)
			_strcat(paths, _cmd);
			else
			{
				_strcat(paths, "/");
				_strcat(paths, _cmd);
 			}


			if (a_cmd(inf, paths))
				return (paths);


			if (!path_str[x])
				break;


			pres_pos = x + 1;
		}
	}

	return (NULL);
}
