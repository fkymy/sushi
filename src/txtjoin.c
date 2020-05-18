#include "../include/sushi.h"

int		txtlen(int size, char **strs, char *sep);

char	*txtjoin(int size, char **strs, char *sep)
{
	char	*res;
	int		index;
	int		i;
	int		j;
	int		k;

	res = malloc(txtlen(size, strs, sep) * 1);
	if (size == 0)
		return (res);
	index = -1;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (strs[i][++j])
			res[++index] = strs[i][j];
		k = -1;
		while (i < size - 1 && sep[++k])
			res[++index] = sep[k];
	}
	res[++index] = '\0';
	return (res);
}

int		txtlen(int size, char **strs, char *sep)
{
	int mem_len;
	int i;
	int j;
	int k;

	mem_len = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
		{
			mem_len++;
			j++;
		}
		i++;
	}
	k = 0;
	while (sep[k])
		k++;
	mem_len += k * (size - 1);
	return (mem_len * 1);
}
/*  */
/* int		main(void) */
/* { */
/* 	char *strs[] = { "Stay", "awhile", "you", "are", "so", "beautiful" }; */
/* 	char *sep = "_______"; */
/* 	char *res = ft_strjoin(6, strs, sep); */
/* 	int i = -1; */
/* 	while (res[++i]) */
/* 		write(1, &res[i], 1); */
/* 	return (0); */
/* } */
