#include "shell.h"

/**
 * insert_node - a function that adds a node to the begining of a list
 * @hd: pointer to head node's adrress
 * @strr: str part of the node
 * @nums: history's node index
 * Return: list size
 */


t_list *insert_node(t_list **hd, const char *strr, int nums)
{
	t_list *nw_hd;

	if (!hd)
		return (NULL);

	nw_hd = malloc(sizeof(t_list));
	if (!nw_hd)
		return (NULL);

	nw_hd->number = nums;
	nw_hd->str = NULL;

	if (strr)
	{
		nw_hd->str = malloc(_strlen(strr) + 1);
		if (!nw_hd->str)
		{
			free(nw_hd);
			return (NULL);
		}
		_strcpy(nw_hd->str, strr);
	}

	nw_hd->next = *hd;
	*hd = nw_hd;

	return (nw_hd);
}

/**
 * insert_node_end - a function that adds to the list end a node
 * @hd: pointer to head node address
 * @strr: the string field
 * @nums: history's node index
 * Return: length of list
 */

t_list *insert_node_end(t_list **hd, const char *strr, int nums)
{
	t_list *nw_node;

	if (!hd)
		return (NULL);

	nw_node = malloc(sizeof(t_list));
	if (!nw_node)
		return (NULL);

	nw_node->number = nums;
	nw_node->str = NULL;

	if (strr)
	{
		nw_node->str = _strdup(strr);
		if (!nw_node->str)
		{
			free(nw_node);
			return (NULL);
		}
	}

	nw_node->next = NULL;

	if (*hd)
	{
		t_list *node = *hd;
		for (; node->next; node = node->next)
			;
		node->next = nw_node;
	}
	else
	{
		*hd = nw_node;
	}
	
	return (nw_node);
}

/**
 * put_list_str - the list element of the linked list is printed
 * @hd: 1st node's pointer
 * Return: list length
 */

size_t put_str_list(const t_list *hd)
{
	size_t cnt = 0;

	for (; hd; hd = hd->next)
	{
		if (hd->str)
		{
			_puts(hd->str);
		}
		else
		{
			_puts("(nil)");
		}
		_puts("\n");
		cnt++;
	}

	return (cnt);
}

/**
 * rem_node_at_index - given index node is removed
 * @hd: pointer to first node's address
 * @_index: index of node to remove
 * Return: 0 on failure 1, otherwise
 */


int rem_node_at_index(t_list **hd, unsigned int _index)
{
	t_list *current, *previous;
	unsigned int i;

	if (!hd || !_index)
		return (0);

	current = *hd;
	previous = NULL;

	for (i = 0; current; i++, previous = current, current = current->next)
	{
		if (i == _index)
		{
			if (previous)
			{
				previous->next = current->next;
			}
			else
			{
				*hd = current->next;
			}
			free(current->str);
			free(current);
			return (1);
		}
	}

	return (0);
}

/**
 * clear_list - all the nodes of the list is cleared
 * @heads_ptr: pointer to head node address
 * Return: nothing
 */

void clear_list(t_list **hd_ptr)
{
	t_list *next_node;

	if (!hd_ptr || !*hd_ptr)
		return;

	t_list *current = *hd_ptr;
	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}

	*hd_ptr = NULL;
}
