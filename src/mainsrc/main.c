/**
 *      @file  main.c
 *      @brief  Programa Principal
 *
 * Descrição mais detalhada do ficheiro
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  27-Sep-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */

#define _MAIN_C_
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "myf.h"
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <errno.h>
#include <termios.h>
#include <sys/shm.h>



/**
 * @brief Starts program and with the use of fork, divides into two
 *    seperated processes. GUIMain, which handles all interface
 *    configuration and callbacks. ManagerMain handles the
 *    comunication between the server to perform the simulation.
 *
 * @param  argc - number of arguments
 * @param  argv[] - array with innput arguments
 * @return none
 */
int main(int argc, char *argv[])
{
    int pid = fork();
    int s_id;

    /* handling erros if no port is provided */
    if(argc < 2){
            fprintf(stderr, "Syntax: %s <port_num>\n", argv[0]);
	          fprintf(stderr, "ERROR, no port provided\n");
	          exit(1);
    }
    port = atoi(argv[1]);	//get port number from command line
    printf("argv(1):%d\n",port);
    if(pid == -1) { printf("Could not fork(). Exiting\n"); return -1; }

    if(pid == 0)            /* The child */
    {
            MessageFromChild("I am the child\n");
            ManagerMain();
            MessageFromChild("CHILD ended\n");
    }
    else /* The parent */
    {
            MessageFromParent("I am the parent\n");
            s_id = GUIMain();                        //Get s_id from return value to know the id to destroy the shared mem
            if(s_id > 0) shmctl(s_id, IPC_RMID, NULL);  //Allow elimination of shared memory
            //if you comment the previous line the shared memory is not cleared from system!
            kill(pid,SIGTERM);
            MessageFromParent("PARENT ended\n");
    }

    return 0;
}
