#include <signal.h>

int catchsetup(void (*handler)(void));
void sethardwaretimer(long interval);
void waitforinterrupt(void);