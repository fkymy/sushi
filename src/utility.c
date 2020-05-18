#include "../include/sushi.h"

int		is_space(char c)
{
	return ((c == ' ' || c == '\t' || c == '\n' ||
				c == '\v' || c == '\f' || c == '\r') ? 1 : 0);
}

int		wc(char *str)
{
	int len;

	len = 0;
	while (*str)
	{
		if (is_space(*str))
			str++;
		else
		{
			len++;
			while (*str && !is_space(*str))
				str++;
		}
	}
	return (len);
}
