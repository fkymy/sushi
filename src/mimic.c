#include "../include/sushi.h"

Dict	load_dict(char **strs)
{
	Dict d;
	int i;
	char *prev;

	d = dict_create();
	i = 0;
	prev = " ";
	while (strs[i])
	{
		dict_insert(d, prev, strs[i]);
		prev = strs[i];
		i++;
	}

	return (d);
}

char	**mimic(Dict d, int num, char *word)
{
	int i;
	int n;
	struct elt *head;
	char *current;
	char *random;
	char **result;

	i = 0;
	current = word;
	result = (char **)malloc(sizeof(char *) * (num + 1));
	while (i < num)
	{
		if (dict_search(d, current) == 0)
		{
			printf("dict_search returned 0\n");
			current = " ";
		}
		head = d->table[hash(current) % d->size];
		srand(time(NULL));
		random = head->value;
		n = 2;
		while (head != 0)
		{
			if (rand() % n == 0)
				random = head->value;
			head = head->next;
			n++;
		}
		current = random;
		result[i] = (char *)malloc(sizeof(char) * strlen(current));
		result[i] = strdup(current);
		i++;
		// trying
		/* if (result == NULL) */
		/* 	result = strdup(current); */
		/* else */
		/* { */
		/* 	old = result; */
		/* 	result = strcat(result, " "); */
		/* 	free(old); */
		/* 	old = result; */
		/* 	result = strcat(result, current); */
		/* 	free(old); */
		/* } */
	}
	result[i] = NULL;
	return (result);
}
