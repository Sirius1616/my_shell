#include "shell.h"

/**
 * **str_token - string is splited into word
 * @strr: string inputed
 * @dc: string delimiter
 * Return: array of string pointed to
 */

char **str_token(char *strr, char *dc) {
	int x, y, z, m, n_word = 0;
	char **st;

	if (strr == NULL || strr[0] == 0)
 		return (NULL);
	if (!dc)
	dc = " ";

	x = 0;
	while ( strr[x] != '\0')
	{
	if (!is_delimiter(strr[x], dc) && (is_delimiter(strr[x + 1], dc) || !strr[x + 1]))
		n_word++;
	x++;
	} 

	if (n_word == 0)
 	return (NULL);

	st = malloc((1 + n_word) * sizeof(char *));
	if (!st)
		return (NULL);

	x = 0;
	y = 0;
	while (y < n_word) {
 	while (is_delimiter(strr[x], dc))
		x++;
 	z = 0;
	while (!is_delimiter(strr[x + z], dc) && strr[x + z])
 		z++;
	st[y] = malloc((z + 1) * sizeof(char));
	if (!st[y]) {
		for (z = 0; z < y; z++)
	free(st[z]);
 		free(st);
 	return (NULL);
	}
	m = 0;
	while (m < z) {
		st[y][m] = strr[x++];
	m++;
	}
	st[y][m] = 0;
	y++;
	}
	st[y] = NULL;
	return (st);
}



/**
 * **str_token2 - word split from string
 * @strr: string inputed
 * @dc: delimeter
 * Return: an array of string is pointed to
 */


char **str_token2(char *strr, char dc)
{
	int x = 0, y = 0, z, m, n_word = 0;
	char **st;

	if (strr == NULL || strr[0] == 0)
		return (NULL);

	while (strr[x] != '\0') 
	{
	if ((strr[x] != dc && strr[x + 1] == dc) ||
		(strr[x] != dc && !strr[x + 1]) || strr[x + 1] == dc)
		n_word++;
	x++;
	}

	if (n_word == 0)
		return (NULL);

	st = malloc((1 + n_word) * sizeof(char *));
	if (!st)
		return (NULL);

	x = 0;
	y = 0;
	while (y < n_word)
	{
		while (strr[x] == dc)
			x++;

		z = 0;
		while (strr[x + z] != dc && strr[x + z] && strr[x + z] != dc)
			z++;

		st[y] = malloc((z + 1) * sizeof(char));
		if (!st[y])
		{
			for (z = 0; z < y; z++)
				free(st[z]);
			free(st);
			return (NULL);
		}

		m = 0;
		while (m < z) {
			st[y][m] = strr[x++];
		m++;
		}

		st[y][m] = 0;
	y++;
	}
	st[y] = NULL;
	return (st);
}
