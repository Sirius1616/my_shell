#include "shell.h"

/**
 * free_add - address is Nullified after freeing ptr
 * @ptrr: pointer to free address
 * Return: 0 if not freed, otherwise 1.
 */

int free_add(void **ptrr)
{
	if (!ptrr || !*ptrr)
	{
		return (0);
	}

	free(*ptrr);
	*ptrr = NULL;
	return (1);
}
