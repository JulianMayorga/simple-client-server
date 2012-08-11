/*
 ** request_handler.c -- request_handler module c file
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "request_handler.h"

extern int server_socket_fd;

void request_handler_handle(int socket_fd) {	
	//TODO reformat Hello World code into another c file
	if ( send(socket_fd, "Hello World!", 13, 0) == -1 )
			perror("send");
	close(socket_fd);
	exit(0);
}
