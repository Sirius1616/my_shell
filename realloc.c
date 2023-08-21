#include "shell.h"

/**
 **_memset - a constant byte of memory is filled
 *@src: memory area pointer
 *@ch: the bytes to be used for filling
 *@m: filled byte amount
 *Return: the memory area pointer
 */

char *_memset(char *src, char ch, unsigned int m)
{
	unsigned int x = 0;

	while (x < m)
	{
		src[x] = ch;
		x++;
	}

	return (src);
}


/**
 * ffree - string of strings is freed
 * @ppl: strings' string
 */


void ffree(char **ppl)
{
	char **current, **aa = ppl;

	if (!ppl)
		return;

	for (current = ppl; *current != NULL; current++)
	{
		free(*current);
	}

	free(aa);
}

/**
 * _realloc - block of memory is reallocated
 * @ptrr: previous malloc'ated block ptr
 * @prev_sizee: previous block bytes size
 * @curr_sizee: new block byted size
 * Return: pointer to da ol'block nameen.
 */


void *_realloc(void *ptrr, unsigned int prev_sizee, unsigned int curr_sizee)
{
	char *pp;
	int dup, i;

	if (!ptrr)
		return (malloc(curr_sizee));

	if (!curr_sizee)
	{
		free(ptrr);
		return (NULL);
	}

	if (curr_sizee == prev_sizee)
		return (ptrr);

	pp = malloc(curr_sizee);
	if (!pp)
		return (NULL);

	dup = prev_sizee < curr_sizee ? prev_sizee : curr_sizee;
	for (i = 0; i < dup; i++)
		pp[i] = ((char *)ptrr)[i];

	free(ptrr);
	return (pp);
} 
