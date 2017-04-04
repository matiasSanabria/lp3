/* socketServer.c */
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include "socketServer.h"


u_short	portbase = 0;	/* puerto base*/

/*------------------------------------------------------------------------
 * socketServer - prepara y realiza el bind de un socket para un servidor, usando TCP o UDP
 *------------------------------------------------------------------------
 */
int socketServer(const char *service, const char *transport, int qlen)
/*
 * Argumentos:
 *      service   - servicio que se asocia al puerto
 *      transport - modo de transporte a usar ("tcp" o "udp")
 *      qlen      - tamanho maximo de la cola de requests del servidor
 * 	return    - el descriptor del socket
 */
{
    struct servent *pse;	// puntero a la informacion del servicio
    struct protoent *ppe;	// puntero a la informacion del protocolo
    struct sockaddr_in sin;	// direccion ip
    int	s, type;	// descriptor de socket y tipo

    memset(&sin, 0, sizeof(sin)); //reserva de memoria
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;

/* Busqueda del servicio por nombre*/
    if ( pse = getservbyname(service, transport) )
            sin.sin_port = htons(ntohs((u_short)pse->s_port) + portbase);
    else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 ){
        printf("No se encuentra la entrada del servicio \"%s\" \n", service);
        exit(1);
    }

/* Busqueda del protocolo*/
    if ( (ppe = getprotobyname(transport)) == 0){
        printf("No se encuentra la entrada al protocolo \"%s\" \n", transport);
        exit(1);
    }

/* Selcion del tipo de socket*/
    if (strcmp(transport, "udp") == 0)
            type = SOCK_DGRAM;
    else
            type = SOCK_STREAM;

/* Creacion de socket*/
    s = socket(PF_INET, type, ppe->p_proto);
    if (s < 0){
        printf("No se puede crear socket: %s\n", strerror(errno));
        exit(1);
    }

/* Bind del socket */
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0){
        printf("No se puede hacer bind %s: %s\n", service, strerror(errno));
        exit(1);
    }
    if (type == SOCK_STREAM && listen(s, qlen) < 0){
        printf("No se puede escuchar %s: %s\n", service,strerror(errno));
        exit(1);
    }
    return s;
}

/*------------------------------------------------------------------------
 * udpSocket - Crea un socket para un servidor UDP
 *------------------------------------------------------------------------
 */
int udpSocket( const char *service )
{
	return socketServer(service, "udp", 0);
}

/*------------------------------------------------------------------------
 * passiveTCP - create a passive socket for use in a TCP server
 *------------------------------------------------------------------------
 */
int tcpSocket(char *service, int qlen )
{
	return socketServer(service, "tcp", qlen);
}
