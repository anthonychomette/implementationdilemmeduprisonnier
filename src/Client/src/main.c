/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aurelio
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "clientcxnmanager.h"
#include "packetmanager.h"


/*
 * 
 */
int main(int argc, char** argv) {


    int sockfd;
    int status = 0;
    char bufferOut[500];
    pthread_t thread;
    config();
    sockfd = open_connection();

    //paquetClientInit *paquetOK = malloc(1 * sizeof(paquetClientInit));
    //paquetClientInit *paquetOK;


    //Ancien Code bon ! packetClientInit *paquetOK = createPacketClientInit(42);
    //Ancien Code bon ! write(sockfd, paquetOK, sizeof(paquetOK));

    //strcpy(msg, "Hello from Xeon"); //Xeon is the name of the this client
    //printf("sending : %s\n", msg);
    
    //memcpy(bufferOut, paquetOK, sizeof(paquetOK));
    
    //bufferOut = paquetOK;
    //write(sockfd, bufferOut, strlen(bufferOut));

    sendPacket(sockfd, 1, 42);

    //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcess, &sockfd);
    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(thread);
    do {
        fgets(bufferOut, 100, stdin);
        //printf("sending : %s\n", msg);
        status = write(sockfd, bufferOut, strlen(bufferOut));
        //memset(msg,'\0',100);
    } while (status != -1);

    return (EXIT_SUCCESS);
}

