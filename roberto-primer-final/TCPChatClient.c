/* 
 * NO ES MULTI HILOOOO :'C
 * CUANDO COMENZE LA DOCUMENTACION ME DI CUENTA :'(
*/
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

#define LINELEN 1024


int main(int argc, char *argv[]){
	int intervalo  = 5; //intervalo de cada n segundos enviar datos al servidor 
	char *host = "localhost";	/* host to use if none supplied	*/
	char *service = "15000";	/* default service name		*/
	time_t	now;			/* 32-bit integer to hold time	*/
	int s, n;			/* socket descriptor, read count*/
	char retorno[LINELEN];//definicion de la variable retorno en donde se almacenara la respuesta del servidor
	char mensaje[LINELEN];//variable mensaje que almancena el mensaje a enviar, en nuestro caso utilizaremos propias variables
	
	char *p;
	
	//aqui inicializamos las variables posibles 
	char mensaje1[] = "enviado 200 - OK";
	char mensaje2[] = "recibido 200 - OK";
	
	char mensaje3[] = "enviado 400 - Bad Request";
	char mensaje4[] = "recibido 400 - Registered";
	
	char mensaje5[] = "500 - Internal Error.";
	char mensaje6[] = "CualquierCosa :D";
	
	
	switch (argc) {//analizamos si se dieron argumentos para iniciar el cliente
	case 1:
		host = "localhost";
		break;
	case 3:
		service = argv[2];
	case 2:
		host = argv[1];
		break;
	default:
		fprintf(stderr, "uso: TCPTimeClient [host [puerto]]\n");
		exit(1);
	}
	int numero = 0;
	s = connectTCP(host, service);//iniciamos el socket conectandonos a la ip host y el puerto service 
	while(1){
		
		//imprime fecha y hora
			
		time_t tiempo = time(0);
		struct tm *tlocal = localtime(&tiempo);
		char output[128];
		strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
		printf("Se envia y recibe datos el: %s\n",output);
			
		// aqui sorteamos que enviarle al servidor, mensaje ok, mensaje error o cualquier cosa
		numero = rand () % 3 ;
		
		if(numero == 0){
			printf("El cliente envia: %s\n", mensaje1);
			(void) write(s, mensaje1, LINELEN);//en la variable mensaje se encuentra el mensaje a enviar
			  
		}
		if(numero == 1){
			printf("El cliente envia: %s\n", mensaje3);
			(void) write(s, mensaje3, LINELEN);//en la variable mensaje se encuentra el mensaje a enviar
			
		}
		if(numero == 2){
			printf("El cliente envia: %s\n", mensaje6);
			(void) write(s, mensaje6, LINELEN);//en la variable mensaje se encuentra el mensaje a enviar
		}
		

		// Leer la respuesta del servidor 
		n = read(s, (char *)&retorno, sizeof(retorno));
		if (n < 0){
		        printf("Fallo del read \"%s\" \n", strerror(errno));
		        exit(1);
		}
		printf("El Cliente recibe: %s \nDurmiendo %d segundos...\n\n\n", retorno, intervalo);
		
		sleep(intervalo);//hacemos dormir el proceso por intervalo segundos
		
	}
	
	exit(0);
}