/**
 *      @file  myfclient.c
 *      @brief Auxiliary functions for client
 *
 * Connects to a server port number given by user input and
 * send messages to a server. Can also check for available ports.
 *
 *
 *
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

/**
 * @brief Test if a server is responding in a given port
 *
 * @param  adrr - String with the IP address
 * @param  port - Integet with the port number
 * @param  tv -   Address of a struct timeval with the timeout
 *                NB. On returning, the tv structure holds the time
 *                left after the connection attempt. Can be useful to assess
 *                the speed of the connection.
 * @return srv_status value (NOTAVAILABLE, PORTOPEN, PORTCLOSED, ...)
 */
srv_status pari_TestServer(char *addr, int port, struct timeval *tv)
{
        struct sockaddr_in address;  /* the libc network address data structure */
        int sock;                    /* file descriptor for the network socket */
        srv_status ret=NOTAVAILABLE; /*default value*/
        fd_set fdset;                /* set of sockets to test. Here only 1*/
        int so_error;
        int len = sizeof(so_error);

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if( ! sock )
        {
                printf("Could not create socket\n");
                return ret;
        }
        fcntl(sock, F_SETFL, O_NONBLOCK);
        address.sin_family = AF_INET;
        address.sin_port = htons(port);             /* translate int2port num */
        address.sin_addr.s_addr = inet_addr(addr);  /* assign the address */

        connect(sock, (struct sockaddr *) &address, sizeof(address));

        FD_ZERO(&fdset);       //clear set of sockets to test
        FD_SET(sock, &fdset);  //insert the socket to test

        if(select(sock + 1, NULL, &fdset, NULL, tv) == 1)
        {
                getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
                if(so_error == 0)
                        ret=PORTOPEN;
                else
                        ret=PORTCLOSED;
        }

        close(sock);
        return ret;
}

/**
 * @brief  Sends a message to server and feteches the reply
 *
 * @param  ip string with the server IP (xxx.xxx.xxx.xxx)
 * @param  port Integer with the port number
 * @param  message String with message to send to server
 * @param  server_reply String with message given by the server
 * @param  maxChars maximal size of server reply
 *
   * @return 1 in case of sucess. 0 for error.
 */
int pari_AskDataFromServer(char *ip, int port, char *message, char *server_reply, int maxChars)
{
        int sock;
        int ret;
        struct sockaddr_in server;
        char buffer[100];

        bzero(&server, sizeof(server));      //fill with zeros
        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        //Create a socket for communications
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock == -1)
        {
                printf("Could not create socket\n");
                return 0;
        }

        //Connect to remote server using the created socket
        ret = connect(sock, (struct sockaddr *) &server, sizeof(server));
        if(ret < 0)
        {
                printf("connect error\n");
                return 0;
        }

        //send the query message
        ret = send(sock,message, strlen(message), 0);
        if(ret < 0)
        {
                printf("Send failed\n");
                return 0;
        }

        //receive the answer up to a maximal size...
        bzero(server_reply, maxChars);  //important when reading repeatidely
        ret = recv(sock, server_reply, maxChars, 0);
        if(ret < 0)
        {
                printf("recv failed\n");
                return 0;
        }

        //close the socket before exiting
        close(sock);
        return 1;  //success
}
