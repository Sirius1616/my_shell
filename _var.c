#include "shell.h"

/**
 * is_linked - checks if current buffer is linked
 * @inf: struct parameter
 * @buffer: buffer char
 * @pp: current position in buf address
 *
 * Return: 0 if chain not delimeter, 1 otherwise
 */
int is_linked(t_info *inf, char *buffer, size_t *pp)
{
	size_t x = *pp;

	if (buffer[x] == '|' && buffer[x + 1] == '|')
	{
		buffer[x] = 0;
		x++;
		inf->cmd_type = OR_CMD;
	}
	else if (buffer[x] == '&' && buffer[x + 1] == '&')
	{
		buffer[x] = 0;
		x++;
		inf->cmd_type = AND_CMD;
	}
	else if (buffer[x] == ';')
	{
		buffer[x] = 0;
		inf->cmd_type = CHAIN_CMD;
	}
	else
		return (0);
	*pp = x;
	return (1);
}

/**
 * chk_chain - confirms if the next chain is linked
 * @inf: struct parameter
 * @buffer: buffer
 * @pp: current position address in buf
 * @x: begining position
 * @_len: buf len
 *
 * Return: nothing
 */


void chk_link(t_info *inf, char *buffer, size_t *pp, size_t x, size_t _len)
{
	size_t y = *pp;

	if (inf->cmd_type == AND_CMD)
	{
		if (inf->stat)
		{
			buffer[x] = 0;
			y = _len;
		}
	}
	if (inf->cmd_type == OR_CMD)
	{
		if (!inf->stat)
		{
			buffer[x] = 0;
			y = _len;
		}
	}

	*pp = y;
}

/**
 * change_alias - tokenized string alias replacement
 * @inf: the struct parameter
 *
 * Return: 0 if not replaced, 1 otherwise
 */


int change_alias(t_info *inf)
{
	int x = 0;
	t_list *nodes;
	char *pp;

	while (x < 10)
	{
		nodes = begin_node(inf->alias, inf->av[0], '=');
		if (!nodes)
			return (0);

		free(inf->av[0]);
		pp = _strchr(nodes->str, '=');
		if (!pp)
			return (0);

		pp = _strdup(pp + 1);
		if (!pp)
			return (0);

		inf->av[0] = pp;
		x++;
	}
	return (1);
}



/**
 * change_vars - tokenized string replacement
 * @inf: struct parameter
 *
 * Return: 0 if not replaced, 1 otherwise
 */


int change_vars(t_info *inf)
{
	int x = 0;
	t_list *nodes;

	while (inf->av[x])
	{
	if (inf->av[x][0] != '$' || !inf->av[x][1])
	{
		x++;
		continue;
	}

	if (!_strcmp(inf->av[x], "$?"))
	{
		change_string(&(inf->av[x]),
		_strdup(num_conv(inf->stat, 10, 0)));
		x++;
		continue;
	}

	if (!_strcmp(inf->av[x], "$$"))
	{
		change_string(&(inf->av[x]),
		_strdup(num_conv(getpid(), 10, 0)));
		x++;
		continue;
	}

	nodes = begin_node(inf->env_list, &inf->av[x][1], '=');
	if (nodes)
	{
		change_string(&(inf->av[x]),
		_strdup(_strchr(nodes->str, '=') + 1));
	}
	else
	{
		change_string(&(inf->av[x]), _strdup(""));
	}

	x++;
	}

	return (0);
}


/**
 * change_string - string replacement
 * @_prev: prev string address
 * @_curr: current string address
 *
 * Return: 0 if not replaced, 1 otherwise
 */
int change_string(char **_prev, char *_curr)
{
	free(*_prev);
	*_prev = _curr;
	return (1);
}
