#include "shell.h"

/**
 * my_hist - show the history list
 * @details: Aarguments contained in the structure.
 * Return: Always 0
 */
int my_hist(t_info *details)
{
	print_list(details->hist);
	return (0);
}

/**
 * rem_alias - string's set alias
 * @details: struct parameter
 * @s: alias' string
 * Return: Always 1 on failure, 0 on otherwise
 */

int rem_alias(t_info *details, char *s)
{
	char *equal_sign, temp_char;
	int ret, alias_index;

	equal_sign = _strchr(s, '=');
	if (!equal_sign)
		return (1);

	temp_char = *equal_sign;
	*equal_sign = '\0';

	alias_index = set_node_index(info->alias, begin_node(info->alias, s, -1));
	ret = rem_node_at_index(&(info->alias), alias_index);

	*equal_sign = temp_char;

	return (ret);
}


/**
 * put_alias - puts alias to string
 * @details: struct
 * @s: string alias
 *
 * Return: Always 1 on failure, 0 otherwise
 */

int put_alias(t_info *details, char *s)
{
	char *equal_sign;

	equal_sign = strchr(s, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return rem_alias(details, s);

	rem_alias(details, s);
	return (insert_node_end(&(details->alias), s, 0) == NULL);
}


/**
 * write_alias - alias string is printed
 * @node: the node alias
 *
 * Return: Always 1 on failure, 0 otherwise
 */


int write_alias(t_list *node)
{
	char *equal_sign;
	size_t alias_name_length, i;

	if (node)
	{
	equal_sign = _strchr(node->str, '=');
	if (equal_sign)
	{
		alias_name_length = equal_sign - node->str;
		i = 0;

		while (i < alias_name_length)
		{
			_putchar(node->str[i]);
			i++;
		}

		_puts("'");
		_puts(equal_sign + 1);
		_puts("'\n");

		return (0);
	}
	}

	return (1);
}


/**
 * my_alias - behaves like alias builtin
 * @details: Potential argument is contained in structure
 *  Return: Always 0
 */

int my_alias(t_info *details)
{
	int j = 1;
	char *p = NULL;

	t_list *node = NULL;

	if (details->ac == 1)
	{
		node = details->alias;
		while (node)
	{
		write_alias(node);
		node = node->next;
	}
	return (0);
	}

	while (details->av[j])
	{
		p = _strchr(details->av[j], '=');
		if (p)
		put_alias(details, details->av[j]);
	else
		write_alias(begin_node(details->alias, details->av[j], '='));

	j++;
	}

	return (0);
}
