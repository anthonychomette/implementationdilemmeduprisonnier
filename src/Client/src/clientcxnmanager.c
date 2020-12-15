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

void *threadProcess(void * ptr) {
    char buffer_in[BUFFERSIZE];
    int sockfd = *((int *) ptr);
    int len;

    //printf("&&&&&&& Debut ThreadProcess\n\n");

    //recuperation du clientID
    int clientID = 8; //TODO RECUP DEPUIS LE FICHIER DE CONF

    //printf("Avant paquet d'Init\n\n");
    //Envoi d'un paquet d'Init
    clientInitClient(sockfd, clientID);
    //printf("paquet d'Init\n\n");

    //usleep(100000); //Pause de 10 ms ne pas utiliser normalement mais obligatoire

    //Envoi d'un paquet d'Attente
    //ClientWaitingGame(sockfd);
    //usleep(100000); //Pause de 10 ms ne pas utiliser normalement mais obligatoire */

    //printf("&&&&&&& Mid ThreadProcess\n\n");
    while ((len = read(sockfd, buffer_in, BUFFERSIZE)) != 0) {
        //printf("&&&&&&& WHILE ThreadProcess\n\n");
        receivePacket(buffer_in, sockfd);
    }

    //printf("&&&&&&& Fin ThreadProcess\n\n");

    close(sockfd);
    printf("client pthread ended, len=%d\n", len);
}

int open_connection() {
    //printf("&&&&&&&&&&&&Debut open connection\n\n");
    int sockfd;

    struct sockaddr_in serverAddr;
    int port = 7799;

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

    //printf("&&&&&&&&&&&&FIN open connection\n\n");
    return sockfd;
}

/* int createSocket() {
    int sockfd = open_connection();
    return sockfd;
} */

void createPthread(int sockfd) {



    int status = 0;
    char bufferOut[1000];
    pthread_t thread;

    //clientInitClient(sockfd, 4);

    //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcess, &sockfd);

    //clientInitClient(sockfd, 5);

    //write(connection->sock,"Main APP Still running",15);

    printf("Detachement du phthread !!!\n");
    pthread_join(thread, NULL);
/*       do {
        fgets(bufferOut, 100, stdin);
        //printf("sending : %s\n", msg);
        status = write(sockfd, bufferOut, strlen(bufferOut));
        //memset(msg,'\0',100);
    } while (status != -1); */
}