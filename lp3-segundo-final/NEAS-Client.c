/* TCPEchoClient.c - main */

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
#include "PTI_functions/socketClient.h"

#define OK           "enviado 200 - OK         "
#define ERROR        "enviado 400 - Bad Request"
#define OTRO_MENSAJE "enviando otro mensaje    "
#define INTERVALO 5 //para que el proceso envie cada 3 segundos el mensaje
#define MAX_LEN 1024 //longitud maxima del mensaje que se envia y recibe


int main(int argc, char *argv[])
{
	char *host = "localhost";	/* host usado por default	*/
	char *service = "31000";	/* puerto default del servicio*/
	char buf[BUFSIZ];		/*buffer de escritura*/
	int s, n;			/* descriptor de socket, counter del read*/
	char respuesta[MAX_LEN]; /*definicion de la variable retorno en donde se almacenara la respuesta del servidor*/
    time_t t;
    int i = 0;
    
	s = connectTCP(host, service); /* iniciamos el socket, nos conectamos al host y al servicio*/
    
    while(1){

		/*mostramos la fecha y hora*/
		time_t tiempo = time(0);
		struct tm *tlocal = localtime(&tiempo);
		char output[128];
		strftime(output,128,"%d/%m/%y %H:%M:%S\n",tlocal);
		printf("\nSe envia y recibe datos el: %s",output);

	    srand((unsigned) time(&t));
	    i = rand() % 3;
	    
	    switch(i){
	        case 0:
	        	printf("Enviado: %s",OK);
	        	strcpy(buf,OK);
		        break;
		    case 1:
		        printf("Enviado: %s",ERROR);
		        strcpy(buf,ERROR);
		        break;
		    case 2:
		    	printf("Enviado: %s",OTRO_MENSAJE);
		    	strcpy(buf,OTRO_MENSAJE);
		        break;
	    }
	    /* enviamos el mensaje al servidor */
	    (void) write(s, buf, strlen(buf));
	    strcpy(buf,"");
	    
		/* Leer la respuesta */
	
		n = read(s, (char *)respuesta, sizeof(respuesta));
	
		if (n < 0){
	        printf("Fallo del read \"%s\" \n", strerror(errno));
	        exit(1);
	    }
		printf("\nRecibido: %s \nDurmiendo %d segundos...\n", respuesta, INTERVALO);
		sleep(INTERVALO); //hacemos dormir el proceso por intervalo segundos
    }

	exit(0);
}
