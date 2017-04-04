#include "virtualtimers.h"
#include "hardwaretimer.h"
#include "show.h"

struct timerdata_t timers;

/*
 * Retorna el numero del temporizador asociado con una entrada particular
 * en el array events.
 * Si eventnumber es negativo o mayor a 4 se retorna -1
 */
int getevent(int eventnumber){
    if((eventnumber < 0) || (eventnumber > 4)){
        return -1;
    }
    return timers.events[event_number];
}

/*
 * Retorna el valor de la cantidad de eventos
 */
int getnumevents(void){
    return timers.num_events;
}

/*
 * Retorna el numero de temporizador que esta corriendo o -1 si no 
 * esta corriendo ninguno
 */
int getrunning(void){
    if(timer.running == -1){
        return -1;
    }
    return timers.running;
}

/*
 * Elimina el elemento que se encuentra en la parte superior y se devuelve el
 * numero del temporizador
 * Si el array events esta vacio se retorna -1
 */
int removetop(void){
    int i = 0;
    if(timer.events[0] == -1){
        return -1;
    }
    
    while(i < strlen(timer.events)){
        if(timer.events[i] == -1){
            break;
        }
        i++;
    }
    int temp = timers.events[i];
    timers.events[i] = -1;
    return temp;
}

/*
 * Inicializa la estructura de datos timers. La funcion tambien llama a 
 * catchsetup del objeto hardwaretimer y showinit del objeto show
 * Si tiene exito, timerinit retorna 0, si no tiene exito timerinit retorna -1
 * y establece a errno
 */
int timerinit(void){
    timers.running = -1;
    int i;
    for(i = 0; i < 5; i++){
        timers.active[i] = -1;
    }
    timers.num_events = 0;
    for(i = 0; i < 5; i++){
        timers.events[i] = -1;
    }
    if(catchsetup() == -1)
        fprintf(stderr, "Error al iniciar el temporizador", n);
        return -1;
    else
        return 0;
    if(showinit(interval) != 0)
        fprintf(stderr, "Error al iniciar el temporizador ", n);
        return -1;
    else
        return 0;
}

/*
 * Inicia el temporizador n con el intervalo de tiempo en microsegundos.
 * Para esta parte, asumimos que no hay temporizadores activos.
 * El interval es el numero de microsegundos despues de que el temporizador
 * debe expirar
 */
void timerstart(int n, long interval){
    timers.events[n] = -1;
    timers.running = n;
    timers.active[n] = interval;
    timers.num_events = -1;
    sethardwaretimer();

}

/*
 * Detiene el temporizador n si es que esta activo y elimina el temporizador de
 * events si esta alli.
 */
void timerstop(int n){
    if(timers.active[n] != -1){
        timers.running = -1;
        timers.events[n] = -1;
        timers.active[n] = -1;
    }
}

/*
 * Espera hasta que haya un evento en events y retorna sin cambiar nada 
 */
void waitforevent(void){
    if(timers.events[0] == -1)
        waitforinterrupt();
}

/*
 * Esta funcion es llamada por el actual manejador de senhales en 
 * hardwaretimer para mantener la estructura de timers cuando el hardware
 * del temporizador real expira
 */
static void timerhandler(void){
    int i = 0;
    
    while(i < strlen(timers.events)){
        i++;
    }
    timers.events[i] = timers.running;
    timers.running = -1;
}