/* 
 * File:   main.c
 * Author: aurelio
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <stdbool.h>

#include "srvcxnmanager.h"

#include <netinet/tcp.h>

#include "fichier_confsrv.h"
#include "fichier_csv.h"
/*
 *
 */

//int newSocket = 0;
player* playerPool[100];
game* gamePool[100];

/**
 * @brief Fonction principale du serveur
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv) {

    int sockfd = -1;
    int index = 1;
    connection_t *connection;
    pthread_t thread;
    //config();
    //csvFile();
    //csvWriteAndRead();
    /* init array*/
    init_sockets_array();
    /* create socket */
    sockfd = create_server_socket();
    
    /* listen on port , stack size 50 for incoming connections*/
    if (listen(sockfd, 50) < 0) {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }

    addGameToPool(4, 8, 2);

    printf("ready and listening\n");

    //Wait for connection
    while (true) {
        /* accept incoming connections */
        connection = (connection_t *) malloc(sizeof (connection_t));
        connection->sockfd = accept(sockfd, &connection->address, &connection->addr_len);
        connection->index = index++;
        if (connection->sockfd <= 0) {
            free(connection);
        } else {

            player* newPlayer;
            newPlayer = (player *) malloc(sizeof(player*));
            newPlayer->connection = connection;
            
            /* start a new thread but do not wait for it */
            pthread_create(&thread, 0, threadProcess, (void *) newPlayer);
            pthread_detach(thread);
        }
    }

    return (EXIT_SUCCESS);
}