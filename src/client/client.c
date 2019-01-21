/**
 *      @file  client.c
 *      @brief Client Program
 *
 * Connect to a server with a specific port, given by user input. Then
 * sends the parameters for simulation through sockets and waits for
 * server response.
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  10-Jan-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */

#include "myclient.h"

#define MAXCHARS 4096   //just a large buffer for data chunks

/**
 * @brief Connects to a server by TCP-IP protocol. Then it will send the parameters
 * needed to start the simulation.
 *
 * @param  message - parameters to be sent to server
 * @param  port - port number to connect to server
 * @return 1 or 0 depending on simulation or connection success
 */
int Client(char *message,int port)
{
struct timeval tv;
srv_status retval;
char addr[20];      // an auxiliary string
char server_reply[MAXCHARS-1];
int ret;
          sprintf(addr, "127.0.0.1"); // fills adr string with local ip
          printf("address-> %s\n",addr);
          /* send message to server and waits for answer (server_reply) */
          ret=pari_AskDataFromServer(addr, port, message, server_reply, MAXCHARS);
          if(ret) printf("server_reply -> %s\t",server_reply);
          /* checks if simulation is Completed*/
          if(!strncmp(server_reply, "Simulation Completed" , 20))
          {
                  return SUCCESS;   // Simulation Succeeded
          }
          else
          {
                  return FAIL;      // Simulation Failed
          }
	return FAIL; // Connection Failed
}
