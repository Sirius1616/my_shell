#include "shell.h"

/**
 * list_len - determines length of linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */

size_t len_list(const t_list *hd)
{
	size_t cnt = 0;

	for (; hd; hd = hd->next)
	{
		cnt++;
	}

	return (cnt);
}


/**
 * list_to_strings - returns an array of strings of the list->str
 * @heads: pointer to first node
 * Return: array of strings
 */


char **list_strings_conv(t_list *hd)
{
	size_t i, j, length = 0;
	char **str_array;
	list_t *node = hd;

	while (node)
	{
		length++;
		node = node->next;
	}

	str_array = malloc(sizeof(char *) * (length + 1));
	if (!str_array)
		return (NULL);

	node = hd;
	for (i = 0; i < length; i++)
	{
		str_array[i] = _strdup(node->str);
		if (!str_array[i])
		{
			for (j = 0; j < i; j++)
			{
				free(str_array[j]);
			}
			free(str_array);
			return (NULL);
		}
		node = node->next;
		}

		str_array[length] = NULL;

	return (str_array);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t put_list(const t_list *hd)
{
	size_t cnt = 0;

	for (; hd; hd = hd->next)
	{
		_puts(num_conv(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		cnt++;
	}

	return (cnt);
}


/**
 * node_starts_with - returns node whose string starts with prefix
 * @nodes: pointer to list head
 * @prefixes: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */


list_t *begin_node(t_list *nodes, char *pref, char ch)
{
	char *pt;

	for (; nodes; nodes = nodes->next)
	{
		pt = begins_with(nodes->str, pref);
		if (pt && (ch == -1 || *pt == ch))
		{
			return nodes;
		}
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @heads: pointer to list head
 * @nodes: pointer to the node
 *
 * Return: index of node or -1
 */


ssize_t set_node_index(t_list *hd, t_list *nodes)
{
	size_t index = 0;

	for (; hd; hd = hd->next, index++)
	{
		if (hd == nodes)
		{
			return (index);
		}
	}

	return (-1);
}
