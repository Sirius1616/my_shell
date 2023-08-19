#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @heads: address of pointer to head node
 * @strr: str field of node
 * @nums: node index used by history
 *
 * Return: size of list
 */


list_t *insert_node(t_list **hd, const char *strr, int nums)
{
	t_list *nw_hd;

	if (!hd)
		return (NULL);

	nw_hd = malloc(sizeof(t_list));
	if (!nw_hd)
		return (NULL);

	nw_hd->num = nums;
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
 * add_node_end - adds a node to the end of the list
 * @heads: address of pointer to head node
 * @strr: str field of node
 * @nums: node index used by history
 *
 * Return: size of list
 */

list_t *insert_node_end(t_list **hd, const char *strr, int nums)
{
	t_list *nw_node;

	if (!hd)
		return (NULL);

	nw_node = malloc(sizeof(t_list));
	if (!nw_node)
		return (NULL);

	nw_node->num = nums;
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
 * print_list_str - prints only the str element of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
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
 * delete_node_at_index - deletes node at given index
 * @heads: address of pointer to first node
 * @_index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */


int rem_node_at_index(t_list **hd, unsigned int _index)
{
	t_list *current, previous;
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
 * free_list - frees all nodes of a list
 * @heads_ptr: address of pointer to head node
 *
 * Return: void
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
