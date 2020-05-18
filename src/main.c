#include "../include/sushi.h"

char	*read_fd(int ifd, size_t *size)
{
	int		n;
	char	buf[S_BUFSIZ + 1];
	char	*data;
	char	*old;

	data = NULL;
	n = 0;
	while ((n = read(ifd, buf, S_BUFSIZ)) > 0)
	{
		buf[n] = '\0';
		if (data == NULL)
			data = txtdup(buf, n);
		else
		{
			old = data;
			data = txtcat(data, buf, *size, n);
			free(old);
		}
		*size += n;
	}
	return (data);
}

int		main(int argc, char *argv[])
{
	char			*filename;
	char			*data;
	int				ifd;
	size_t			size;
	char			**strs;
	Dict			dict;
	char			**mimic_strs;
	char			*mimic_str;

	filename = (argc == 2) ? argv[1] : TEXT;
	printf("opening %s!\n", filename);
	if ((ifd = open(filename, O_RDWR, 0)) == -1)
	{
		printf("error opening file\n");
		return (1);
	}
	data = read_fd(ifd, &size);
	strs = txtsplit(data);
	dict = load_dict(strs);

	// mimic
	mimic_strs = mimic(dict, 13, " ");
	mimic_str = txtjoin(13, mimic_strs, " ");
	printf("%s\n", mimic_str);

	free(data);
	for (int i = 0; strs[i]; i++)
		free(strs[i]);
	free(strs);
	for (int j = 0; mimic_strs[j]; j++)
		free(mimic_strs[j]);
	free(mimic_strs);
	free(mimic_str);
	dict_destroy(dict);
	close(ifd);

	return (0);
}
