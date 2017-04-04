#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include "PTI_functions/socketServer.h"

#define	QLEN		  32	/* tamanho de cola del servidor	*/
#define	BUFSIZE		4096

#define	INTERVAL	5	/* secs */
#define OK            "enviado 200 - OK         " /* mensaje OK del cliente */
#define OKS           "recibido 200 - OK        " /* mensaje OK del servidor */
#define ERROR         "enviado 400 - Bad Request" /* mensaje ERROR del cliente */
#define ERRORS        "recibido 400 - Registered" /*mensaje ERROR del servidor */
#define ERROR_INTERNO "500 - Internal Error     " /* mensaje de ERROR INTERNO del servidor*/

struct {
	pthread_mutex_t	st_mutex;
	unsigned int	st_concount; 
	unsigned int	st_contotal;
	unsigned long	st_contime;
	unsigned long	st_bytecount;
} stats;

void prstats(void);
int	TCPechod(int fd);

/*------------------------------------------------------------------------
 * main - Servidor concurrente para servicio echo
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	pthread_t th;
	pthread_attr_t ta;
	char *service = "31000";	/* puerto del servicio	*/
	struct sockaddr_in fsin;	/* direccion del cliente	*/
	unsigned int alen;		/* longitud de la direccion del cliente	*/
    int	msock;			/* socket del master */
    int	ssock;			/* socket de esclavo */

	printf("Iniciando Servicio en el puerto %s...\n", service);
	msock = tcpSocket(service, QLEN);

	(void) pthread_attr_init(&ta);
	(void) pthread_attr_setdetachstate(&ta, PTHREAD_CREATE_DETACHED);
	(void) pthread_mutex_init(&stats.st_mutex, 0);
	
	while (1) {
		alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		if (ssock < 0) {
			if (errno == EINTR)
				continue;
			printf("accept: %s\n", strerror(errno));
			exit(1);
		}
		if (pthread_create(&th, &ta, (void * (*)(void *))TCPechod,(void *)ssock) < 0)
		{
			printf("pthread_create: %s\n", strerror(errno));
			exit(1);
		}
	}
}

/*------------------------------------------------------------------------
 * TCPechod - echo de los datos recibidos
 *------------------------------------------------------------------------
 */
int TCPechod(int fd)
{
	time_t	start;
	int	cc;
	char mensaje[BUFSIZE];

	start = time(0);

	while(1){
		memset(mensaje,0,24);
		cc = read(fd, mensaje, sizeof(mensaje));//se lee el mensaje recibido en el socket ssock y se guarda en mensaje
		
		/*imprime fecha y hora*/
				
		time_t tiempo = time(0);
		struct tm *tlocal = localtime(&tiempo);
		char output[128];
		
		strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
		printf("\nSe recibe y responde datos el: %s\n",output);
		printf("Recibido: %s \n", mensaje);
		
		/* vemos que tipo de mensaje fue recibido y de acuerdo a ello para responder al cliente */
		if(strcmp(OK, mensaje) == 0){ /* si se recibio OK */
			printf("Enviado: %s \n", OKS);	
			(void) write(fd, OKS, sizeof(OKS));
			
		}else if(strcmp(ERROR, mensaje) == 0){ /* si se recibio ERROR */
			printf("Enviado: %s \n", ERRORS);	
			(void) write(fd, ERRORS, sizeof(ERRORS));
		}else{	/* si no se reconoce el mensaje */
			printf("Enviado: %s\n", ERROR_INTERNO);
			(void) write(fd, ERROR_INTERNO, sizeof(ERROR_INTERNO));
		}
		
	}

	close(fd);
	return 0;
}
