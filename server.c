/*
 ** server.c -- separation in modules of a simple client server demo
 ** based on the demo taken from Beej's Guide to Networking
 ** http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <unistd.h>

// allocate memory for global variable server_socket_fd
sig_atomic_t server_socket_fd;

#include "net.h"
#include "signals.h"
#include "request_handler.h"

int main(void)
{
	int new_fd; // listen on sock_fd, new connection on new_fd

	server_socket_fd = net_bind_socket();

	signals_setup_listeners();

	printf("server: waiting for connections...\n");

	while ( 1 ) { // main accept() loop
		new_fd = net_accept_connection();
		if ( new_fd == -1 )
			continue;

		if ( !fork() ) { // this is the child process
			close(server_socket_fd); //child doesn't need the listener
			request_handler_handle(new_fd);
		}
		close(new_fd); //parent doesn't need this
	}

	return 0;
}
