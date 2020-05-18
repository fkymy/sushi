#include "../include/sushi.h"

char	**txtsplit(char *str)
{
	char	**res;
	int		size;
	int		len;
	int i;
	int j;
	int k;

	size = wc(str);
	if (!(res = malloc(sizeof(char *) * size + 1)))
		return (NULL);
	len = 0;
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		while (str[i] && is_space(str[i]))
			i++;
		while (str[i] && !is_space(str[i]))
		{
			len++;
			i++;
		}
		if (!(res[j] = malloc(sizeof(char) * len + 1)))
			return (NULL);
		k = 0;
		while (len)
			res[j][k++] = str[i - len--];
		res[j++][k] = '\0';
	}
	res[j] = NULL;
	return (res);
}
