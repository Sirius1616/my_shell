#include "shell.h"

/**
 * find_environ - the string array copy of our environ is returned
 * @details: potential arguments contained in struct.
 * Return: Always 0
 */

char **find_environ(t_info *details)
{
	if (details->environ == NULL || details->changed_env)
	{
		details->environ = list_strings_conv(details->env_list);
		details->changed_env = 0;
	}

	return (details->environ);
}


/**
 * remenv - environment variable is removed
 * @details: Potential arguments contained in structure
 *  Return: 1 on delete, 0 otherwise
 * @v: variable property of the string
 */

int remenv(t_info *details, char *v)
{
	size_t j;
	char *t;
	t_list *node = details->env_list;

	if (!node || !v)
		return (0);

	for (j = 0; node; node = node->next, j++)
	{
		t = begins_with(node->str, v);
		if (t && *t == '=')
		{
			details->changed_env = rem_node_at_index(&(details->env_list), j);
			j = 0;
			node = details->env_list;
		}
	}

	return (details->changed_env);
}


/**
 * put_env - Environment variable is initialized
 * @details: potential argument contained in a structure
 * @v: Property of the string environment
 * @vl: variable value of the string
 *  Return: Always 0
 */


int set_env(t_info *details, char *v, char *vl)
{
	char *buff = NULL;
	t_list *node;
	char *t;

	if (!v || !vl)
	return 0;

	buff = malloc(_strlen(v) + _strlen(vl) + 2);
	if (!buff)
	return 1;

	_strcpy(buff, v);
	_strcat(buff, "=");
	_strcat(buff, vl);

	for (node = details->env_list; node; node = node->next)
	{
		t = begins_with(node->str, v);
		if (t && *t == '=')
		{
			free(node->str);
			node->str = buff;
			details->changed_env = 1;
			return (0);
		}
	}

	insert_node_end(&(details->env_list), buff, 0);
	free(buff);
	info->changed_env = 1;
	return (0);
}
