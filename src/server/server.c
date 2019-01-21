/**
 *      @file  server.c
 *      @brief  Simple TCP/IP server that deals with multiple clients
 *
 *	Based on http://www.linuxhowtos.org/C_C++/socket.htm
 *	A simple server in the internet domain using TCP
 *	The port number is passed as an argument
 *	This version runs forever, forking off a separate
 *	process for each connection
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 *   @internal
 *     Created  19-Dez-2012
 *   Revisions  09-Dez-2014, 08-Dez-2015, Dez-2017
 *	 Modified 	Jan-2018 by Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 * =====================================================================================
 */

#define _MAIN_C_

#include "myserver.h"
/**
 * @brief  Server main.
 *
 * @param  argc - integer with number of user inputs
 * @return none - array with user inputs
 */
int main(int argc, char *argv[])
{
	int sockfd, clientsockfd, portno, pid;
	int ret;
	char clntName[INET_ADDRSTRLEN];	                   // String to contain client name
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	//To avoid defuncts due to the fork() below.
	//It is actually the default action and occurs when Child stopped or terminated
	signal(SIGCHLD, SIG_IGN);

	//To catch CTRL_C and allow the closure of port
	signal(SIGINT, ManageCTRL_C);

	if(argc < 2)
	{
		fprintf(stderr, "Syntax: %s <port_num>\n", argv[0]);
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	//create a INET socket to communicate
	if(sockfd < 0) myerror("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));	//fill with zeros
	portno                    = atoi(argv[1]);	//get port number from command line
	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port        = htons(portno);
	ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));	//bind the name to the socket
	if(ret < 0) myerror("ERROR on binding");

	listen(sockfd, 20);           //start waiting for connections on the socket up to a maximum of 20 connections
	clilen = sizeof(cli_addr);

	//make socket non blocking so other events may be processed inside the infinite loop
	//An equivalent action could also be done at the socket creation...
	int flags = fcntl(sockfd, F_GETFL, 0); fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	while(infinite_loopG)
	{
		clientsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);	//accept the connection
		if(clientsockfd < 0)  //some error occured.
		{
			if (errno == EAGAIN) continue;  //simply absence of data on nonblocking socket. Not really an error.
			myerror("ERROR on accept");
		}

		/*notify that you know the client: this is optional */
		if(inet_ntop (AF_INET, &cli_addr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
			printf("Client %s connected/%d\n", clntName, ntohs(cli_addr.sin_port));
		else
			printf("Unable to get client address\n");

		pid = fork();	                         //create a process child to manage the connection
		if(pid < 0) myerror("ERROR on fork");	 //rare but may occur!
		if(pid == 0)	                         //It is the child... proceed accordingly
		{
			close(sockfd);	 //child no longer needs the parent socket. Close it, after all it's simply a handle
					//Cf. http://stackoverflow.com/questions/14427898/socket-from-parent-to-child
			processclient(clientsockfd, clntName);	 //Process client request (a new process)
			exit(0);	                 //Exits when finishing processing the client request
		}
		else	       //It is the parent... does nothing: closes the client socket and resume accepting...
			close(clientsockfd);
	}/* end of while */

	close(sockfd);
	return 0;		/* we only get here when someone breaks the infinite loop */
}



/**
 * @brief  Function to process client request
 *
 * There will be a separate instance of this function
 * for each connection established by clients. It handles
 * all communications once a connection has been established.
 *
 * @param  sock The socket ID
 * @param  clientID The client ID (normally the IP)
 * @return  Nothing. It will return to terminate immediatly
 */
void processclient(int sock, char *clientID)
{
	int n, numBytesSent, bufLen;
	char inbuffer[BUFFSIZE], outbuffer[BUFFSIZE], command[BUFFSIZE],*str;
	char length[BUFFSIZE], youngM[BUFFSIZE], poisson[BUFFSIZE], jobname[BUFFSIZE];
	int count=0;
	int keepGoing=1;

	while(keepGoing)
	{
		bzero(inbuffer, BUFFSIZE);	//empty buffer
		n = recv(sock, inbuffer, BUFFSIZE-1,0);
		if(n == BUFFSIZE-1)	//means read the entire buffer... there is the chance that more data may be waiting
		{
			printf("Buffer filled\n");
			//mysocketflush(sock);
			//in that case additional memory should be allocated
			//to read the remainder of the message and build it entirely to deal with it.
			//Not done in this example but may be necessary if large bunchs of data were sent from client.
		}

		if(n < 0) myerror("ERROR reading from socket"); // error handler

		printf("Message received from the client %s: %s\n", clientID, inbuffer);

		    // Returns first token
				char *token = strtok(inbuffer, ",");
				sprintf(command,"%s",token);									// Get command

		    // Keep filling variables with tokens while one of the
		    // delimiters is present in inbuffer[].
				/* the inbuffer recieved from socket is expected to have
				a certain structure (command,lenght,youngM,poisson,jobname).
				If you want to add some other parameters you can do so by adding
				here and in StartSimulation function accordingly. */
		    while (token != NULL)
		    {
		        printf("%s\n", token);
		        token = strtok(NULL, ",");
						count++;
						switch (count) {
							case 1:sprintf(length,"%s",token); break;  // Get length
							case 2:sprintf(youngM,"%s",token); break;	 // Get youngM
							case 3:sprintf(poisson,"%s",token); break; // Get poisson
							case 4:sprintf(jobname,"%s",token); break; // Get jobname
						}
		    }
				count=0;
				/* A control check for erros */
				printf("Command: %s\n", command);
				printf("length: %s\n", length);
				printf("youngM: %s\n", youngM);
				printf("poisson: %s\n", poisson);
				printf("jobname: %s\n", jobname);

		/* interpret what command the Client wanted, and answer accordingly */
		if(!strncmp(command, "who", 3))	//answer who am I
		{
			strcpy(outbuffer, "mgaspar");  //adapt this to your ID
			bufLen = strlen(outbuffer);
		}
		else if(!strncmp(command, "time", 4))	// send your current time
		{
			str=vsTimeString();
			sprintf(outbuffer, "%s", str);
			free(str);
			bufLen = strlen(outbuffer);
		}
		else if(!strncmp(command, "simulate", 4))
		{
			StartSimulation(length,youngM,poisson,jobname);	// Starts Simulation
			sprintf(outbuffer, "Simulation Completed");
			bufLen = strlen(outbuffer);
		}
		else if(!strncmp(command, "quit", 4))
		{
			sprintf(outbuffer, "Client %s, you have requested to close the connection!", clientID);
			bufLen = strlen(outbuffer);
			keepGoing=0;
		}
		//Here you can add other elseifs
		else
		{
			sprintf(outbuffer, "Client %s, your message is not recognized!", clientID);
			bufLen = strlen(outbuffer);
		}

		numBytesSent = send(sock, outbuffer, bufLen, 0);   //here send the reply to the client
		if(numBytesSent < 0) myerror("send()/write() failed");
	}
	printf("\nConnection to client %s terminated.\n", clientID);
}
