#include "shell.h"

/**
 * my_env - current environment is displayed
 * @details: potential arguments containing structure
 * Return: 0
 */

int my_env(t_info *details)
{
	put_str_list(details->env_list);
	return (0);
}


/**
 * get_env - a function that finds an environ variable value
 * @details:  pot arg structure
 * @nm: environ variable name
 * Return: value
 */


char *get_env(t_info *details, const char *nm)
{
	t_list *node;

	for (node = details->env_list; node != NULL; node = node->next)
	{
		if (begins_with(node->str, nm))
		{
			return (begins_with(node->str, nm));
		}
	}

	return (NULL);
}


/**
 * my_set_env - initialized new variable
 * @details: potential arguments structure
 *  Return: 0
 */

int my_set_env(t_info *details)
{	int success;

	if (details->ac != 3)
	{
		puts_err("wrong number of arguments\n");
		return (1);
	}

	success = set_env(details, details->av[1], details->av[2]);
	return ((success) ? 0 : 1);
}


/**
 * my_unset_env - environment variable is deleted
 * @details: arguments structural argument
 *  Return: 0
 */

int my_unset_env(t_info *details)
{
	int j = 1;

	if (details->ac == 1)
	{
		puts_err("Not enough arguments.\n");
		return (1);
	}

	while (j <= details->ac)
	{
		remenv(details, details->av[j]);
		j++;
	}

	return (0);
}


/**
 * fill_env_list - env linked list is filled
 * @details: structural argument
 * Return: 0
 */

int fill_env_list(t_info *details)
{
	t_list *node = NULL;
	size_t j = 0;

	while (environ[j])
	{
		insert_node_end(&node, environ[j], 0);
		j++;
	}

	details->env_list = node;

	return (0);
}
