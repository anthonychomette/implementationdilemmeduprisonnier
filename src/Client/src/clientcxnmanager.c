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

void *threadProcess(void * ptr) {
    char buffer_in[BUFFERSIZE];
    int sockfd = *((int *) ptr);
    int len;
    while ((len = read(sockfd, buffer_in, BUFFERSIZE)) != 0) {
        if (strncmp(buffer_in, "exit", 4) == 0) {
            break;
        }

        receivePacket(buffer_in);

        printf("receive %d chars\n", len);
        printf("%.*s\n", len, buffer_in);
    }
    close(sockfd);
    printf("client pthread ended, len=%d\n", len);
}

int open_connection() {
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

    return sockfd;
}

/* int createSocket() {
    int sockfd = open_connection();
    return sockfd;
} */

void createPthread(int sockfd) {

    int status = 0;
    char bufferOut[500];
    pthread_t thread;

    //clientInitClient(sockfd, 4);

    //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcess, &sockfd);

    //clientInitClient(sockfd, 5);

    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(thread);
    do {
        fgets(bufferOut, 100, stdin);
        //printf("sending : %s\n", msg);
        status = write(sockfd, bufferOut, strlen(bufferOut));
        //memset(msg,'\0',100);
    } while (status != -1);
}