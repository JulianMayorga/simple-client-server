/*
 ** signals.c -- signals module c file
 ** signal handler
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "signals.h"

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void signals_setup_listeners() {
	struct sigaction sa;
	
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if ( sigaction(SIGCHLD, &sa, NULL) == -1 ) {
		perror("sigaction");
		exit(1);
	}
}
