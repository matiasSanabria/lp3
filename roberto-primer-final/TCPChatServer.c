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
#include "PTI_functions/socketServer.h"

int TCPdaytimed(int fd);

#define QLEN 5
#define LINELEN 1024


int main(int argc, char *argv[]){

  struct sockaddr_in fsin;	/* the from address of a client	*/
    char *service = "15000";	/* service name or port number	*/
    int	msock, ssock;		/* master & slave sockets	*/
    int	alen;			/* from-address length		*/
	
	char mensaje[LINELEN]; //variable mensjae en donde se guarda el mensaje recibido por los clientes
	char salir[] = "exit";
	
	//aqui inicializamos las variables posibles 
	char mensaje1[] = "enviado 200 - OK";
	char mensaje2[] = "recibido 200 - OK";
	
	char mensaje3[] = "enviado 400 - Bad Request";
	char mensaje4[] = "recibido 400 - Registered";
	
	char mensaje5[] = "500 - Internal Error.";
	
	int estado = 0; // 0 = todavia no se dio una respuesta , 1 = si ya se dio una respuesta
	
	int cc;
	char *p;

    switch (argc) {
    case	1:
            break;
    case	2:
            service = argv[1];
            break;
    default:
            printf("uso: TCPTimeServer[puerto]\n");
            exit(1);
    }

    msock = tcpSocket(service, QLEN); //se reserva un socket utilizando el protocolo tcp teniendo como tamanho de cola 5 en el puerto service

    
    
    
    while (1) {
      
	
        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);//utilizando el socket msock, tambien la estructura de direccion del cliente sockaddr y su tamanho alen
        if (ssock < 0){//si se produjo un error al procesar los datos
            printf("Fallo en el accept: %s\n", strerror(errno));
            exit(1);
        }
		while (1){
			estado = 0;//una bandera para controlar si se enviaron respuestas del caso 1 2 o 3
			cc = read(ssock, mensaje, sizeof(mensaje));//se lee el mensaje recibido en el socket ssock y se guarda en mensaje
			//Borrar el "\n"
			p = strchr(mensaje, '\n');
		  	if (p)
				*p = '\0';
			if(strcmp(salir,mensaje)==0){//si el mensaje fue salir, entonces se sale
				break;
			}

			//imprime fecha y hora
			
			time_t tiempo = time(0);
			struct tm *tlocal = localtime(&tiempo);
			char output[128];
			strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
			printf("Se recibe y responde datos el: %s\n",output);
			
			printf("Servidor ahora recibe: %s \n", mensaje);
			// aqui comenzamos el analisis para saber que nos envio el cliente para dar una respuesta respectica a su caso
			
			// recibe el servidor mensaje 1 y responde mensaje 2  
			if(estado == 0){
				if(strcmp(mensaje1, mensaje)==0 && estado == 0){
					//printf("Es caso 1\n");
					printf("Servidor ahora responde: %s \n\n\n", mensaje2);	
					(void) write(ssock, mensaje2, sizeof(mensaje2));
					estado = 1;//se marca la respuesta
				}else{
					//printf("no es caso 1\n");
				}
			}
			
			//recibe el servidor mensaje 3 y responde mensaje 4 
			if(estado == 0){
				if(strcmp(mensaje3, mensaje)==0 ){
					//printf("Es caso 2\n");
					printf("Servidor ahora responde: %s \n\n\n", mensaje4);	
					(void) write(ssock, mensaje4, sizeof(mensaje4));
					estado = 1;//se marca la respuesta
				}else{
					//printf("no es caso 2\n");
				}
			}
			//recibe el servidor un mensaje que no conoce entonces envia el mensaje 5
			if(estado == 0){
				if(estado == 0) {
					//printf("Es caso 3\n");
					printf("Servidor ahora responde: %s \n\n\n", mensaje5);	
					(void) write(ssock, mensaje5, sizeof(mensaje5));
				}else{
					//printf("no es caso 3??\n");
				}
			  
			}
			
		}
        (void) close(ssock);//se libera el socket ssock que fue reservado
    }
	exit(0);
}