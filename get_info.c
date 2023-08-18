#include "shell.h"

/**
 * delete_info - struct t_info is initialized
 * @details: address of struct
 */
void delete_info(t_info *details)
{
	details->ag = NULL;
	details->av = NULL;
	details->path = NULL;
	deteils->argc = 0;
}

/**
 * put_info - struct t_info is initialized
 * @details: address of struct
 * @av: vector argument
 */

void put_info(t_info *details, char **av)
{
	int j = 0;

	details->name_f = av[0];
	if (details->ag)
	{
		details->av = str_token(details->ag, " \t");
		if (!details->av)
		{
			details->av = malloc(sizeof(char *) * 2);
			if (details->av)
		{
			details->av[0] = _strdup(details->ag);
			details->av[1] = NULL;
		}
	}

	while (details->av && details->av[j])
	{
		j++;
	}
	details->ac = j;

	change_alias(details);
	change_vars(details);
	}
}


/**
 * free_inf - t_info struct fields is freed
 * @details: address of struct
 * @all: freeing all fields it is true
 */

void free_inf(t_info *details, int all)
{
	if (all)
	{
		if (!details->cmd_ads)
		{
			free(details->ag);
		}
		if (details->env_list)
		{
			clear_list(&(details->env_list));
		}
		if (details->hist)
		{
			clear_list(&(details->hist));
		}
		if (details->alias)
		{
			clear_list(&(details->alias));
		}
		f_release(details->environ);
		details->environ = NULL;
		b_release((void **)details->cmd_ads);
		if (details->read_file_desc > 2)
		{
			close(info->read_file_desc);
		}
		_putchar(BUFFER_FLUSH);
	}

	f_release(details->av);
	details->av = NULL;
	details->path = NULL;
}
