
all: NEAS-Server NEAS-Client
	
NEAS-Server: NEAS-Server.c PTI_functions/socketServer.o
	gcc -o NEAS-Server NEAS-Server.c PTI_functions/socketServer.o -I. -lpthread

NEAS-Client: NEAS-Client.c PTI_functions/socketClient.o
	gcc -o NEAS-Client NEAS-Client.c PTI_functions/socketClient.o -I.

socketServer.o: PTI_functions/socketServer.c
	gcc -c PTI_functions/socketServer.c -I.

socketClient.o: PTI_functions/socketClient.c
	gcc -c PTI_functions/socketClient.c -I.
clean:
	rm NEAS-Client NEAS-Server