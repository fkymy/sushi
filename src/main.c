#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
/* #include <dict.h> */

#define TEXT "alice.txt"
#define LENGTH 45

int main(void)
{
	struct rusage before, after;
	double time_load = 0.0, time_mimic = 0.0;

	char *text = TEXT;
	if ((FILE *file = fopen(text, "r")) == NULL)
	{
		printf("Could not open %s\n", text);
		// unload();
		return (1);
	}

	// fgetc (try mallocing every word)
	// or read entire file and split

	if (ferror(file))
	{
		fclose(file);
		printf("Error reading %s\n", text);
		return (1);
	}
	fclose(file);
	// unload()

	return (0);
}
