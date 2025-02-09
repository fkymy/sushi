#ifndef SUSHI_H
# define SUSHI_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdbool.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <fcntl.h>
# include <libgen.h>
# include <string.h>
# include <stdint.h>
# include <stdarg.h>
# include "dict.h"

# define TEXT "README"
# define S_BUFSIZ 1024
# define LENGTH 45

char	*txtcat(char *dest, char *buf, size_t size, size_t n);
char	*txtdup(char *buf, int size);
char	**txtsplit(char *str);
int		is_space(char c);
int		wc(char *str);
int		txtcmp(char *s1, char *s2);

Dict	load_dict(char **strs);
char	**mimic(Dict d, int num, char *word);
char	*txtjoin(int size, char **strs, char *sep);

#endif
