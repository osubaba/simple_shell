#include "main.h"

/**
 * get_num_l - Get the length of an integer.
 * @n: An integer.
 *
 * Return: Length of the integer.
 */
int get_num_l(int n)
{
	unsigned int num = (n < 0) ? -n : n;
	int l = 1;

	while (num > 9)
	{
		l++;
		num /= 10;
	}

	if (n < 0)
		l++; /* Account for the negative sign */

	return (l);
}

/**
 * aux_itoa - Convert an integer to a string.
 * @n: An integer.
 *
 * Return: The string representation of the integer.
 */
char *aux_itoa(int n)
{
	unsigned int num = (n < 0) ? -n : n;
	int l = get_num_l(n);
	char *buf = malloc(sizeof(char) * (l + 1));

	if (buf == NULL)
		return (NULL);

	buf[l] = '\0';

	if (n < 0)
	{
		buf[0] = '-';
		num = -n;
	}

	l--;

	do {
		buf[l] = (num % 10) + '0';
		num /= 10;
		l--;
	} while (num > 0);

	return (buf);
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The input string.
 *
 * Return: The integer representation of the string.
 */
int _atoi(char *s)
{
	unsigned int c = 0, l = 0, res = 0, sign = 1, m = 1, i;

	while (s[c] != '\0')
	{
		if (l > 0 && (s[c] < '0' || s[c] > '9'))
			break;

		if (s[c] == '-')
			sign *= -1;

		if (s[c] >= '0' && s[c] <= '9')
		{
			if (l > 0)
				m *= 10;
			l++;
		}
		c++;
	}

	for (i = c - l; i < c; i++)
	{
		res += (s[i] - '0') * m;
		m /= 10;
	}

	return (res * sign);
}

