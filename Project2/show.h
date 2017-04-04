#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "hardwaretimer.h"
#include "show.h"
#include "virtualtimers.h"
#define MILLION 1000000L

static double getrelativetime(void);
static double gettime(void);
static void showtimerdata(void);
static double timetodouble(long interval);
void show(int traceflag, const char *msg, long val1, long val2, int blockedflag);
void showinit(int maxt);