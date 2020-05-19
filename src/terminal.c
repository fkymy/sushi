#include "../include/sushi.h"
#include "../include/terminal.h"
#include <sys/ioctl.h>
#include <termios.h>

void tm_welcome(void)
{
	return ;
}

void tm_settitle(char *title)
{
	printf(ESC"]0;%s\x7", title);
}

void tm_wait(void)
{
    while (fgetc(stdin) != '\n');
}

void tm_clear(void)
{
    printf(ESC"[2J"ESC"[?6h");
}

void tm_resetcolors(void){
    printf(ESC"001b"ESC"[0m");
}
