#include "hardware_timer.h"
#define MAXTIMERS 5

typedef struct timerdata_t {
    long active[MAXTIMERS];
    int events[MAXTIMERS];
    int numevents;
    int running;
} timerdata_t;

int getevent(int eventnumber);
int getnumevents(void);
int getrunning(void);
long getvalue(int n);
int removetop(void);
int timerinit(void);
void timerstart(int n, long interval);
void timerstop(int n);
void waitforevent(void);
static void timerhandler(void);