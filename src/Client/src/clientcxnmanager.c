/**
 * @file clientcxnmanager.c
 * @author Thomas
 * @brief 
 * @version 0.1
 * @date 2020-12-17
 * 
 * @copyright Copyright (c) 2020
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
#include <netinet/tcp.h>
#include "clientcxnmanager.h"
#include "packetmanager.h"
#include "Controller/envoiClientToServ.h"
#include "confreadwrite.h"



configuration* clientInfos;





/**
 * @brief Processus du thread
 * 
 * @param ptr 
 * @return void* 
 */
void *threadProcess(void * ptr) {
    char buffer_in[BUFFERSIZE];
    int sockfd = *((int *) ptr);
    int len;
    clientInfos = config();
    int clientID = atoi(clientInfos->IdClient);

    clientInitClient(sockfd, clientID); //Envoi d'un paquet d'init avec le ClientID

    while ((len = read(sockfd, buffer_in, BUFFERSIZE)) != 0) {
        receivePacket(buffer_in, sockfd);
    }

    close(sockfd);
    printf("client pthread ended, len=%d\n", len);
}

/**
 * @brief Ouvre une connexion avec le serveur
 * 
 * @return int Socket de la connexion ouverte
 */
int open_connection() {

    int sockfd;
    int port = 7799;
    struct sockaddr_in serverAddr;

    // Create the socket. 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Disable Nagle's Algorithm that causes problem for sending data
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));

    //Configure settings of the server address
    // Address family is Internet 
    serverAddr.sin_family = AF_INET;

    //Set port number, using htons function 
    serverAddr.sin_port = htons(port);

    //Set IP address to localhost
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    //Connect the socket to the server using the address
    if (connect(sockfd, (struct sockaddr *) &serverAddr, sizeof (serverAddr)) != 0) {
        printf("Fail to connect to server");
        exit(-1);
    };
    return sockfd;
}

/**
 * @brief Permet de créer un thread
 * 
 * @param sockfd Socket de la connexion
 */
void createPthread(int sockfd) {

    int status = 0;
    char bufferOut[1000];
    pthread_t thread;

    //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcess, &sockfd);
    pthread_join(thread, NULL);
}