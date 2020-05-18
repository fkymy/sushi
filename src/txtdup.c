#include "../include/sushi.h"

char	*txtdup(char *buf, int size)
{
	char	*res;
	int		i;

	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = buf[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
