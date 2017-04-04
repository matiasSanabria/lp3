{"filter":false,"title":"TCPChatServer.c","tooltip":"/lp3-primer-final/TCPChatServer.c","undoManager":{"mark":0,"position":0,"stack":[[{"start":{"row":0,"column":0},"end":{"row":132,"column":1},"action":"insert","lines":["/* "," * NO ES MULTI HILOOOO :'C"," * CUANDO COMENZE LA DOCUMENTACION ME DI CUENTA :'(","*/","","#include <sys/socket.h>","#include <sys/types.h>","#include <netinet/in.h>","#include <netdb.h>","#include <stdio.h>","#include <time.h>","#include <string.h>","#include <unistd.h>","#include <errno.h>","#include <stdlib.h>","#include \"PTI_functions/socketServer.h\"","","int TCPdaytimed(int fd);","","#define QLEN 5","#define LINELEN 1024","","","int main(int argc, char *argv[]){","","  struct sockaddr_in fsin;\t/* the from address of a client\t*/","    char *service = \"15000\";\t/* service name or port number\t*/","    int\tmsock, ssock;\t\t/* master & slave sockets\t*/","    int\talen;\t\t\t/* from-address length\t\t*/","\t","\tchar mensaje[LINELEN]; //variable mensjae en donde se guarda el mensaje recibido por los clientes","\tchar salir[] = \"exit\";","\t","\t//aqui inicializamos las variables posibles ","\tchar mensaje1[] = \"enviado 200 - OK\";","\tchar mensaje2[] = \"recibido 200 - OK\";","\t","\tchar mensaje3[] = \"enviado 400 - Bad Request\";","\tchar mensaje4[] = \"recibido 400 - Registered\";","\t","\tchar mensaje5[] = \"500 - Internal Error.\";","\t","\tint estado = 0; // 0 = todavia no se dio una respuesta , 1 = si ya se dio una respuesta","\t","\tint cc;","\tchar *p;","","    switch (argc) {","    case\t1:","            break;","    case\t2:","            service = argv[1];","            break;","    default:","            printf(\"uso: TCPTimeServer[puerto]\\n\");","            exit(1);","    }","","    msock = tcpSocket(service, QLEN); //se reserva un socket utilizando el protocolo tcp teniendo como tamanho de cola 5 en el puerto service","","    ","    ","    ","    while (1) {","      ","\t","        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);//utilizando el socket msock, tambien la estructura de direccion del cliente sockaddr y su tamanho alen","        if (ssock < 0){//si se produjo un error al procesar los datos","            printf(\"Fallo en el accept: %s\\n\", strerror(errno));","            exit(1);","        }","\t\twhile (1){","\t\t\testado = 0;//una bandera para controlar si se enviaron respuestas del caso 1 2 o 3","\t\t\tcc = read(ssock, mensaje, sizeof(mensaje));//se lee el mensaje recibido en el socket ssock y se guarda en mensaje","\t\t\t//Borrar el \"\\n\"","\t\t\tp = strchr(mensaje, '\\n');","\t\t  \tif (p)","\t\t\t\t*p = '\\0';","\t\t\tif(strcmp(salir,mensaje)==0){//si el mensaje fue salir, entonces se sale","\t\t\t\tbreak;","\t\t\t}","","\t\t\t//imprime fecha y hora","\t\t\t","\t\t\ttime_t tiempo = time(0);","\t\t\tstruct tm *tlocal = localtime(&tiempo);","\t\t\tchar output[128];","\t\t\tstrftime(output,128,\"%d/%m/%y %H:%M:%S\",tlocal);","\t\t\tprintf(\"Se recibe y responde datos el: %s\\n\",output);","\t\t\t","\t\t\tprintf(\"Servidor ahora recibe: %s \\n\", mensaje);","\t\t\t// aqui comenzamos el analisis para saber que nos envio el cliente para dar una respuesta respectica a su caso","\t\t\t","\t\t\t// recibe el servidor mensaje 1 y responde mensaje 2  ","\t\t\tif(estado == 0){","\t\t\t\tif(strcmp(mensaje1, mensaje)==0 && estado == 0){","\t\t\t\t\t//printf(\"Es caso 1\\n\");","\t\t\t\t\tprintf(\"Servidor ahora responde: %s \\n\\n\\n\", mensaje2);\t","\t\t\t\t\t(void) write(ssock, mensaje2, sizeof(mensaje2));","\t\t\t\t\testado = 1;//se marca la respuesta","\t\t\t\t}else{","\t\t\t\t\t//printf(\"no es caso 1\\n\");","\t\t\t\t}","\t\t\t}","\t\t\t","\t\t\t//recibe el servidor mensaje 3 y responde mensaje 4 ","\t\t\tif(estado == 0){","\t\t\t\tif(strcmp(mensaje3, mensaje)==0 ){","\t\t\t\t\t//printf(\"Es caso 2\\n\");","\t\t\t\t\tprintf(\"Servidor ahora responde: %s \\n\\n\\n\", mensaje4);\t","\t\t\t\t\t(void) write(ssock, mensaje4, sizeof(mensaje4));","\t\t\t\t\testado = 1;//se marca la respuesta","\t\t\t\t}else{","\t\t\t\t\t//printf(\"no es caso 2\\n\");","\t\t\t\t}","\t\t\t}","\t\t\t//recibe el servidor un mensaje que no conoce entonces envia el mensaje 5","\t\t\tif(estado == 0){","\t\t\t\tif(estado == 0) {","\t\t\t\t\t//printf(\"Es caso 3\\n\");","\t\t\t\t\tprintf(\"Servidor ahora responde: %s \\n\\n\\n\", mensaje5);\t","\t\t\t\t\t(void) write(ssock, mensaje5, sizeof(mensaje5));","\t\t\t\t}else{","\t\t\t\t\t//printf(\"no es caso 3??\\n\");","\t\t\t\t}","\t\t\t  ","\t\t\t}","\t\t\t","\t\t}","        (void) close(ssock);//se libera el socket ssock que fue reservado","    }","\texit(0);","}"],"id":1}]]},"ace":{"folds":[],"scrolltop":0,"scrollleft":0,"selection":{"start":{"row":132,"column":1},"end":{"row":132,"column":1},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":0},"timestamp":1466641424026,"hash":"4ba72f5fa74a16b84d1bf77814c9b43dd1b89611"}