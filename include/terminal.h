#ifndef TERMINAL_H
# define TERMINAL_H
# include <sys/ioctl.h>
# include <termios.h>
# include <unistd.h>

# define ESC "\x1b"

void tm_welcome(void);
void tm_settitle(char *title);
void tm_wait(void);
void tm_clear(void);

#endif
