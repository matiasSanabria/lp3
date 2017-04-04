#include "hardware_timer.h"

/*
 * Configura un manejador de senhales para que capture el SIGALRM 
 * llamando a sigaction
 * Si tiene exito, retorna 0, en caso contrario retorna -1 y establece
 * a errno
 */
int catchsetup(void (*handler)(void)){

    struct sigaction alarm;
    act.sa_handler = handler;
    act.sa_flags = 0;
    if((sigemptyset(&alarm.sa_mask) == -1)
        || (sigaction(SIGALRM, &alarm, NULL) == -1)){
        perror("Fallo al establecer SIGALRM con el manejador");
        return -1;
    }
    return 0;
}

void sethardwaretimer(long interval){
    struct itimerval value;
    value.it_interval.tv_sec = 2;
    value.it_interval.tv_usec = 0;
    value.it_value = value.it_interval;
    return (setitimer(ITIMER_REAL, &value, NULL));
}


void waitforinterrupt(void){
    static volatile sig_atomic_t sigreceived = 0;
    
    sigset_t masknew, maskold;
    int signum = SIGINT;

    sigprocmask(SIG_SETMASK, NULL, &masknew);
    sigaddset(&masknew, signum);
    sigprocmask(SIG_SETMASK, &masknew, &maskold);
    sigdelset(&masknew, signum);
    if(sigreceived == 0){
        sigsuspend(&masknew);
    }
    sigprocmask(SIG_SETMASK, &maskold, NULL);
}

static void timerhandler(void){
    int i = 0;
    
    while(i < strlen(timers.events)){
        i++;
    }
    timers.events[i] = timers.running;
    timers.running = -1;
}