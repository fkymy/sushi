#include "../include/sushi.h"
#include "../include/terminal.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"

// TODO: allow multiple rounds
static size_t allocations = 0;
static char **str_store = NULL;

char	*read_fd(int ifd, size_t *size);

void	play(Dict dict);

char	*get_str(const char *prompt);

double	calculate(const struct rusage *b, const struct rusage *a);

void	teardown_str(void);

void	welcome(void);

void	goodbye(void);

int		main(int argc, char *argv[])
{
	char			*filename;
	char			*data;
	int				ifd;
	size_t			size;
	char			**strs;
	Dict			dict;

	filename = (argc == 2) ? argv[1] : TEXT;
	if ((ifd = open(filename, O_RDWR, 0)) == -1)
	{
		printf("error opening file\n");
		return (1);
	}
	data = read_fd(ifd, &size);
	strs = txtsplit(data);
	dict = load_dict(strs);
	free(data);
	for (int i = 0; strs[i]; i++)
		free(strs[i]);
	free(strs);
	play(dict);
	dict_destroy(dict);
	close(ifd);
	return (0);
}

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

void	play(Dict dict)
{
	struct	timeval start, end;
	long	seconds;
	long	micros;
	char	**mimic_strs;
	char	*mimic_str;
	char	*user_input;

	welcome();
	mimic_strs = mimic(dict, 13, " ");
	mimic_str = txtjoin(13, mimic_strs, " ");
	printf("Type: %s\n", mimic_str);
	gettimeofday(&start, NULL);
	user_input = get_str(" > ");
	gettimeofday(&end, NULL);
	tm_clear();
	if (txtcmp(mimic_str, user_input) == 0)
	{
		printf("Great job <3\n");
		seconds = (end.tv_sec - start.tv_sec);
		micros = (((seconds * 1000000) + end.tv_usec) - (start.tv_usec)) / 10000;
		printf("Time taken is %ld seconds or %ld micros\n", seconds, micros);
		printf("Hit ENTER to exit...");
		tm_wait();
		tm_clear();
	}
	else
	{
		printf("Sorry, you typed the wrong thing.");
		tm_wait();
		printf("Hit ENTER to exit...");
		tm_clear();
	}
	for (int j = 0; mimic_strs[j]; j++)
		free(mimic_strs[j]);
	free(mimic_strs);
	free(mimic_str);
	teardown_str();
}

// TODO: allow va_list and format prompt
char	*get_str(const char *prompt)
{
	char	*buffer = NULL;
	size_t	capacity = 0;
	size_t	size = 0;
	int		c;

	if (allocations == SIZE_MAX / sizeof(char *))
		return (NULL);
	printf(prompt);
	while ((c = fgetc(stdin)) != '\n' && c != EOF)
	{
		if (size + 1 > capacity)
		{
			if (capacity < SIZE_MAX)
				capacity++;
			else
			{
				free(buffer);
				return (NULL);
			}
			char *tmp = realloc(buffer, capacity);
			if (tmp == NULL)
			{
				free(buffer);
				return (NULL);
			}
			buffer = tmp;
		}
		buffer[size++] = c;
	}
	if (size == 0 && c == EOF)
		return (NULL);
	if (size == SIZE_MAX)
	{
		free(buffer);
		return (NULL);
	}
	char *str = realloc(buffer, size + 1);
	if (str == NULL)
	{
		free(buffer);
		return (NULL);
	}
	str[size] = '\0';
	char **temp = realloc(str_store, sizeof(char *) * (allocations + 1));
	if (temp == NULL)
	{
		free(str);
		return (NULL);
	}
	str_store = temp;
	str_store[allocations] = str;
	allocations++;
	return (str);
}

double	calculate(const struct rusage *b, const struct rusage *a)
{
	if (b == NULL || a == NULL)
	{
		return 0.0;
	}
	else
	{
		return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
				  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
				 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
				  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
				/ 1000000.0);
	}
}

void teardown_str(void)
{
	if (str_store != NULL)
	{
		for (size_t i = 0; i < allocations; i++)
			free(str_store[i]);
		free(str_store);
	}
}

void	welcome(void)
{
	tm_clear();
	printf("Sushida in Wonderland\n\nHit ENTER to continue...");
	tm_wait();
	tm_clear();
	printf("How to play: \n(1)Type the exact phrase displyed\n(2)Press ENTER when finished.\n(3)That's pretty much it... sorry i didn't have enogh time\n\nHit ENTER to start!");
	tm_wait();
	tm_clear();
}

void	goodbye(void)
{
	tm_clear();
	printf("Your time: 5.3 seconds. Goodbye.\n\nHit ENTER to exit...");
	tm_wait();
}

#pragma GCC diagnostic pop
