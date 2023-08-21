#include "shell.h"

/**
 * len_list - a function that gets linked list length
 * @hd: 1stnode pointer
 * Return: list length
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
 * list_strings_conv  - gets the array of the linked list
 * @hd: 1st node pointer
 * Return: strings array
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
 * put_list - all the elements are written out
 * @hd: 1st node pointer
 * Return: list length
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
 * begin_node - node whose string begins with prefix is displayed
 * @nodes: list head ptr
 * @pref: matched string
 * @ch: next xter after matched prefix
 * Return: null or matched node
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
 * set_node_index - a function that gets node's index
 * @heads: list head ptr
 * @nodes: node ptr
 * Return: -1 or node index
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
