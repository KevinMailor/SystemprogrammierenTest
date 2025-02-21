#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include "connectionhandler.h"
#include "util.h"

static int createPassiveSocket(in_port_t port)
{
	int fd = -1;
	//TODO: socket()
	fd=socket(AF_INET, SOCK_STREAM,0);
	if(fd<0){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	//TODO: bind() to port
	struct sockaddr_in address;
	memset(&address,0,sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(fd,(struct sockaddr* ) &address, sizeof(address)) < 0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}


	//TODO: listen()
	if(listen(fd,4)<0){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	errno = ENOSYS;
	return fd;
	
}

int connectionHandler(in_port_t port)
{
	const int fd = createPassiveSocket(port);
	if(fd == -1)
	{
		errnoPrint("Unable to create server socket");
		return -1;
	}

	for(;;)
	{
		//TODO: accept() incoming connection
		//Macht Passiven Socket	
		const int passive_sock=createPassiveSocket(port);
		if(passive_sock == -1 ){
			perror("Error creating passive socket");
			return EXIT_FAILURE;
		}
		//Macht aktiven Socket
		const int active_sock = accept(passive_sock, NULL, NULL);
		if(active_sock == -1){
			perror("Error accepting  a connecton");
			continue;
		}


		//TODO: add connection to user list and start client thread
		pthread_t id[2];
		pthread_create(&id[0], NULL,NewUser,User u);	
		



		close(active_sock);
	}

	return 0;	//never reached
}
