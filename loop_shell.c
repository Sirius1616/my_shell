#include "shell.h"

/**
 * hash - loop of the main for shell
 * @inf: the parameter
 * @ave: main argument vector
 *
 * Return: 0 on success, 1 on error
 */

int hash(t_info *inf, char **ave)
{
	ssize_t x = 0;
	int builtin_rt = 0;

	for (; x != -1 && builtin_rt != -2; delete_info(inf))
	{
	if (interact(inf))
	_puts("$ ");
	putchar_err(BUFFER_FLUSH);
	x = find_input(inf);
	if (x != -1)
	{
		put_inf(inf, ave);
		builtin_rt = find_builtin(inf);
		if (builtin_rt == -1)
		get_cmd(inf);
	}
	else if (interact(inf))
	_putchar('\n');
	free_inf(inf, 0);
	}

	wr_hist(inf);
	free_inf(inf, 1);

	if (!interact(inf) && inf->stat)
	exit(inf->stat);

	if (builtin_rt == -2)
	{
	if (inf->error_code == -1)
		exit(inf->stat);
	exit(inf->error_code);
	}
	return (builtin_rt);
}


/**
 * get_inbuilt - getss a builtin command
 * @inf: the parameter
 *
 * Return: - 0 if builtin executed successfully
 */

int get_inbuilt(t_info *inf)
{
	int x = 0;
	int built_in_rt = -1;
	in_built_chart inbuilt1[] = {
	{"exit", my_exit},
	{"env", my_env},
	{"help", help_cd},
	{"history", my_hist},
	{"setenv", my_set_env},
	{"unsetenv", my_unset_env},
	{"cd", change_cd},
	{"alias", _myalias},
	{NULL, NULL}
	};

	while (inbuilt1[x].type != NULL)
	{
	if (_strcmp(inf->av[0], inbuilt1[x].flag_type) == 0)
	{
		inf->count_line++;
		built_in_rt = inbuilt1[x].functn(inf);
		break;
	}
	x++;
	}
	return built_in_rt;
}



/**
 * get_cmd - looks for a command in PATH
 * @inf: return info struct and the parameter
 *
 * Return: void
 */


void get_cmd(t_info *inf)
{
	char *path = NULL;
	int x = 0, y = 0;

	inf->path = inf->av[0];

	if (inf->count_line_flag == 1)
	{
	inf->count_line++;
	inf->count_line_flag = 0;
	}

	while (inf->ag[x])
	{
	if (!is_delimiter(inf->ag[x], " \t\n"))
		y++;
	x++;
	}

	if (!y)
	return;

	path = get_path(inf, get_env(inf, "PATH="), inf->av[0]);
	if (path)
	{
	inf->path = path;
	fork_cmd(inf);
	}
	else
	{
	if ((interact(inf) || get_env(inf, "PATH=") || inf->av[0][0] == '/')
	&& a_cmd(inf, inf->av[0]))
		fork_cmd(inf);
	else if (*(inf->ag) != '\n')
	{
		inf->stat = 127;
		err_print(inf, "doesn't exist\n");
	}
	}
}


/**
 * fork_cmd - forks a command to be run
 * @inf: the return info struct
 *
 * Return: void
 */

void fork_cmd(t_info *inf)
{
	pid_t child_id;

	child_id = fork();
	if (child_id == -1)
	{

	perror("Error:");
	return;
	}

	if (child_id == 0)
	{
	if (execve(inf->path, inf->av, find_environ(inf)) == -1)
	{
		free_inf(inf, 1);
		if (errno == EACCES)
		exit(126);
		exit(1);
	}

	}

	while (wait(&(inf->stat)) != child_id)
	{
	continue;
	}

	if (WIFEXITED(inf->stat))
	{
		inf->stat = WEXITSTATUS(inf->stat);
		if (inf->stat == 126)
		err_print(inf, "Permission denied\n");
	}
}
