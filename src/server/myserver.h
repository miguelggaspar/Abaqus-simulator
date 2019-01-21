/**
 *       @file  myserver.h
 *      @brief
 *
 * Detailed description starts here.
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 *   @internal
 *     Created  09-Dez-2014
 *   Copyright  Copyright (c) 2014, Vitor Santos, 2016
 *
 * =====================================================================================
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#ifdef _MAIN_C_
	int infinite_loopG=1;
	const int BUFFSIZE=1024;		/*If this is small, enlarge it or use dynamic allocation */
#else
	extern int infinite_loopG;
	extern const int BUFFSIZE;
#endif

typedef struct { int hora, minutos;} tempo;

#include "prototypes.h"
