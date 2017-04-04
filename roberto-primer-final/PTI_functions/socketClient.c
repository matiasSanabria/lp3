/* socketClient.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include "socketClient.h"


/*------------------------------------------------------------------------
 * connectsock - crea y conecta un socket usando TCP o UDP
 *------------------------------------------------------------------------
 */
int connectsock(char *host, char *service, char *protocol )
{
    struct hostent *phe;	/* puntero a la información del host*/
    struct servent *pse;	/* puntero a la información del servicio*/
    struct protoent *ppe;	/* puntero a la información del potocolo*/
    struct sockaddr_in sin;	/* dirección*/
    int	s, type;            /* descriptor del socket y tipo*/


    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;

    /* Obtener puntero al servicio */
    if ( pse = getservbyname(service, protocol) )
            sin.sin_port = pse->s_port;
    else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 ){
        printf("No se encuentra la entrada del servicio \"%s\" \n", service);
        exit(1);
    }

    /* Obtener la IP de acuerdo al hostname*/
    if ( phe = gethostbyname(host) )
            bcopy(phe->h_addr, (char *)&sin.sin_addr, phe->h_length);
    else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE ){
        printf("No se encuentra el host \"%s\" \n", host);
        exit(1);
    }

    /* Obtener puntero al protocolo */
    if ( (ppe = getprotobyname(protocol)) == 0){
        printf("No se encuentra la entrada al protocolo \"%s\" \n", protocol);
        exit(1);
    }

    /* Selección del tipo de protocolo */
    if (strcmp(protocol, "udp") == 0)
            type = SOCK_DGRAM;
    else
            type = SOCK_STREAM;

    /* Creación del socket*/
    s = socket(PF_INET, type, ppe->p_proto);
    if (s < 0){
        printf("No se puede crear socket: %s\n", strerror(errno));
        exit(1);
    }

    /* Connect */
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0){
        printf("No se puede hacer connect a %s.%s: %s\n", host, service, strerror(errno));
        exit(1);
    }
    return s;
}

/*------------------------------------------------------------------------
 * connectUDP - realiza conexión a un servicio UDP en el host especificado
 *------------------------------------------------------------------------
 */
int connectUDP(char *host, char *service )
{
    return connectsock(host, service, "udp");
}

/*------------------------------------------------------------------------
 * connectTCP - realiza conexión a un servicio TCP en el host especificado
 *------------------------------------------------------------------------
 */
int connectTCP(char *host, char *service )
{
    return connectsock(host, service, "tcp");
}
